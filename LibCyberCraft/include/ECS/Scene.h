//
// Created by jngl on 18/07/2020.
//

#ifndef CYBERCRAFT_SCENE_H
#define CYBERCRAFT_SCENE_H

#include <Core/Common.h>
#include "Range.h"
#include "Basic.h"

#include <unordered_map>
#include <vector>
#include <memory>
#include <array>

struct Entity{
    Uint32 id;
};

struct GenericComponentManager{
    virtual ~GenericComponentManager() = default;
};

class Scene;
/*
template <class T>
class ComponentManager : public GenericComponentManager {
public:

    T& create(Entity e){
        if(m_components.size() < e.id){
            m_components.resize(e.id, {});
            m_created.resize(e.id, false);
        }

        m_created[e.id-1] = true;

        return m_components[e.id-1];
    }

    T* get(Entity e){
        if(!m_created[e.id-1]){
            return nullptr;
        }

        return &m_components[e.id-1];
    }

private:
    std::vector<T> m_components;
    std::vector<bool> m_created;
};
*/
class Scene
{
public:
    /*[[nodiscard]] int numberOfEntity() const;
    [[nodiscard]] int numberOfComponentType() const;

    Entity createEntity();

    template<class T>
    T& createComponent(Entity e) {
        return getManager<T>().create(e);
    }


    template<class T>
    T* getComponent(Entity e) {
        return getManager<T>().get(e);
    }

    template<class... Args>
    Range allEntityWith(){
        std::vector<Uint32> arrayId;
        genArrayId<Args...>(arrayId);
        return Range(*this, std::move(arrayId));
    }

private:
    Uint32 m_numberOfEntity = 0;
    std::unordered_map<Uint32, std::unique_ptr<GenericComponentManager>> m_manager;

    template<class T>
    ComponentManager<T>& getManager() {
        Uint32 id = getTypeId<T>();

        auto it = m_manager.find(id);

        if(it == m_manager.end()){
            it = m_manager.emplace(std::pair<Uint32 , std::unique_ptr<GenericComponentManager>>{id, std::make_unique<ComponentManager<T>>()}).first;
        }

        GenericComponentManager& manager = *it->second;

        return static_cast<ComponentManager<T>&>(manager);
    }
*/

};

#endif //CYBERCRAFT_SCENE_H
