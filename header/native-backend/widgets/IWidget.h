//
// Created by albert on 3/11/18.
//

#ifndef NATIVE_BACKEND_WIDGET_H
#define NATIVE_BACKEND_WIDGET_H

#include <boost/move/unique_ptr.hpp>
#include <string>
#include <boost/shared_ptr.hpp>

namespace nvb{
    /*!\brief Interface from which all Widgets inherit.
     * The \c build method is used by all Widgets to inject there html code into the document.*/
    class IWidget {
    private:
        boost::shared_ptr<IWidget> parent_ = boost::shared_ptr<IWidget>(nullptr);
        boost::shared_ptr<IWidget> shared_ptr_to_this = boost::shared_ptr<IWidget>(nullptr);

    public:
        virtual ~IWidget() = default;

        /*!\brief Injects the HTML code of the widget into the document at a given position.*/
        virtual std::string build(std::string&, size_t) = 0;
        /*!\brief Injects the HTML code of the widget into the document at a given position.*/
        virtual std::string build(std::string&&, size_t) = 0;
        /*!\brief Returns the size of the string which is going to be injected into the document.
         * This size will also include the HTML code of all children.*/
        virtual size_t contentSize() = 0;

        virtual boost::shared_ptr<IWidget> add(boost::shared_ptr<IWidget>) = 0;
        virtual boost::shared_ptr<IWidget> setProperty(std::pair<std::string, boost::shared_ptr<void>>) = 0;
        virtual boost::shared_ptr<IWidget> generateHtml() = 0;
        virtual boost::shared_ptr<IWidget> getParent() { return parent_; };
        virtual void setParent(boost::shared_ptr<IWidget> p) { parent_ = std::move(p); };
        virtual boost::shared_ptr<IWidget> getSharedPtrToThis() { return shared_ptr_to_this; };
        virtual void setSharedPtrToThis(boost::shared_ptr<IWidget> p) { shared_ptr_to_this = std::move(p); };

        virtual boost::shared_ptr<IWidget> updateState() {
            generateHtml();
            if(getParent().get() != nullptr)
                getParent()->updateState();
            return shared_ptr_to_this;
        }
    };
}




#endif //NATIVE_BACKEND_WIDGET_H
