//
// Created by jngl on 18/07/2020.
//

#include "Scene.h"

Entity Scene::create() {
    return m_registry.create();
}
