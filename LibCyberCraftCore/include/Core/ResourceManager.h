//
// Created by jngl on 24/04/2021.
//

#ifndef CYBERCRAFT_RESOURCEMANAGER_H
#define CYBERCRAFT_RESOURCEMANAGER_H

#include "Id.h"

/*
Idea of runtime file and resource pipeline :
                                    Extension
                                       │
                                       │     ┌───┐
                                       ├─────┤...│
                                       │     └───┘
                                       │
                                       │     ┌─────────┐
                                       ├─────┤FileType2│
              Mock-able                │     └─────────┘
                 │                     │
                 │  ┌──────────┐       │     ┌─────────┐
                 ├─►│FileSystem│       ├─────┤FileType1│
                 │  └──────────┘       │     └─────────┘
                 │                     ▼
     ┌────┐    ┌─┴─────────────┐    ┌───────────────┐    ┌────────┐
     │Game├─┬─►│ResourceManager├─┬─►│FileTypeManager├─┬─►│Graphics│
     └────┘ │  └──────┬────────┘ │  └───────────────┘ │  └────────┘
       ▲    │         │          │                    │
       │   Load       │         File                  │  ┌────┐
       │  Unload      │                               ├─►│Game│
       │              │                               │  └────┘
       │              │                               │
       │              │                               │  ┌────────┐
       └──────┬───────┘                               ├─►│3DEngine│
              │                                       │  └────────┘
        GetResourceID                                 │
                                                      │  ┌───┐
                                                      ├─►│...│
                                                      │  └───┘
                                                      │
                                                     Data
 */

}

#endif //CYBERCRAFT_RESOURCEMANAGER_H
