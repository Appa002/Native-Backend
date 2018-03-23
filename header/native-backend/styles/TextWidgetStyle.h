//
// Created by albert on 3/23/18.
//

#ifndef NATIVE_BACKEND_TEXTWIDGETSTYLE_H
#define NATIVE_BACKEND_TEXTWIDGETSTYLE_H

#include <boost/shared_ptr.hpp>
#include <utility>
#include <native-backend/errors/errors.h>
#include <native-backend/utils/Types.h>
#include <iomanip>

namespace nvb {
    class TextWidgetStyle {
    private:
        unsigned int font_weight_;
        unsigned long color_;
        UnitValue<unsigned int> size_;

        TextWidgetStyle(unsigned int font_weight, unsigned long font_color, UnitValue<unsigned int> size) :
                font_weight_(setFontWeight(font_weight)), color_(setColor(font_color)), size_(std::move(size)) {};

    public:

        static boost::shared_ptr<TextWidgetStyle> createShared(unsigned int font_weight = 400,
                                                               unsigned long font_color = 0x0,
                                                               UnitValue<unsigned int> font_size =
                                                                    UnitValue<unsigned int>(1, "em")) {

            return boost::shared_ptr<TextWidgetStyle>(new TextWidgetStyle(font_weight, font_color, std::move(font_size)));
        }

        unsigned int setFontWeight(unsigned int weight);
        size_t setColor(unsigned long color);
        UnitValue<unsigned int> setSize(UnitValue<unsigned int> size);

        unsigned int getFontWeight();
        size_t getColor();
        UnitValue<unsigned int> getSize();

    };
}

unsigned int nvb::TextWidgetStyle::setFontWeight(unsigned int weight) {
    if (weight % 100 == 0 && weight >= 100 && weight <= 900) {
        font_weight_ = weight;
        return weight;
    } else{
        throw error::invalid_argument_error("The font weight must either be 100, 200, 300, 400, 500, 600, 700, 800 or 900. Requested weight: " + std::to_string(weight));
    }

}

size_t nvb::TextWidgetStyle::setColor(unsigned long color) {
    if((color >> 24) == 0){
        color_ = color;
        return color;
    }else{
        std::stringstream stream;
        stream << "0x" << std::hex << color;
        std::string colorAsHex( stream.str() );
        throw error::invalid_argument_error("The Color must be in the range of 0x0 to 0xffffff. Requested color: " + colorAsHex);

    }
}

nvb::UnitValue<unsigned int> nvb::TextWidgetStyle::setSize(UnitValue<unsigned int> size) {
    size_ = size;
    return size;
}

unsigned int nvb::TextWidgetStyle::getFontWeight() {
    return font_weight_;
}

size_t nvb::TextWidgetStyle::getColor() {
    return color_;
}

nvb::UnitValue<unsigned int> nvb::TextWidgetStyle::getSize() {
    return size_;
}


#endif //NATIVE_BACKEND_TEXTWIDGETSTYLE_H
