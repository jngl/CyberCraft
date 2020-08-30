//
// Created by jngl on 18/08/2020.
//
#include "Bloc.h"

const BlocInfo &getBlocInfo(Bloc bloc) {
    constexpr Color grassColorMain{50,150,25};
    constexpr Color grassColorDetail{50,125,25};
    constexpr Color stoneColorMain{50,55,52};
    constexpr Color stoneColorDetail{100,110,105};
    constexpr Color treeColor{25,85,12};
    constexpr Color transparent{0,0,0,0};
    constexpr Color waterColorMain{0, 134, 255};
    constexpr Color waterColorDetail{58, 163, 255};

    static constexpr BlocInfo GrassInfo = {
            component::Sprite {
                    math::Vector2i {5,0},
                    grassColorDetail,
                    grassColorMain
            },
            false
    };

    static constexpr BlocInfo StoneInfo = {
            component::Sprite {
                    math::Vector2i {6,13},
                    stoneColorDetail,
                    stoneColorMain
            },
            true
    };

    static constexpr BlocInfo WaterInfo = {
            component::Sprite {
                    math::Vector2i {7,0},
                    waterColorDetail,
                    waterColorMain
            },
            true
    };

    static constexpr BlocInfo AirInfo = {
            component::Sprite {
                math::Vector2i {0,0},
                transparent,
                transparent
            },
            false
    };

    static constexpr BlocInfo TreeBloc = {
            component::Sprite {
                math::Vector2i  {0, 1},
                treeColor,
                grassColorMain
            },
            true
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
        case Bloc::Tree:
            return TreeBloc;
        default:
            return AirInfo;
    }
}
