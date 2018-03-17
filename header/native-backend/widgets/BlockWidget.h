//
// Created by albert on 3/16/18.
//

#ifndef NATIVE_BACKEND_BLOCKWIDGET_H
#define NATIVE_BACKEND_BLOCKWIDGET_H


#include <native-backend/widgets/IWidget.h>
#include <string>
#include <boost/move/unique_ptr.hpp>
#include <native-backend/styles/BlockWidgetStyle.h>

namespace nvb{
    /*!\brief Widget which shrinks to fit its content and is supposed to be used for aligning widgets.
     * Use a instance of \c BlockWidgetStyle to define the position to where it should align.*/
    class BlockWidget : public IWidget {
    private:
        const std::string raw_html_ = "<div style=\"display: flex; flex-direction: row; width: 100%; height: 100%;\">"
                " [LEFT_HORIZONTAL_BUFFER] "

                "<div style=\"display: flex; flex-direction: column;\">"
                    " [TOP_VERTICAL_BUFFER] "
                    " [INSERT] "
                    " [BOTTOM_VERTICAL_BUFFER] "
                "</div>"

                " [RIGHT_HORIZONTAL_BUFFER] "
                "</div>";

        const std::string horizontal_buffer_html_ = "<div style=\"width: 100vw\"></div>";
        const std::string vertical_buffer_html_ = "<div style=\"height: 100vh\"></div>";

        const boost::movelib::unique_ptr<nvb::IWidget> child_;
        const boost::movelib::unique_ptr<nvb::BlockWidgetStyle> style_;
        const std::string injection_html_;

        std::string createHtml();

    public:
        explicit BlockWidget(nvb::IWidget* child, BlockWidgetStyle* style = new BlockWidgetStyle());

        std::string build(std::string& document, size_t pos);
        std::string build(std::string&& document, size_t pos);
    };
}



#endif //NATIVE_BACKEND_BLOCKWIDGET_H
