//
// Created by jngl on 18/08/2020.
//

#ifndef CYBERCRAFT_BLOC_H
#define CYBERCRAFT_BLOC_H

#include "Component.h"
#include <Core/Error.h>

struct BlocGroup
{
    std::string_view name;
    bool collision = false;
};

struct BlocInfo {
    std::string_view name;
    component::Sprite sprite;
    const BlocGroup& group;
};

constexpr Color grassColorMain{45,155,13};
constexpr Color grassColorDetail{3,249,41};
constexpr Color stoneColorMain{176, 176, 176};
constexpr Color transparent{0,0,0,0};
constexpr Color waterColorMain{33, 105, 197};

constexpr std::array<BlocGroup, 4> g_blocGroupArray{
        BlocGroup{
                "Grass",
                false
        },
        BlocGroup{
                "Stone",
                true
        },
        BlocGroup{
                "Water",
                true
        },
        BlocGroup{
                "Tree",
                true
        }
};

constexpr const BlocGroup& getBlocGroup(std::string_view name){
    const BlocGroup* result = nullptr;
    for(const BlocGroup& group: g_blocGroupArray) {
        if (group.name == name) {
            result = &group;
        }
    }
    if(!result){
        throw Error("Bloc group not found");
    }
    return *result;
}

constexpr std::array<BlocInfo, 5> g_blocInfoArray{
        BlocInfo{
                "Grass",
                component::Sprite {
                        math::Vector2i {3,0},
                        transparent,
                        grassColorMain
                },
                getBlocGroup("Grass")
        },
        BlocInfo{
                "LongGrass",
                component::Sprite {
                        math::Vector2i {3,0},
                        grassColorMain,
                        grassColorDetail
                },
                getBlocGroup("Grass")
        },
        BlocInfo{
                "Stone",
                component::Sprite {
                        math::Vector2i {5,0},
                        grassColorMain,
                        stoneColorMain
                },
                getBlocGroup("Stone")
        },
        BlocInfo{
                "Water",
                component::Sprite {
                        math::Vector2i {7,0},
                        transparent,
                        waterColorMain
                },
                getBlocGroup("Water")
        },
        BlocInfo{
                "Tree",
                component::Sprite {
                        math::Vector2i  {4, 0},
                        grassColorMain,
                        grassColorDetail
                },
                getBlocGroup("Tree")
        }
};

constexpr const BlocInfo& getBlocInfo(std::string_view name){
    const BlocInfo* result = nullptr;
    for(const BlocInfo& blocInfo : g_blocInfoArray){
        if(name == blocInfo.name){
            result  = &blocInfo;
        }
    }
    if(!result){
        throw Error("Bloc info not found");
    }
    return *result;
}

#endif //CYBERCRAFT_BLOC_H
