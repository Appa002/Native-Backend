//
// Created by albert on 3/16/18.
//

#ifndef NATIVE_BACKEND_TEXTWIDGET_H
#define NATIVE_BACKEND_TEXTWIDGET_H

#include <native-backend/widgets/IWidget.h>
#include <string>
#include <native-backend/styles/TextWidgetStyle.h>
#include <unordered_map>

namespace nvb{
    /*!\brief Basic Widget which takes no children and shows simple text on screen.*/
    class TextWidget : public IWidget {
    public:
        std::string text;
        boost::shared_ptr<nvb::TextWidgetStyle> style;

        std::string build(std::string& document, size_t pos) override;
        std::string build(std::string&& document, size_t pos) override;

        boost::shared_ptr<IWidget> generateHtml() override;
        size_t contentSize() override;
        boost::shared_ptr<IWidget> add(boost::shared_ptr<IWidget> widget) override;
        boost::shared_ptr<IWidget> setProperty(std::pair<std::string, boost::shared_ptr<void>>) override;
        boost::shared_ptr<IWidget> updateAll() override;


        static boost::shared_ptr<IWidget> createShared(std::string& text);

        static boost::shared_ptr<IWidget> createShared(std::string&& text);

    private:
        explicit TextWidget(std::string& text, boost::shared_ptr<nvb::TextWidgetStyle> style =
                    TextWidgetStyle::createShared());

        explicit TextWidget(std::string&& text, boost::shared_ptr<nvb::TextWidgetStyle> style =
                    TextWidgetStyle::createShared());

        const std::string template_html = "<span style=\"white-space: nowrap; font-weight: [WEIGHT]; font-size: [SIZE]; color: [COLOR]; font-family: [FONT];\">[INSERT]</span>";
        std::string generated_html_;

    };
}


#endif //NATIVE_BACKEND_TEXTWIDGET_H
