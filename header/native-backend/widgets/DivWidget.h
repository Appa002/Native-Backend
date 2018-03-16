//
// Created by albert on 3/16/18.
//

#ifndef NATIVE_BACKEND_DIVWIDGET_H
#define NATIVE_BACKEND_DIVWIDGET_H


#include <native-backend/widgets/IWidget.h>
#include <string>
#include <boost/move/unique_ptr.hpp>

namespace nvb{

    /*!\brief DEPRECATED used for testing only*/
    class DivWidget : public IWidget {
    private:
        const std::string raw_html_ = "<div></div>";
        const boost::movelib::unique_ptr<nvb::IWidget> child_;

    public:
        explicit DivWidget(nvb::IWidget* child) : child_(boost::movelib::unique_ptr<IWidget>(child)) {};

        std::string build(std::string& document, size_t pos) {
            document = document.insert(pos, raw_html_);
            return child_->build(document, pos + 5);
        };

        std::string build(std::string&& document, size_t pos) {
            document = document.insert(pos, raw_html_);
            return child_->build(document, pos + 5);
        };
    };
}



#endif //NATIVE_BACKEND_DIVWIDGET_H
