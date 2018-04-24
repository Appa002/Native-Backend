//
// Created by albert on 3/24/18.
//

#include <utility>
#include <native-backend/errors/errors.h>
#include "native-backend/widgets/RawWidget.h"

nvb::RawWidget::RawWidget(std::string html) : template_html_(std::move(html)){

}

std::string nvb::RawWidget::build(std::string & document, size_t pos) {
    if(!contains_newest_state_)
        throw error::old_state_error("The RawWidget doesn't contain the newest state.");
    return document.insert(pos, generated_html_);
}

std::string nvb::RawWidget::build(std::string && document, size_t pos) {
    if(!contains_newest_state_)
        throw error::old_state_error("The RawWidget doesn't contain the newest state.");
    return document.insert(pos, generated_html_);
}

size_t nvb::RawWidget::contentSize() {
    return generated_html_.size();
}

boost::shared_ptr<nvb::IWidget> nvb::RawWidget::add(boost::shared_ptr<nvb::IWidget> w) {
    contains_newest_state_  = false;
    children_.push_back(w);
    return getSharedPtrToThis();
}

boost::shared_ptr<nvb::IWidget> nvb::RawWidget::setProperty(std::pair<std::string, boost::shared_ptr<void>>) {
    contains_newest_state_  = false;
    return getSharedPtrToThis();
}

boost::shared_ptr<nvb::IWidget> nvb::RawWidget::generateHtml() {
    contains_newest_state_  = true;
    size_t i = 0;
    size_t pos;
    std::string out = template_html_;
    // Uses the comma operator to iterate through every [CHILD] string in template_html_ and store the position of that
    // [CHILD] in pos (think like for each through a string.
    while((pos = out.find("[CHILD]"), pos) != out.npos){
        out.replace(pos, 7, "");
        out.insert(pos, children_.at(i)->build("", 0));
        i++;
    }
    generated_html_ = out;
    return getSharedPtrToThis();
}

boost::shared_ptr<nvb::IWidget> nvb::RawWidget::updateAll() {
    for(auto& child : children_){
        child->updateAll();
    }

    if(children_.empty())
        updateLeast();
    return getSharedPtrToThis();
}

boost::shared_ptr<nvb::IWidget> nvb::RawWidget::createShared(std::string html) {
    auto ptr = boost::shared_ptr<IWidget>(new RawWidget(std::move(html)));
    ptr->setSharedPtrToThis(ptr);
    return ptr;
}

std::string nvb::RawWidget::buildJs(std::string &document, boost::shared_ptr<JSBundle> jsBundle) {
    for(auto& child : children_){
        document += "\n" + child->buildJs(document, jsBundle);
    }
    return document;
}

std::string nvb::RawWidget::buildJs(std::string &&document, boost::shared_ptr<JSBundle> jsBundle) {
    for(auto& child : children_){
        document += "\n" + child->buildJs(document, jsBundle);
    }
    return document;
}
