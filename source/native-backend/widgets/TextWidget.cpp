#include <native-backend/widgets/TextWidget.h>
#include <native-backend/errors/errors.h>

#include <utility>
#include <native-backend/parsing/TextProcessor.h>
#include <iomanip>

nvb::TextWidget::TextWidget(std::string &text, boost::shared_ptr<nvb::TextWidgetStyle> style) : text(text), style(
        std::move(style)){
    generateHtml();
}

nvb::TextWidget::TextWidget(std::string &&text, boost::shared_ptr<nvb::TextWidgetStyle> style) : text(text), style(
        std::move(style)){
    generateHtml();
}

/*!\brief Injects already generated HTML into the document at \c pos.*/
std::string nvb::TextWidget::build(std::string &document, size_t pos) {
    return document.insert(pos, generated_html_);
}
/*!\brief Injects already generated HTML into the document at \c pos.*/
std::string nvb::TextWidget::build(std::string &&document, size_t pos) {
    return document.insert(pos, generated_html_);
}

/*!\brief Returns a \c boost::shared_ptr<IWidget> instance with a newly allocated \c TextWidget.*/
boost::shared_ptr<nvb::IWidget> nvb::TextWidget::createShared(std::string &text) {

    auto sPtr = boost::shared_ptr<nvb::IWidget>(new TextWidget(text));
    sPtr->setSharedPtrToThis(sPtr);
    return sPtr;
}
/*!\brief Returns a \c boost::shared_ptr<IWidget> instance with a newly allocated \c TextWidget.*/
boost::shared_ptr<nvb::IWidget> nvb::TextWidget::createShared(std::string &&text) {

    auto sPtr = boost::shared_ptr<nvb::IWidget>(new TextWidget(text));
    sPtr->setSharedPtrToThis(sPtr);
    return sPtr;
}

/*!\brief Returns the size of the content that is going to be injected into the document.*/
size_t nvb::TextWidget::contentSize() {
    return generated_html_.size();
}

/*!\brief Generates the HTML which is going to be injected into the document.*/
boost::shared_ptr<nvb::IWidget> nvb::TextWidget::generateHtml() {
    size_t pos_change = template_html.find("[INSERT]");
    std::string out = template_html;
    out.replace(pos_change, 8, "");
    out.insert(pos_change, text);

    std::stringstream stream;
    stream << "#" << std::hex << style->getColor();
    std::string colorAsHex( stream.str() );

    std::unordered_map<std::string, std::string> replacements;
    replacements["[WEIGHT]"] = std::to_string(style->getFontWeight());
    replacements["[SIZE]"] = std::to_string(style->getSize().value) + style->getSize().unit;
    replacements["[COLOR]"] = colorAsHex;

    TextProcessor::process(&out, replacements);
    generated_html_ = out;
    return getSharedPtrToThis();
}

boost::shared_ptr<nvb::IWidget> nvb::TextWidget::add(boost::shared_ptr<nvb::IWidget>) {
    throw error::no_child_error("A TextWidget can't take a child!");
}

boost::shared_ptr<nvb::IWidget> nvb::TextWidget::setProperty(std::pair<std::string, boost::shared_ptr<void>> pair) {
    if(pair.first == "style")
        style = boost::shared_ptr<TextWidgetStyle>((TextWidgetStyle*)pair.second.get());

    return getSharedPtrToThis();
}

boost::shared_ptr<nvb::IWidget> nvb::TextWidget::updateAll() {
    updateLeast();
}
