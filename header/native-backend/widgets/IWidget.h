//
// Created by albert on 3/11/18.
//

#ifndef NATIVE_BACKEND_WIDGET_H
#define NATIVE_BACKEND_WIDGET_H

#include <boost/move/unique_ptr.hpp>
#include <string>
#include <boost/shared_ptr.hpp>
#include <native-backend/packaging/JSBundle.h>

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

        /*!\brief Adds a child to the Widget and returns the widget to which the child has been added.
         * May be called multiple times on the same widget to add many children.*/
        virtual boost::shared_ptr<IWidget> add(boost::shared_ptr<IWidget>) = 0;

        /*!\brief Takes an \c std::pair<std::string, boost::shared_ptr<void>> to set a property to the second value.*/
        virtual boost::shared_ptr<IWidget> setProperty(std::pair<std::string, boost::shared_ptr<void>>) = 0;

        /*!\brief Generates the HTML code for the widget.*/
        virtual boost::shared_ptr<IWidget> generateHtml() = 0;

        /*!\brief Updates every child in a tree.
         * Use this if you don't have a reference to the widget which state has changed.*/
        virtual boost::shared_ptr<IWidget> updateAll() = 0;

        /*!\brief Injects required JS into the document.*/
        virtual std::string buildJs(std::string &document, boost::shared_ptr<JSBundle> jsBundle) = 0;

        /*!\brief Injects required JS into the document.*/
        virtual std::string buildJs(std::string &&document, boost::shared_ptr<JSBundle> jsBundle) = 0;

        /*!\brief Returns the Widgets parent.*/
        virtual boost::shared_ptr<IWidget> getParent();

        /*!\brief Returns a \c boost::shared_ptr<IWidget> which points to the widget's this.*/
        virtual boost::shared_ptr<IWidget> getSharedPtrToThis();

        /*!\brief Only updates the widgets parent and it's parent.
         * Use this if you have a reference to the widget which state has been changed.*/
        virtual boost::shared_ptr<IWidget> updateLeast();

        /*!\brief Sets the widgets parent.*/
        virtual void setParent(boost::shared_ptr<IWidget> p);

        /*!\brief Sets sharedPtrToThis*/
        virtual void setSharedPtrToThis(boost::shared_ptr<IWidget> p);


    };
}




#endif //NATIVE_BACKEND_WIDGET_H
