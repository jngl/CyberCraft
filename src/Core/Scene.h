//
// Created by jngl on 18/07/2020.
//

#ifndef CYBERCRAFT_SCENE_H
#define CYBERCRAFT_SCENE_H

#include "Update.h"

#include "entt/entt.h"

using Entity = entt::entity;

class Scene {
public:
    Entity create();

    template<typename Component, typename... Args>
    decltype(auto) emplace(Entity entity, Args &&... args) {
        return m_registry.emplace<Component>(entity);
    }

    template<typename... Component>
    auto view() {
        return m_registry.view<Component...>();
    }

private:
    entt::registry m_registry;
};


#endif //CYBERCRAFT_SCENE_H
