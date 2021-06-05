#include "SystemState.h"

#include <iostream>

int main () {
    try{
        SystemState systemState;

        while(systemState.isRunning()){
            systemState.frame();
        }

        return 0;
    }catch(const std::exception& e){
        std::cout<<e.what()<<std::endl;
        return 1;
    }
}
