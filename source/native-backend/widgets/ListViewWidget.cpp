#include <native-backend/widgets/ListViewWidget.h>



nvb::ListViewWidget::ListViewWidget(std::vector<boost::shared_ptr<IWidget>> &children) : children_(children), generated_html_(
        generateHtml()) {

}

nvb::ListViewWidget::ListViewWidget(std::vector<boost::shared_ptr<IWidget>> &&children) : children_(children), generated_html_(
        generateHtml()){

}

/*!\brief Generates the HTML which is goeing to be injected into the HTML document.*/
std::string nvb::ListViewWidget::generateHtml() {
    std::string outStr = template_html_;

    size_t injection_position = outStr.find("[INSERT]", 0);
    outStr.erase(injection_position, 8);


    for(auto& child : children_){
        std::string newInjection = child->build(outStr, injection_position);
        injection_position += child->contentSize();
        outStr = newInjection;
    }
    return outStr;
}

/*!\brief Injects already generated HTML into the document at \c pos.*/
std::string nvb::ListViewWidget::build(std::string &document, size_t pos) {
    return document.insert(pos, generated_html_);
}

/*!\brief Injects already generated HTML into the document at \c pos.*/
std::string nvb::ListViewWidget::build(std::string &&document, size_t pos) {
    return document.insert(pos, generated_html_);
}

boost::shared_ptr<nvb::IWidget> nvb::ListViewWidget::createShared(std::vector<boost::shared_ptr<IWidget>> &&children) {
    return boost::shared_ptr<IWidget>(new ListViewWidget(children));
}

boost::shared_ptr<nvb::IWidget> nvb::ListViewWidget::createShared(std::vector<boost::shared_ptr<IWidget>> &children) {
    return boost::shared_ptr<IWidget>(new ListViewWidget(children));
}

/*!\brief Returns the size of the content that is going to be injected into the document.*/
size_t nvb::ListViewWidget::contentSize() {
    return generated_html_.size();
}
