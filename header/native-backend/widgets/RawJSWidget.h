//
// Created by a_mod on 02.05.2018.
//

#ifndef NATIVE_BACKEND_RAWJS_H
#define NATIVE_BACKEND_RAWJS_H


//
// Created by albert on 3/24/18.
//

#include <native-backend/widgets/IWidget.h>

namespace nvb{
    /*!\brief A widget which displays raw html.
     * It can take normal IWidgets as children by putting [CHILD] in the html
     * where you want the widget to be inserted. Use the \c add method to add the IWidgets.
     * You can have multiple children, they are inserted in order of being added via \c add.
     * To designate the position for multiple children but more then one [CHILD] token into the html.*/
    class RawJSWidget : public IWidget {
    private:
        const std::string javascript;
        bool contains_newest_state_= false;
        std::vector<boost::shared_ptr<nvb::IWidget>> children_;
        std::string generated_html_;

    public:
        explicit RawJSWidget(std::string);

        std::string build(std::string&, size_t) override;

        std::string build(std::string&&, size_t) override;

        size_t contentSize() override;

        boost::shared_ptr<IWidget> add(boost::shared_ptr<IWidget>) override;

        boost::shared_ptr<IWidget> setProperty(std::pair<std::string, boost::shared_ptr<void>>) override;

        boost::shared_ptr<IWidget> generateHtml() override;

        boost::shared_ptr<IWidget> updateAll() override;

        /*!\brief Injects required JS into the document.*/
        std::string buildJs(std::string &document, boost::shared_ptr<JSBundle> jsBundle) override;
        /*!\brief Injects required JS into the document.*/
        std::string buildJs(std::string &&document, boost::shared_ptr<JSBundle> jsBundle) override;

        static boost::shared_ptr<nvb::IWidget> createShared(std::string);

    };
}


#endif //NATIVE_BACKEND_RAWJS_H
