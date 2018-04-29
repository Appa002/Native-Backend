//
// Created by a_mod on 22.04.2018.
//

#include <native-backend/errors/errors.h>
#include "native-backend/widgets/FormWrapperWidget.h"
#include <native-backend/parsing/TextProcessor.h>
#include <sstream>

std::string nvb::FormWrapperWidget::build(std::string & document, size_t pos) {
    if(!contains_newest_state_)
        throw nvb::error::old_state_error("The FormWrapperWidget contains old state!");
    return document.insert(pos, generated_html_);
}

std::string nvb::FormWrapperWidget::build(std::string && document, size_t pos) {
    if(!contains_newest_state_)
        throw nvb::error::old_state_error("The FormWrapperWidget contains old state!");
    return document.insert(pos, generated_html_);
}

size_t nvb::FormWrapperWidget::contentSize() {
    return generated_html_.size();
}

boost::shared_ptr<nvb::IWidget> nvb::FormWrapperWidget::add(boost::shared_ptr<nvb::IWidget> widget) {
    children_.push_back(widget);
    widget->setParent(getSharedPtrToThis());
    return getSharedPtrToThis();
}

boost::shared_ptr<nvb::IWidget> nvb::FormWrapperWidget::setProperty(std::pair<std::string, boost::shared_ptr<void>> propPair) {
 /*   contains_newest_state_ = false;
    if(propPair.first == "method")
        method = *static_cast<HttpVerb::Verb*>(propPair.second.get());
    else if (propPair.first == "target")
        target = *static_cast<FormWrapperWidgetTarget*>(propPair.second.get());
    else if (propPair.first == "action")
        action = *static_cast<std::string*>(propPair.second.get());
    else
        throw nvb::error::invalid_argument_error("Invalid property for FormWrapperWidget");
*/
    return getSharedPtrToThis();
}

boost::shared_ptr<nvb::IWidget> nvb::FormWrapperWidget::generateHtml() {
    contains_newest_state_ = true;
    std::unordered_map<std::string, std::string> replacements;
    std::string out = template_html;

    const void * address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;
    replacements["[ID]"] = ss.str();

    replacements["[METHOD]"] = HttpVerb::toString(method);
    replacements["[ACTION]"] = action;

    switch (target){
        case FormWrapperWidgetTarget::Self:
            replacements["[TARGET]"] = "_self";
            break;
        case FormWrapperWidgetTarget::NewTab:
            replacements["[TARGET]"] = "_blank";
    }

    size_t insertPos = out.find("[INSERT]");
    out.replace(insertPos, 8, "");

    std::string newInsert;
    for(auto& child : children_){
        newInsert = child->build("", 0);
        out.insert(insertPos, newInsert);
        insertPos += child->contentSize();
    }

    TextProcessor::process(&out, replacements);

    generated_html_ = out;

    return getSharedPtrToThis();
}

boost::shared_ptr<nvb::IWidget> nvb::FormWrapperWidget::updateAll() {
    for(auto& child : children_){
        child->updateAll();
    }

    if(children_.empty())
        updateLeast();
    return getSharedPtrToThis();
}

std::string nvb::FormWrapperWidget::buildJs(std::string &document, boost::shared_ptr<JSBundle> jsBundle) {
    const void * address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;

    jsBundle = boost::shared_ptr<JSBundle>(new JSBundle(ss.str()));

    for(auto& child : children_){
        document += "\n" + child->buildJs(document, jsBundle);
    }
    return document;
}

std::string nvb::FormWrapperWidget::buildJs(std::string &&document, boost::shared_ptr<JSBundle> jsBundle) {
    const void * address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;

    jsBundle = boost::shared_ptr<JSBundle>(new JSBundle(ss.str()));

    for(auto& child : children_){
        document += "\n" + child->buildJs(document, jsBundle);
    }
    return document;
}

boost::shared_ptr<nvb::IWidget> nvb::FormWrapperWidget::createShared(std::string action, nvb::HttpVerb::Verb verb, nvb::FormWrapperWidgetTarget target) {
    auto sPtr = boost::shared_ptr<IWidget>(new FormWrapperWidget(action, verb, target));
    sPtr->setSharedPtrToThis(sPtr);
    return sPtr;
}

nvb::FormWrapperWidget::FormWrapperWidget(std::string action, nvb::HttpVerb::Verb method, nvb::FormWrapperWidgetTarget target) : action(action), method(method),target(target){

}
