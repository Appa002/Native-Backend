//
// Created by albert on 3/16/18.
//

#ifndef NATIVE_BACKEND_LISTVIEWWIDGET_H
#define NATIVE_BACKEND_LISTVIEWWIDGET_H


#include <string>
#include <boost/move/unique_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <unordered_map>

#include <native-backend/styles/BlockViewWidgetStyle.h>
#include <native-backend/widgets/IWidget.h>


namespace nvb{

    /*!\brief Widget which orders its children in a list next to each other.
     * Give it a \c std::vector<IWidget> with the children to align; this can be a rValue reference
     * so one can create the vector using {} in the arguments of \c createShared,*/
    class ListViewWidget : public IWidget {
    private:
        const std::string template_html_ =
                "<div style=\"display: flex; flex-direction: column;\">"
                "[INSERT]"
                "</div>";

        std::vector<boost::shared_ptr<IWidget>> children_;
        bool html_contains_newest_state = false;
        std::string generated_html_;
    public:
        explicit ListViewWidget() = default;

        std::string build(std::string& document, size_t pos) override;
        std::string build(std::string&& document, size_t pos) override;
        boost::shared_ptr<IWidget> add(boost::shared_ptr<IWidget> widget) override;
        boost::shared_ptr<IWidget> setProperty(std::pair<std::string, boost::shared_ptr<void>>) override;
        boost::shared_ptr<IWidget> generateHtml() override;

        size_t contentSize() override;


        static boost::shared_ptr<nvb::IWidget> createShared();
    };
}



#endif //NATIVE_BACKEND_LISTVIEWWIDGET_H
