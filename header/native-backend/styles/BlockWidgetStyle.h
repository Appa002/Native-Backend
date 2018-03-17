//
// Created by albert on 3/17/18.
//

#ifndef NATIVE_BACKEND_BLOCKWIDGETSTYLE_H
#define NATIVE_BACKEND_BLOCKWIDGETSTYLE_H

namespace nvb {
    /*!\brief Class which holds information for styling \c BlockWidget 's.*/
    class BlockWidgetStyle {
    public:
        /*!\brief Type used to define the position to where the \c BlockWidget should float to.*/
        enum class PositionHint{
            TOP,
            CENTER,
            BOTTOM,
            LEFT,
            RIGHT
        };

        /*!\brief Defines where the \c BlockWidget should float to on the X-Axis.
         * Expected values: \c PositionHint::LEFT \c PositionHint::RIGHT \c PositionHint::CENTER.
         * Example: If the value PositionHint::LEFT is passed the \c BlockWidget will go as far to the left in its container as possible.*/
        const PositionHint horizontal_alignment;

        /*!\brief Defines where the \c BlockWidget should float to on the Y-Axis.
         * Expected values: \c PositionHint::TOP \c PositionHint::BOTTOM \c PositionHint::CENTER.
         * Example: If the value PositionHint::TOP is passed the \c BlockWidget will go as high in its container as possible.*/
        const PositionHint vertical_alignment;


        explicit BlockWidgetStyle(PositionHint _horizontal_alignment=PositionHint::LEFT,
                        PositionHint _vertical_alignment=PositionHint::TOP) :
                horizontal_alignment(_horizontal_alignment),
                vertical_alignment(_vertical_alignment) {}
        
    };
}


#endif //NATIVE_BACKEND_BLOCKWIDGETSTYLE_H
