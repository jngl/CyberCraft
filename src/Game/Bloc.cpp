//
// Created by jngl on 18/08/2020.
//
#include "Bloc.h"

const BlocInfo &getBlocInfo(Bloc bloc) {
    static constexpr BlocInfo GrassInfo = {
            component::Sprite {
                    math::Vector2i {5,0},
                    Color{50,125,25},
                    Color{50,150,25}
            },
            false
    };

    static constexpr BlocInfo StoneInfo = {
            component::Sprite {
                    math::Vector2i {6,13},
                    Color{100,110,105},
                    Color{50,55,52}
            },
            true
    };

    static constexpr BlocInfo WaterInfo = {
            component::Sprite {
                    math::Vector2i {7,0},
                    Color{58,163,255},
                    Color{0,134,255}
            },
            true
    };

    static constexpr BlocInfo AirInfo = {
            component::Sprite {
                math::Vector2i {0,0},
                Color{0,0,0,0},
                Color{0,0,0,0}
            },
            false
    };

    switch (bloc) {
        case Bloc::Grass:
            return GrassInfo;
        case Bloc::Stone:
            return StoneInfo;
        case Bloc::Water:
            return WaterInfo;
        case Bloc::Air:
            return AirInfo;
        default:
            return GrassInfo;
    }
}
