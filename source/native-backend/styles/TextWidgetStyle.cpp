#include <native-backend/styles/TextWidgetStyle.h>

nvb::TextWidgetStyle::TextWidgetStyle(unsigned int font_weight, unsigned long font_color,
                                      nvb::UnitValue<unsigned int> size, std::string font) :
        weight_(setWeight(font_weight)), color_(setColor(font_color)),
        size_(std::move(size)), font_(std::move(font)) {}



unsigned int nvb::TextWidgetStyle::setWeight(unsigned int weight) {
    if (weight % 100 == 0 && weight >= 100 && weight <= 900) {
        weight_ = weight;
        return weight;
    } else {
        throw error::invalid_argument_error(
                "The font weight must either be 100, 200, 300, 400, 500, 600, 700, 800 or 900. Requested weight: " +
                std::to_string(weight));
    }

}

size_t nvb::TextWidgetStyle::setColor(unsigned long color) {
    if ((color >> 24) == 0) {
        color_ = color;
        return color;
    } else {
        std::stringstream stream;
        stream << "0x" << std::hex << color;
        std::string colorAsHex(stream.str());
        throw error::invalid_argument_error(
                "The Color must be in the range of 0x0 to 0xffffff. Requested color: " + colorAsHex);

    }
}

nvb::UnitValue<unsigned int> nvb::TextWidgetStyle::setSize(UnitValue<unsigned int> size) {
    size_ = size;
    return size;
}

unsigned int nvb::TextWidgetStyle::getWeight() {
    return weight_;
}

size_t nvb::TextWidgetStyle::getColor() {
    return color_;
}

nvb::UnitValue<unsigned int> nvb::TextWidgetStyle::getSize() {
    return size_;
}


boost::shared_ptr<nvb::TextWidgetStyle>
nvb::TextWidgetStyle::createShared(unsigned int font_weight, unsigned long font_color,
                                   nvb::UnitValue<unsigned int> font_size, std::string font) {


    return boost::shared_ptr<TextWidgetStyle>(
            new TextWidgetStyle(font_weight, font_color, std::move(font_size), std::move(font)));


}

std::string nvb::TextWidgetStyle::getFont() {
    return font_;
}

std::string nvb::TextWidgetStyle::setFont(std::string newFont) {
    font_ = newFont;
    return font_;
};
