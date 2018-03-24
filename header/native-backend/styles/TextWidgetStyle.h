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
        unsigned int weight_;
        unsigned long color_;
        UnitValue<unsigned int> size_;
        std::string font_;

        TextWidgetStyle(unsigned int font_weight, unsigned long font_color, UnitValue<unsigned int> size,
                        std::string font);

    public:
        static boost::shared_ptr<TextWidgetStyle>
        createShared(unsigned int font_weight = 400,
                     unsigned long font_color = 0x0,
                     UnitValue<unsigned int> font_size = UnitValue<unsigned int>(1, "em"),
                     std::string font = R"("Times New Roman", Times, serif)");


        unsigned int setWeight(unsigned int weight);
        unsigned int getWeight();

        size_t setColor(unsigned long color);
        size_t getColor();

        UnitValue<unsigned int> getSize();
        UnitValue<unsigned int> setSize(UnitValue<unsigned int> size);

        std::string getFont();
        std::string setFont(std::string newFont);

    };
}


#endif //NATIVE_BACKEND_TEXTWIDGETSTYLE_H
