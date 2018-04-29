//
// Created by a_mod on 22.04.2018.
//

#ifndef NATIVE_BACKEND_REQUESTBUTTON_H
#define NATIVE_BACKEND_REQUESTBUTTON_H

#include <native-backend/widgets/IWidget.h>

namespace nvb {

    class FormSubmitButton : public nvb::IWidget {
    public:
        /*!\brief Injects the HTML code of the widget into the document at a given position.*/
        std::string build(std::string &, size_t) override;

        /*!\brief Injects the HTML code of the widget into the document at a given position.*/
        std::string build(std::string &&, size_t) override;

        /*!\brief Returns the size of the string which is going to be injected into the document.
         * This size will also include the HTML code of all children.*/
        size_t contentSize() override;

        /*!\brief Adds a child to the Widget and returns the widget to which the child has been added.
         * May be called multiple times on the same widget to add many children.*/
        boost::shared_ptr<IWidget> add(boost::shared_ptr<IWidget>) override;

        /*!\brief Takes an \c std::pair<std::string, boost::shared_ptr<void>> to set a property to the second value.*/
        boost::shared_ptr<IWidget> setProperty(std::pair<std::string, boost::shared_ptr<void>>) override;

        /*!\brief Generates the HTML code for the widget.*/
        boost::shared_ptr<IWidget> generateHtml() override;

        /*!\brief Updates every child in a tree.
         * Use this if you don't have a reference to the widget which state has changed.*/
        boost::shared_ptr<IWidget> updateAll() override;

        /*!\brief Injects required JS into the document.*/
        std::string buildJs(std::string &document, boost::shared_ptr<nvb::JSBundle> jsBundle) override;

        /*!\brief Injects required JS into the document.*/
        std::string buildJs(std::string &&document, boost::shared_ptr<nvb::JSBundle> jsBundle) override;

        static boost::shared_ptr<IWidget> createShared();

    private:
        bool contains_newest_state_ = false;

        const std::string template_html = R"(<button id=[ID]">I AM A BUTTON</button>)";
        const std::string template_js = R"(document.onload = function(){ document.getElementById([MYID]).oncLick = console.log(["[FORMID]"]) })";

        std::string generated_html_;
    };

}
#endif //NATIVE_BACKEND_REQUESTBUTTON_H
