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

    /*!\brief Holds styling information for \c TextWidget 's.*/
    class TextWidgetStyle {
    private:
        /*!\brief The Weight of the text.
         * Must either be 100, 200, 300, 400, 500, 600, 700, 800 or 900.*/
        unsigned int weight_;

        /*!\brief The Color of the text.
         * Must be in range 0x0 to 0xffffff.*/
        unsigned long color_;

        /*!\brief The size of the text.*/
        UnitValue<unsigned int> size_;

        /*!\brief The font of the text.
         * Enter like you would in normal css, for instance:
         * Times New Roman", Times, serif. See https://www.w3schools.com/css/css_font.asp for information.*/
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

        /*!\brief Sets the color. It's recommended to enter the color as a hex value like 0x2159b2 (this is dark blue).*/
        size_t setColor(unsigned long color);
        size_t getColor();

        UnitValue<unsigned int> getSize();
        UnitValue<unsigned int> setSize(UnitValue<unsigned int> size);

        std::string getFont();
        std::string setFont(std::string newFont);

    };
}


#endif //NATIVE_BACKEND_TEXTWIDGETSTYLE_H
