//
// Created by albert on 3/16/18.
//

#ifndef NATIVE_BACKEND_BLOCKVIEWWIDGET_H
#define NATIVE_BACKEND_BLOCKVIEWWIDGET_H


#include <native-backend/widgets/IWidget.h>
#include <string>
#include <boost/move/unique_ptr.hpp>
#include <native-backend/styles/BlockViewWidgetStyle.h>
#include <boost/shared_ptr.hpp>

namespace nvb{
    /*!\brief Widget which shrinks to fit its content and is supposed to be used for aligning widgets.
     * Use a instance of \c BlockWidgetStyle to define the position to where it should align.*/
    class BlockViewWidget : public IWidget {
    private:
        const std::string template_html_ = "<div style=\"display: flex; flex-direction: row; width: 100%; height: 100%;\">"
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

        boost::shared_ptr<nvb::IWidget> child_;
        boost::shared_ptr<nvb::BlockViewWidgetStyle> style_;
        std::string generated_html_ = "";
        bool html_contains_newest_state = false;

    public:
        explicit BlockViewWidget(boost::shared_ptr<BlockViewWidgetStyle> style =
                                            boost::shared_ptr<BlockViewWidgetStyle>(new BlockViewWidgetStyle()));

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
    };
}



#endif //NATIVE_BACKEND_BLOCKVIEWWIDGET_H
