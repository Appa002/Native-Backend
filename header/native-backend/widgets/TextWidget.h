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
        const std::string template_html = "<span style=\"white-space: nowrap\">[INSERT]</span>";
        const std::string generated_html_;

        std::string generateHtml(std::string &text);

    public:
        explicit TextWidget(std::string& text);
        explicit TextWidget(std::string&& text);

        std::string build(std::string& document, size_t pos) override;
        std::string build(std::string&& document, size_t pos) override;

        size_t contentSize() override;

        static boost::shared_ptr<IWidget> createShared(std::string& text);
        static boost::shared_ptr<IWidget> createShared(std::string&& text);

    };
}


#endif //NATIVE_BACKEND_TEXTWIDGET_H
