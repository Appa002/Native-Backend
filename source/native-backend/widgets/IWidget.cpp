//
// Created by albert on 3/22/18.
//

#include <native-backend/widgets/IWidget.h>

boost::shared_ptr<nvb::IWidget> nvb::IWidget::getParent() {
    return parent_;
}

void nvb::IWidget::setParent(boost::shared_ptr<nvb::IWidget> p) {
    parent_ = std::move(p);
}

boost::shared_ptr<nvb::IWidget> nvb::IWidget::getSharedPtrToThis() {
    return shared_ptr_to_this;
}

void nvb::IWidget::setSharedPtrToThis(boost::shared_ptr<nvb::IWidget> p) {
    shared_ptr_to_this = std::move(p);
}

boost::shared_ptr<nvb::IWidget> nvb::IWidget::updateLeast() {
    generateHtml();
    if(getParent().get() != nullptr)
        getParent()->updateLeast();
    return shared_ptr_to_this;
}
