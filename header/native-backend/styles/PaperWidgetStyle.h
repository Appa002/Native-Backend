//
// Created by albert on 3/24/18.
//

#ifndef NATIVE_BACKEND_PAPERWIDGETSTYLE_H
#define NATIVE_BACKEND_PAPERWIDGETSTYLE_H

#include <boost/shared_ptr.hpp>
#include <iomanip>
#include <native-backend/utils/Types.h>
#include <native-backend/errors/errors.h>
#include <iostream>
#include <utility>

namespace nvb {
    class PaperWidgetStyle {
    private:
        unsigned long background_color_;
        UnitValue<unsigned int> width_;
        UnitValue<unsigned int> height_;

        PaperWidgetStyle(UnitValue<unsigned int> width,
                         UnitValue<unsigned int> height,
                         unsigned long background_color) : width_(std::move(width)),
                                                           height_(std::move(height)),
                                                           background_color_(background_color){}

    public:
        static boost::shared_ptr<PaperWidgetStyle> createShared(UnitValue<unsigned int> width,
                                                                UnitValue<unsigned int> height,
                                                                unsigned long backgroundColor) {
            return boost::shared_ptr<PaperWidgetStyle>(new PaperWidgetStyle(std::move(width), std::move(height), backgroundColor));
        }

        unsigned long getBackgroundColor() {
            return background_color_;
        }

        unsigned long setBackgroundColor(unsigned long backgroundColor) {
            if ((backgroundColor >> 24) == 0) {
                background_color_ = backgroundColor;
                return backgroundColor;
            } else {
                std::stringstream stream;
                stream << "0x" << std::hex << backgroundColor;
                std::string colorAsHex(stream.str());
                throw error::invalid_argument_error(
                        "The Background Color must be in the range of 0x0 to 0xffffff. Requested Background Color: " + colorAsHex);
            }
        }

        UnitValue<unsigned int> getWidth() {
            return width_;
        }

        UnitValue<unsigned int> getHeight() {
            return height_;
        }

        UnitValue<unsigned int> settWidth(UnitValue<unsigned int> val) {
            width_ = std::move(val);
            return width_;
        }

        UnitValue<unsigned int> setHeight(UnitValue<unsigned int> val) {
            height_ = std::move(val);
            return height_;
        }


    };
}

#endif //NATIVE_BACKEND_PAPERWIDGETSTYLE_H
