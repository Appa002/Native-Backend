//
// Created by albert on 3/11/18.
//

#ifndef NATIVE_BACKEND_WIDGET_H
#define NATIVE_BACKEND_WIDGET_H

#include <boost/move/unique_ptr.hpp>
#include <string>

namespace nvb{
    /*!\brief Interface from which all Widgets inherits.
     * The \c build method is used by all Widgets to inject there html code into the document.*/
    class IWidget {
    public:
        virtual ~IWidget() = default;
        virtual std::string build(std::string&, size_t) = 0;
        virtual std::string build(std::string&&, size_t) = 0;
    };
}




#endif //NATIVE_BACKEND_WIDGET_H
