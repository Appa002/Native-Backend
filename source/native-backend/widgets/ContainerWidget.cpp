//
// Created by albert on 3/25/18.
//

#include <native-backend/errors/errors.h>
#include "native-backend/widgets/ContainerWidget.h"

boost::shared_ptr<nvb::IWidget> nvb::ContainerWidget::generateHtml() {
    html_contains_newest_state_ = true;
    std::string outStr = template_html_;

    size_t injection_position = outStr.find("[INSERT]", 0);
    outStr.erase(injection_position, 8);


    for(auto& child : children_){
        std::string newInjection = child->build(outStr, injection_position);
        injection_position += child->contentSize();
        outStr = newInjection;
    }
    generated_html_ = outStr;
    return getSharedPtrToThis();
}

std::string nvb::ContainerWidget::build(std::string &document, size_t pos) {
    if(html_contains_newest_state_)
        throw nvb::error::old_state_error("Container widget contains old state!");
    return document.insert(pos, generated_html_);
}

std::string nvb::ContainerWidget::build(std::string &&document, size_t pos) {
    if(html_contains_newest_state_)
        throw nvb::error::old_state_error("Container widget contains old state!");
    return document.insert(pos, generated_html_);
}

size_t nvb::ContainerWidget::contentSize() {
    return generated_html_.size();
}

boost::shared_ptr<nvb::IWidget> nvb::ContainerWidget::updateAll() {
    for(auto& child : children_){
        child->updateAll();
    }

    if(children_.empty())
        updateLeast();
    return getSharedPtrToThis();
}

boost::shared_ptr<nvb::IWidget> nvb::ContainerWidget::add(boost::shared_ptr<nvb::IWidget> widget) {
    html_contains_newest_state_ = false;
    children_.push_back(widget);
    widget->setParent(getSharedPtrToThis());
    return getSharedPtrToThis();
}

boost::shared_ptr<nvb::IWidget> nvb::ContainerWidget::setProperty(std::pair<std::string, boost::shared_ptr<void>>) {
    return getSharedPtrToThis();
}

std::string nvb::ContainerWidget::buildJs(std::string &document, boost::shared_ptr<JSBundle> jsBundle) {
    for(auto& child : children_){
        document += "\n" + child->buildJs(document, jsBundle);
    }
    return document;
}

std::string nvb::ContainerWidget::buildJs(std::string &&document, boost::shared_ptr<JSBundle> jsBundle) {
    for(auto& child : children_){
        document += "\n" + child->buildJs(document, jsBundle);
    }
    return document;
}

boost::shared_ptr<nvb::IWidget> nvb::ContainerWidget::createShared() {
    auto sPtr = boost::shared_ptr<IWidget>(new ContainerWidget());
    sPtr->setSharedPtrToThis(sPtr);
    return sPtr;
}
