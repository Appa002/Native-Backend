//
// Created by albert on 3/17/18.
//

#include <native-backend/widgets/BlockViewWidget.h>
#include <native-backend/parsing/TextProcessor.h>

#include <utility>
#include <native-backend/errors/errors.h>

/*!\brief Constructor which requires a child widget and can take a instance of \c BlockWidgetStyle.*/
nvb::BlockViewWidget::BlockViewWidget(boost::shared_ptr<BlockViewWidgetStyle> style) : style_(std::move(style)) {}

/*!\brief Injects its already generated HTML code into the document.*/
std::string nvb::BlockViewWidget::build(std::string &document, size_t pos) {
    if(!html_contains_newest_state)
        throw error::old_state_error("The BlockView doesn't contain the newest state.");
    return document.insert(pos, generated_html_);

}

/*!\brief Overload with rValue reference for the \c document parameter; see \c build with lValue reference for information about the function. */
std::string nvb::BlockViewWidget::build(std::string &&document, size_t pos) {
    if(!html_contains_newest_state)
        throw error::old_state_error("The BlockView doesn't contain the newest state.");
    return document.insert(pos, generated_html_);

}

/*!\brief Generates HTML with the correct spacers to align the elements correctly and adds the html of the child.*/
boost::shared_ptr<nvb::IWidget> nvb::BlockViewWidget::generateHtml() {
    html_contains_newest_state = true;
    std::unordered_map<std::string, std::string> replacements;
    replacements["[RIGHT_HORIZONTAL_BUFFER]"] = "";
    replacements["[LEFT_HORIZONTAL_BUFFER]"] = "";
    replacements["[TOP_VERTICAL_BUFFER]"] = "";
    replacements["[BOTTOM_VERTICAL_BUFFER]"] = "";

    if(style_->horizontal_alignment == BlockViewWidgetStyle::PositionHint::LEFT)
        replacements["[RIGHT_HORIZONTAL_BUFFER]"] = horizontal_buffer_html_;
    else if (style_->horizontal_alignment == BlockViewWidgetStyle::PositionHint::RIGHT)
        replacements["[LEFT_HORIZONTAL_BUFFER]"] = horizontal_buffer_html_;
    else{
        replacements["[RIGHT_HORIZONTAL_BUFFER]"] = horizontal_buffer_html_;
        replacements["[LEFT_HORIZONTAL_BUFFER]"] = horizontal_buffer_html_;
    }

    if(style_->vertical_alignment == BlockViewWidgetStyle::PositionHint::TOP)
        replacements["[BOTTOM_VERTICAL_BUFFER]"] = vertical_buffer_html_;
    else if (style_->vertical_alignment == BlockViewWidgetStyle::PositionHint::BOTTOM)
        replacements["[TOP_VERTICAL_BUFFER]"] = vertical_buffer_html_;
    else{
        replacements["[TOP_VERTICAL_BUFFER]"] = vertical_buffer_html_;
        replacements["[BOTTOM_VERTICAL_BUFFER]"] = vertical_buffer_html_;
    }

    std::string out = template_html_;
    TextProcessor::process(&out, replacements);

    size_t insert_pos = out.find_first_of("[INSERT]");
    out = out.replace(insert_pos, 8, "");
    out = child_->build(out, insert_pos);

    generated_html_ = out;
    return getSharedPtrToThis();
}

/*!\brief Returns a \c boost::shared_ptr<IWidget> instance with a newly allocated \c BlockViewWidget.*/
boost::shared_ptr<nvb::IWidget> nvb::BlockViewWidget::createShared() {
    auto sPtr = boost::shared_ptr<IWidget>(new BlockViewWidget());
    sPtr->setSharedPtrToThis(sPtr);
    return sPtr;
}

/*!\brief Returns the size of the content that is going to be injected into the document.*/
size_t nvb::BlockViewWidget::contentSize() {
    return generated_html_.size();
}

boost::shared_ptr<nvb::IWidget> nvb::BlockViewWidget::add(boost::shared_ptr<nvb::IWidget> widget) {
    html_contains_newest_state = false;
    child_ = widget;
    widget->setParent(getSharedPtrToThis());
    return getSharedPtrToThis();
}

void nvb::BlockViewWidget::updateState() {

}

boost::shared_ptr<nvb::IWidget>
nvb::BlockViewWidget::setProperty(std::pair<std::string, boost::shared_ptr<void>> pair) {
    if(pair.first == "style"){
        style_.reset();
        style_ = boost::shared_ptr<BlockViewWidgetStyle>((BlockViewWidgetStyle*)pair.second.get());
    }
    return getSharedPtrToThis();
}

