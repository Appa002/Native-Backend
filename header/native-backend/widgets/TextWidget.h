//
// Created by albert on 3/16/18.
//

#ifndef NATIVE_BACKEND_TEXTWIDGET_H
#define NATIVE_BACKEND_TEXTWIDGET_H

#include <native-backend/widgets/IWidget.h>
#include <string>

namespace nvb{
    /*!\brief Basic Widget which takes no children and shows simple text on screen.*/
    class TextWidget : public IWidget {
    private:
        const std::string raw_html = "<span style=\"white-space: nowrap\">[INSERT]</span>";
        const std::string text;
    public:
        explicit TextWidget(std::string& text) : text(text) {};
        explicit TextWidget(std::string&& text) : text(text) {};

        /*!\brief Injects \c TextWidget::raw_html into the document at position \c pos.*/
        std::string build(std::string& document, size_t pos) override {
            size_t pos_change = raw_html.find_first_of("[INSERT]");
            std::string insert_html = raw_html;
            insert_html = insert_html.replace(pos_change, 8, "");
            insert_html = insert_html.insert(pos_change, text);
            return document.insert(pos, insert_html);
        }

        /*!\brief Injects \c TextWidget::raw_html into the document at position \c pos.*/
        std::string build(std::string&& document, size_t pos) override {
            size_t pos_change = raw_html.find_first_of("[INSERT]");
            std::string insert_html = raw_html;
            insert_html = insert_html.replace(pos_change, 8, "");
            insert_html = insert_html.insert(pos_change, text);
            return document.insert(pos, insert_html);
        }
    };
}


#endif //NATIVE_BACKEND_TEXTWIDGET_H
