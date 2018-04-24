//
// Created by a_mod on 22.04.2018.
//

#ifndef NATIVE_BACKEND_FORMWRAPPER_H
#define NATIVE_BACKEND_FORMWRAPPER_H

#include <native-backend/widgets/IWidget.h>
#include <native-backend/server/HttpVerb.h>

namespace nvb{

    enum class FormWrapperWidgetTarget{
        Self,
        NewTab
    };

    class FormWrapperWidget : public IWidget{
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
        std::string buildJs(std::string &document, boost::shared_ptr<JSBundle> jsBundle) override;

        /*!\brief Injects required JS into the document.*/
        std::string buildJs(std::string &&document, boost::shared_ptr<JSBundle> jsBundle) override;

        static boost::shared_ptr<IWidget> createShared(std::string action, HttpVerb::Verb method, FormWrapperWidgetTarget target);

    private:

        FormWrapperWidget(std::string, HttpVerb::Verb, FormWrapperWidgetTarget);
        const std::string template_html = R"(<form action="[ACTION]" method="[METHOD]" target="[TARGET]" id="[ID]">[INSERT]</form>)";
        std::string generated_html_;
        bool contains_newest_state_ = false;
        std::vector<boost::shared_ptr<IWidget>> children_;

        HttpVerb::Verb method = HttpVerb::Verb::get;
        FormWrapperWidgetTarget target = FormWrapperWidgetTarget::Self;
        std::string action = "/";
    };

}


#endif //NATIVE_BACKEND_FORMWRAPPER_H
