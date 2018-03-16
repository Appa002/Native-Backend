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
        const std::string raw_html;

    public:
        explicit TextWidget(std::string& text) : raw_html("<p>"+text+"</p>"){};
        explicit TextWidget(std::string&& text) : raw_html("<p>"+text+"</p>"){};

        /*!\brief Injects \c TextWidget::raw_html into the document at position \c pos.*/
        std::string build(std::string& document, size_t pos) override {
            return document.insert(pos, raw_html);
        }

        /*!\brief Injects \c TextWidget::raw_html into the document at position \c pos.*/
        std::string build(std::string&& document, size_t pos) override {
            return document.insert(pos, raw_html);
        }
    };
}


#endif //NATIVE_BACKEND_TEXTWIDGET_H
