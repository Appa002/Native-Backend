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
    public:
        virtual ~IWidget() = default;

        /*!\brief Injects the HTML code of the widget into the document at a given position.*/
        virtual std::string build(std::string&, size_t) = 0;
        /*!\brief Injects the HTML code of the widget into the document at a given position.*/
        virtual std::string build(std::string&&, size_t) = 0;
        /*!\brief Returns the size of the string which is going to be injected into the document.
         * This size will also include the HTML code of all children.*/
        virtual size_t contentSize() = 0;
    };
}




#endif //NATIVE_BACKEND_WIDGET_H
