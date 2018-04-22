//
// Created by albert on 3/25/18.
//

#ifndef NATIVE_BACKEND_CONTAINERWIDGET_H
#define NATIVE_BACKEND_CONTAINERWIDGET_H


#include <native-backend/widgets/IWidget.h>

namespace nvb{
    class ContainerWidget : public IWidget{
    public:
        boost::shared_ptr<IWidget> generateHtml() override;
        std::string build(std::string& document, size_t pos) override;
        std::string build(std::string&& document, size_t pos) override;
        size_t contentSize() override;
        boost::shared_ptr<IWidget> updateAll() override;
        boost::shared_ptr<IWidget> add(boost::shared_ptr<IWidget> widget) override;
        boost::shared_ptr<IWidget> setProperty(std::pair<std::string, boost::shared_ptr<void>>) override;

        /*!\brief Injects required JS into the document.*/
        std::string buildJs(std::string &document) override;

        /*!\brief Injects required JS into the document.*/
        std::string buildJs(std::string &&document) override;

        static boost::shared_ptr<IWidget> createShared();

    private:
        const std::string template_html_ = "<div> [INSERT] </div>";
        std::string generated_html_;
        bool html_contains_newest_state_ = false;
        std::vector<boost::shared_ptr<IWidget>> children_;
    };
}



#endif //NATIVE_BACKEND_CONTAINERWIDGET_H
