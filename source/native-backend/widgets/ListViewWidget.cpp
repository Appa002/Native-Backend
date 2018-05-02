#include <native-backend/widgets/ListViewWidget.h>
#include <native-backend/errors/errors.h>

/*!\brief Generates the HTML which is goeing to be injected into the HTML document.*/
boost::shared_ptr<nvb::IWidget> nvb::ListViewWidget::generateHtml() {
    html_contains_newest_state = true;
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

/*!\brief Injects already generated HTML into the document at \c pos.*/
std::string nvb::ListViewWidget::build(std::string &document, size_t pos) {
    if(!html_contains_newest_state)
        throw error::old_state_error("The ListView doesn't contain the newest state.");
    return document.insert(pos, generated_html_);
}

/*!\brief Injects already generated HTML into the document at \c pos.*/
std::string nvb::ListViewWidget::build(std::string &&document, size_t pos) {
    if(!html_contains_newest_state)
        throw error::old_state_error("The ListView doesn't contain the newest state.");
    return document.insert(pos, generated_html_);
}

boost::shared_ptr<nvb::IWidget> nvb::ListViewWidget::createShared() {
    auto sPtr = boost::shared_ptr<IWidget>(new ListViewWidget());
    sPtr->setSharedPtrToThis(sPtr);
    return sPtr;
}

/*!\brief Returns the size of the content that is going to be injected into the document.*/
size_t nvb::ListViewWidget::contentSize() {
    return generated_html_.size();
}

boost::shared_ptr<nvb::IWidget> nvb::ListViewWidget::add(boost::shared_ptr<nvb::IWidget> widget) {
    html_contains_newest_state = false;
    children_.push_back(widget);
    widget->setParent(getSharedPtrToThis());
    return getSharedPtrToThis();
}

boost::shared_ptr<nvb::IWidget>
nvb::ListViewWidget::setProperty(std::pair<std::string, boost::shared_ptr<void>>) {
    html_contains_newest_state = false;
    return getSharedPtrToThis();
}

boost::shared_ptr<nvb::IWidget> nvb::ListViewWidget::updateAll() {
    for(auto& child : children_){
        child->updateAll();
    }

    if(children_.empty())
        updateLeast();
    return getSharedPtrToThis();
}

std::string nvb::ListViewWidget::buildJs(std::string &document, boost::shared_ptr<JSBundle> jsBundle) {
    for(auto& child : children_){
        document += "\n" + child->buildJs(document, jsBundle);
    }
    return document;
}

std::string nvb::ListViewWidget::buildJs(std::string &&document, boost::shared_ptr<JSBundle> jsBundle) {
    for(auto& child : children_){
        document += "\n" + child->buildJs(document, jsBundle);
    }
    return document;
}
