//
// Created by albert on 3/24/18.
//

#ifndef NATIVE_BACKEND_RAWWIDGET_H
#define NATIVE_BACKEND_RAWWIDGET_H

#include <native-backend/widgets/IWidget.h>

namespace nvb{
    /*!\brief A widget which displays raw html.
     * It can take normal IWidgets as children by putting [CHILD] in the html
     * where you want the widget to be inserted. Use the \c add method to add the IWidgets.
     * You can have multiple children, they are inserted in order of being added via \c add.
     * To designate the position for multiple children but more then one [CHILD] token into the html.*/
    class RawWidget : public IWidget {
    private:
        const std::string template_html_;
        std::string generated_html_;
        std::vector<boost::shared_ptr<nvb::IWidget>> children_;
        bool contains_newest_state_ = false;

    public:
        explicit RawWidget(std::string);

        std::string build(std::string&, size_t) override;

        std::string build(std::string&&, size_t) override;

        size_t contentSize() override;

        boost::shared_ptr<IWidget> add(boost::shared_ptr<IWidget>) override;

        boost::shared_ptr<IWidget> setProperty(std::pair<std::string, boost::shared_ptr<void>>) override;

        boost::shared_ptr<IWidget> generateHtml() override;

        boost::shared_ptr<IWidget> updateAll() override;

        static boost::shared_ptr<nvb::IWidget> createShared(std::string);

    };
}



#endif //NATIVE_BACKEND_RAWWIDGET_H
