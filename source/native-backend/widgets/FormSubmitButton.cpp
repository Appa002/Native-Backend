//
// Created by a_mod on 22.04.2018.
//

#include <sstream>
#include "native-backend/widgets/FormSubmitButton.h"
#include <native-backend/parsing/TextProcessor.h>
#include <native-backend/errors/errors.h>

std::string nvb::FormSubmitButton::build(std::string & document, size_t pos) {
    if(!contains_newest_state_)
        throw error::old_state_error("A FormSubmitButtonWidget contains old state!");
    return document.insert(pos, generated_html_);
}

std::string nvb::FormSubmitButton::build(std::string && document, size_t pos) {
    if(!contains_newest_state_)
        throw error::old_state_error("A FormSubmitButtonWidget contains old state!");
    return document.insert(pos, generated_html_);
}

size_t nvb::FormSubmitButton::contentSize() {
    return generated_html_.size();
}

boost::shared_ptr<nvb::IWidget> nvb::FormSubmitButton::add(boost::shared_ptr<nvb::IWidget>) {
    throw nvb::error::no_child_error("A SubmitButton can't take a child!");
}

boost::shared_ptr<nvb::IWidget> nvb::FormSubmitButton::setProperty(std::pair<std::string, boost::shared_ptr<void>>) {
    return boost::shared_ptr<nvb::IWidget>();
}

boost::shared_ptr<nvb::IWidget> nvb::FormSubmitButton::generateHtml() {
    contains_newest_state_ = true;
    std::unordered_map<std::string, std::string> replacements;
    std::string out = template_html;

    const void * address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;
    replacements["[ID]"] = ss.str();

    nvb::TextProcessor::process(&out, replacements);
    generated_html_ = out;
    return getSharedPtrToThis();
}

boost::shared_ptr<nvb::IWidget> nvb::FormSubmitButton::updateAll() {
    updateLeast();
    return getSharedPtrToThis();
}

std::string nvb::FormSubmitButton::buildJs(std::string &document, boost::shared_ptr<nvb::JSBundle> jsBundle) {
    std::unordered_map<std::string, std::string> replacements;
    std::string out = template_js;

    const void * address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;
    replacements["MYID"] = ss.str();
    replacements["FORMID"] = jsBundle->passersId;

    nvb::TextProcessor::process(&out, replacements);

    document += "\n" + out;
    return out;

}

std::string nvb::FormSubmitButton::buildJs(std::string &&document, boost::shared_ptr<nvb::JSBundle> jsBundle) {
    std::unordered_map<std::string, std::string> replacements;
    std::string out = template_js;

    const void * address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;
    replacements["[MYID]"] = ss.str();
    replacements["[FORMID]"] = jsBundle->passersId;

    nvb::TextProcessor::process(&out, replacements);

    document += "\n" + out;
    return out;
}

boost::shared_ptr<nvb::IWidget> nvb::FormSubmitButton::createShared() {
    auto ptr = boost::shared_ptr<IWidget>(new FormSubmitButton());
    ptr->setSharedPtrToThis(ptr);
    return ptr;
}


