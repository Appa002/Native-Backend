#include <native-backend/widgets/TextWidget.h>

nvb::TextWidget::TextWidget(std::string &text) : generated_html_(generateHtml(text)){

}

nvb::TextWidget::TextWidget(std::string &&text) : generated_html_(generateHtml(text)) {

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
    return boost::shared_ptr<nvb::IWidget>(new TextWidget(text));
}
/*!\brief Returns a \c boost::shared_ptr<IWidget> instance with a newly allocated \c TextWidget.*/
boost::shared_ptr<nvb::IWidget> nvb::TextWidget::createShared(std::string &&text) {
    return boost::shared_ptr<nvb::IWidget>(new TextWidget(text));
}

/*!\brief Returns the size of the content that is going to be injected into the document.*/
size_t nvb::TextWidget::contentSize() {
    return generated_html_.size();
}

/*!\brief Generates the HTML which is going to be injected into the document.*/
std::string nvb::TextWidget::generateHtml(std::string &text) {
    size_t pos_change = template_html.find_first_of("[INSERT]");
    std::string out = template_html;
    out.replace(pos_change, 8, "");
    out.insert(pos_change, text);
    return out;
}
