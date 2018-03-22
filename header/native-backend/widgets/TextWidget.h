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
    public:
        std::string text;
        explicit TextWidget(std::string& text);
        explicit TextWidget(std::string&& text);

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
        const std::string template_html = "<span style=\"white-space: nowrap\">[INSERT]</span>";
        std::string generated_html_;

    };
}


#endif //NATIVE_BACKEND_TEXTWIDGET_H
