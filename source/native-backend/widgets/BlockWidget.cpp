//
// Created by albert on 3/17/18.
//

#include <native-backend/widgets/BlockWidget.h>
#include <native-backend/parsing/TextProcessor.h>

/*!\brief Constructor which requires a child widget and can take a instance of \c BlockWidgetStyle.*/
nvb::BlockWidget::BlockWidget(nvb::IWidget *child, nvb::BlockWidgetStyle* style) : child_(boost::movelib::unique_ptr<IWidget>(child)),
                                                                                   style_(boost::movelib::unique_ptr<BlockWidgetStyle>(style)),
                                                                                   injection_html_(createHtml())
{}

/*!\brief Injects its HTML code and finds the position where the child must inject its HTML code and calls the child's \c build method.*/
std::string nvb::BlockWidget::build(std::string &document, size_t pos) {
    size_t pos_change = raw_html_.find_first_of("[INSERT]");
    std::string insert_html = raw_html_;
    insert_html = insert_html.replace(pos_change, 8, "");
    document = document.insert(pos, insert_html);
    return child_->build(document, pos + pos_change);

}

/*!\brief Overload with rValue reference for the \c document parameter; see \c build with lValue reference for information about the function. */
std::string nvb::BlockWidget::build(std::string &&document, size_t pos) {
    size_t pos_change = injection_html_.find_first_of("[INSERT]");
    std::string insert_html = injection_html_;
    insert_html = insert_html.replace(pos_change, 8, "");
    document = document.insert(pos, insert_html);
    return child_->build(document, pos + pos_change);
}

/*!\brief Configures the \c injection_html_ field according to the \c style field*/
std::string nvb::BlockWidget::createHtml() {
    std::unordered_map<std::string, std::string> replacements;
    replacements["[RIGHT_HORIZONTAL_BUFFER]"] = "";
    replacements["[LEFT_HORIZONTAL_BUFFER]"] = "";
    replacements["[TOP_VERTICAL_BUFFER]"] = "";
    replacements["[BOTTOM_VERTICAL_BUFFER]"] = "";

    if(style_->horizontal_alignment == BlockWidgetStyle::PositionHint::LEFT)
        replacements["[RIGHT_HORIZONTAL_BUFFER]"] = horizontal_buffer_html_;
    else if (style_->horizontal_alignment == BlockWidgetStyle::PositionHint::RIGHT)
        replacements["[LEFT_HORIZONTAL_BUFFER]"] = horizontal_buffer_html_;
    else{
        replacements["[RIGHT_HORIZONTAL_BUFFER]"] = horizontal_buffer_html_;
        replacements["[LEFT_HORIZONTAL_BUFFER]"] = horizontal_buffer_html_;
    }

    if(style_->vertical_alignment == BlockWidgetStyle::PositionHint::TOP)
        replacements["[BOTTOM_VERTICAL_BUFFER]"] = vertical_buffer_html_;
    else if (style_->vertical_alignment == BlockWidgetStyle::PositionHint::BOTTOM)
        replacements["[TOP_VERTICAL_BUFFER]"] = vertical_buffer_html_;
    else{
        replacements["[TOP_VERTICAL_BUFFER]"] = vertical_buffer_html_;
        replacements["[BOTTOM_VERTICAL_BUFFER]"] = vertical_buffer_html_;
    }

    std::string out = raw_html_;
    TextProcessor::process(&out, replacements);
    return out;
}

