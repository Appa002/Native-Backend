//
// Created by albert on 3/24/18.
//

#include "native-backend/widgets/PaperWidget.h"
#include <native-backend/parsing/TextProcessor.h>
#include <string>
#include <native-backend/widgets/TextWidget.h>

std::string nvb::PaperWidget::build(std::string & document, size_t pos) {
    if(!contains_newest_state_)
        error::invalid_argument_error("The PaperWidget does not contain the newest state!");
    return document.insert(pos, generated_html_);
}

std::string nvb::PaperWidget::build(std::string && document, size_t pos) {
    if(!contains_newest_state_)
        error::invalid_argument_error("The PaperWidget does not contain the newest state!");
    return document.insert(pos, generated_html_);
}

size_t nvb::PaperWidget::contentSize() {
    return generated_html_.size();
}

boost::shared_ptr<nvb::IWidget> nvb::PaperWidget::add(boost::shared_ptr<nvb::IWidget> w) {
    contains_newest_state_ = false;
    if(child_.get() != nullptr)
        child_.reset();
    child_ = w;
    return getSharedPtrToThis();
}

boost::shared_ptr<nvb::IWidget> nvb::PaperWidget::setProperty(std::pair<std::string, boost::shared_ptr<void>> pair) {
    contains_newest_state_ = false;
    if(pair.first == "style")
        style_ = boost::shared_ptr<PaperWidgetStyle>((PaperWidgetStyle*)pair.second.get());
    return getSharedPtrToThis();
}

boost::shared_ptr<nvb::IWidget> nvb::PaperWidget::generateHtml() {
    contains_newest_state_ = true;
    std::unordered_map<std::string, std::string > replacements;

    if(!style_->getWidth().unit.empty() && style_->getWidth().value != 0)
        replacements["[WIDTH]"] = "width: " + std::to_string(style_->getWidth().value) + style_->getWidth().unit + ";";
    else
        replacements["[WIDTH]"] = "";

    if(!style_->getHeight().unit.empty() && style_->getHeight().value != 0)
        replacements["[HEIGHT]"] = "height: " + std::to_string(style_->getHeight().value) + style_->getHeight().unit + ";";
    else
        replacements["[HEIGHT]"] = "";


    std::stringstream stream;
    stream << "#" << std::hex << style_->getBackgroundColor();
    std::string colorAsHex( stream.str() );

    replacements["[BACKGROUND_COLOR]"] = colorAsHex;

    std::string out = template_html_;
    TextProcessor::process(&out, replacements);

   if(child_.get() != nullptr){
        size_t pos = out.find("[INSERT]");
        out.replace(pos, 8, "");
        out.insert(pos, child_->build("", 0));
    }else{
        size_t pos = out.find("[INSERT]");
        out.replace(pos, 8, "");
    }

    generated_html_ = out;
   // return boost::shared_ptr<IWidget>(nullptr);
    return getSharedPtrToThis();

}

boost::shared_ptr<nvb::IWidget> nvb::PaperWidget::updateAll() {
    if(child_.get() == nullptr)
        child_->updateAll();
    else
        updateLeast();
}

nvb::PaperWidget::PaperWidget(boost::shared_ptr<nvb::PaperWidgetStyle> style) : style_(std::move(style)) {}

boost::shared_ptr<nvb::IWidget> nvb::PaperWidget::createShared() {
    auto ptr = boost::shared_ptr<IWidget>(new PaperWidget());
    ptr->setSharedPtrToThis(ptr);
    return ptr;
}

