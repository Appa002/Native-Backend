//
// Created by a_mod on 02.05.2018.
//

#include "native-backend/widgets/RawJSWidget.h"

//
// Created by albert on 3/24/18.
//

#include <utility>
#include <native-backend/errors/errors.h>
#include "native-backend/widgets/RawHtmlWidget.h"

nvb::RawJSWidget::RawJSWidget(std::string html) : javascript(std::move(html)){

}

std::string nvb::RawJSWidget::build(std::string & document, size_t pos) {
    if(!contains_newest_state_)
        throw error::old_state_error("The RawWidget doesn't contain the newest state.");
    return document.insert(pos, generated_html_);
}

std::string nvb::RawJSWidget::build(std::string && document, size_t pos) {
    if(!contains_newest_state_)
        throw error::old_state_error("The RawWidget doesn't contain the newest state.");
    return document.insert(pos, generated_html_);
}

size_t nvb::RawJSWidget::contentSize() {
    return generated_html_.size();
}

boost::shared_ptr<nvb::IWidget> nvb::RawJSWidget::add(boost::shared_ptr<nvb::IWidget> w) {
    contains_newest_state_  = false;
    children_.push_back(w);
    return getSharedPtrToThis();
}

boost::shared_ptr<nvb::IWidget> nvb::RawJSWidget::setProperty(std::pair<std::string, boost::shared_ptr<void>>) {
    contains_newest_state_  = false;
    return getSharedPtrToThis();
}

boost::shared_ptr<nvb::IWidget> nvb::RawJSWidget::generateHtml() {
    contains_newest_state_  = true;
    size_t pos = 0;
    std::string out = "";

    for (auto child : children_){
        out = child->build(out, pos);
        pos += child->contentSize();
    }

    generated_html_ = out;
    return getSharedPtrToThis();
}

boost::shared_ptr<nvb::IWidget> nvb::RawJSWidget::updateAll() {
    for(auto& child : children_){
        child->updateAll();
    }

    if(children_.empty())
        updateLeast();
    return getSharedPtrToThis();
}

boost::shared_ptr<nvb::IWidget> nvb::RawJSWidget::createShared(std::string html) {
    auto ptr = boost::shared_ptr<IWidget>(new RawJSWidget(std::move(html)));
    ptr->setSharedPtrToThis(ptr);
    return ptr;
}

std::string nvb::RawJSWidget::buildJs(std::string &document, boost::shared_ptr<JSBundle> jsBundle) {
    document += "\n" + javascript;

    for(auto& child : children_){
        document += "\n" + child->buildJs(document, jsBundle);
    }
    return document;
}

std::string nvb::RawJSWidget::buildJs(std::string &&document, boost::shared_ptr<JSBundle> jsBundle) {
    document += "\n" + javascript;

    for(auto& child : children_){
        document += "\n" + child->buildJs(document, jsBundle);
    }
    return document;
}
