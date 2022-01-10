//
// Created by jngl on 18/08/2020.
//

#ifndef CYBERCRAFT_BLOC_H
#define CYBERCRAFT_BLOC_H

#include "Component.h"

enum class BlocGroup{
    Grass,
    Stone,
    Water,
    Tree
};

enum class Bloc{
    Grass,
    LongGrass,
    Stone,
    Water,
    WaterGrassSouth,
    WaterGrassNorth,
    WaterGrassLeft,
    WaterGrassRight,
    WaterGrassNorthRight,
    WaterGrassNorthLeft,
    WaterGrassSouthLeft,
    WaterGrassSouthRight,
    Tree
};

struct BlocGroupInfo
{
    std::string_view name;
    bool collision = false;
};

struct BlocInfo {
    std::string_view name;
    component::Sprite sprite;
    BlocGroup group;
};

constexpr cc::Color grassColorMain{45,155,13};
constexpr cc::Color grassColorDetail{3,249,41};
constexpr cc::Color stoneColorMain{176, 176, 176};
constexpr cc::Color transparent{0,0,0,0};
constexpr cc::Color waterColorMain{33, 105, 197};

constexpr std::array<BlocGroupInfo, 4> g_blocGroupArray{
        BlocGroupInfo{
                "Grass",
                false
        },
        BlocGroupInfo{
                "Stone",
                true
        },
        BlocGroupInfo{
                "Water",
                true
        },
        BlocGroupInfo{
                "Tree",
                true
        }
};

constexpr const BlocGroupInfo& getBlocGroupInfo(BlocGroup group){
    auto index = static_cast<size_t>(group);
    return g_blocGroupArray.at(index);
}

constexpr std::array<BlocInfo, 13> g_blocInfoArray{
        BlocInfo{
                "Grass",
                component::Sprite {
                        cc::Vector2i {3,0},
                        transparent,
                        grassColorMain
                },
                BlocGroup::Grass
        },
        BlocInfo{
                "LongGrass",
                component::Sprite {
                        cc::Vector2i {3,0},
                        grassColorMain,
                        grassColorDetail
                },
                BlocGroup::Grass
        },
        BlocInfo{
                "Stone",
                component::Sprite {
                        cc::Vector2i {5,0},
                        grassColorMain,
                        stoneColorMain
                },
                BlocGroup::Stone
        },
        BlocInfo{
                "Water",
                component::Sprite {
                        cc::Vector2i {7,0},
                        transparent,
                        waterColorMain
                },
                BlocGroup::Water
        },
        BlocInfo{
                "WaterGrassSouth",
                component::Sprite {
                    cc::Vector2i  {1, 0},
                    grassColorMain,
                    waterColorMain,
                    180
                },
                BlocGroup::Water
        },
        BlocInfo{
                "WaterGrassNorth",
                component::Sprite {
                        cc::Vector2i  {1, 0},
                        grassColorMain,
                        waterColorMain,
                        0
                },
                BlocGroup::Water
        },
        BlocInfo{
                "WaterGrassLeft",
                component::Sprite {
                        cc::Vector2i  {1, 0},
                        grassColorMain,
                        waterColorMain,
                        -90
                },
                BlocGroup::Water
        },
        BlocInfo{
                "WaterGrassRight",
                component::Sprite {
                        cc::Vector2i  {1, 0},
                        grassColorMain,
                        waterColorMain,
                        90
                },
                BlocGroup::Water
        },BlocInfo{
                "WaterGrassNorthRight",
                component::Sprite {
                        cc::Vector2i  {2, 0},
                        grassColorMain,
                        waterColorMain,
                        0
                },
                BlocGroup::Water
        },BlocInfo{
                "WaterGrassNorthLeft",
                component::Sprite {
                        cc::Vector2i  {2, 0},
                        grassColorMain,
                        waterColorMain,
                        -90
                },
                BlocGroup::Water
        },BlocInfo{
                "WaterGrassSouthLeft",
                component::Sprite {
                        cc::Vector2i  {2, 0},
                        grassColorMain,
                        waterColorMain,
                        180
                },
                BlocGroup::Water
        },BlocInfo{
                "WaterGrassSouthRight",
                component::Sprite {
                        cc::Vector2i  {2, 0},
                        grassColorMain,
                        waterColorMain,
                        90
                },
                BlocGroup::Water
        },
        BlocInfo{
                "Tree",
                component::Sprite {
                        cc::Vector2i  {4, 0},
                        grassColorMain,
                        grassColorDetail
                },
                BlocGroup::Water
        }
};

constexpr const BlocInfo& getBlocInfo(Bloc bloc){
    auto index = static_cast<size_t>(bloc);
    return g_blocInfoArray.at(index);
}

#endif //CYBERCRAFT_BLOC_H
