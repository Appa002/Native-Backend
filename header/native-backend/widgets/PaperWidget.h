//
// Created by albert on 3/24/18.
//

#ifndef NATIVE_BACKEND_PAPERWIDGET_H
#define NATIVE_BACKEND_PAPERWIDGET_H

#include <native-backend/widgets/IWidget.h>
#include <native-backend/styles/PaperWidgetStyle.h>
#include <string>


namespace nvb {
    class PaperWidget : public IWidget {
    private:
        const std::string template_html_ = R"(<div style="display: inline-block; [WIDTH] [HEIGHT] background-color: [BACKGROUND_COLOR];">[INSERT]</div>)";
        std::string generated_html_;

        boost::shared_ptr<IWidget> child_;
        boost::shared_ptr<PaperWidgetStyle> style_;

        bool contains_newest_state_ = false;
    public:
        explicit PaperWidget(boost::shared_ptr<PaperWidgetStyle> style = PaperWidgetStyle::createShared(
                UnitValue<unsigned int>(0, ""),
                UnitValue<unsigned int>(0, ""),
                0x9ec3ff));

        std::string build(std::string &, size_t) override;

        std::string build(std::string &&, size_t) override;

        size_t contentSize() override;

        boost::shared_ptr<IWidget> add(boost::shared_ptr<IWidget>) override;

        boost::shared_ptr<IWidget> setProperty(std::pair<std::string, boost::shared_ptr<void>>) override;

        boost::shared_ptr<IWidget> generateHtml() override;

        boost::shared_ptr<IWidget> updateAll() override;

        static boost::shared_ptr<IWidget> createShared();
    };
}


#endif //NATIVE_BACKEND_PAPERWIDGET_H
