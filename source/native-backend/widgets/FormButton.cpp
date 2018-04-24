//
// Created by a_mod on 22.04.2018.
//

#include "native-backend/widgets/FormButton.h"

std::string FormButton::build(std::string &, size_t) {
    return std::string();
}

std::string FormButton::build(std::string &&, size_t) {
    return std::string();
}

size_t FormButton::contentSize() {
    return 0;
}

boost::shared_ptr<nvb::IWidget> FormButton::add(boost::shared_ptr<nvb::IWidget>) {
    return boost::shared_ptr<nvb::IWidget>();
}

boost::shared_ptr<nvb::IWidget> FormButton::setProperty(std::pair<std::string, boost::shared_ptr<void>>) {
    return boost::shared_ptr<nvb::IWidget>();
}

boost::shared_ptr<nvb::IWidget> FormButton::generateHtml() {
    return boost::shared_ptr<nvb::IWidget>();
}

boost::shared_ptr<nvb::IWidget> FormButton::updateAll() {
    return boost::shared_ptr<nvb::IWidget>();
}

std::string FormButton::buildJs(std::string &document, boost::shared_ptr<nvb::JSBundle> jsBundle) {
    return document;
}

std::string FormButton::buildJs(std::string &&document, boost::shared_ptr<nvb::JSBundle> jsBundle) {
    return document;
}


