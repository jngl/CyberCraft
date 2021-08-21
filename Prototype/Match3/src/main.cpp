#include <SDL.h>

#include <Core/Timer.hpp>
#include <Core/Math.h>
#include <Core/Id.h>
#include <Core/Component.h>

using IdGenerator = cc::IdGenerator<uint32_t, struct IdTag>;
using Id = IdGenerator::ThisId;

struct PosComp{
    cc::Vector2f pos;
};

void drawEntity(SDL_Renderer* renderer, const PosComp& pos){
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    const SDL_FRect rect{pos.pos.x,pos.pos.y,10,10};
    SDL_RenderFillRectF(renderer, &rect);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Match3", SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    cc::Timer timer;

    IdGenerator idGenerator;
    cc::ComponentManager<PosComp, Id> posCompManager;

    Id entity = idGenerator.create();
    PosComp& pos = posCompManager.create(entity);
    pos.pos.x = 400;
    pos.pos.y = 400;

    float time = 0;
    bool running = true;
    while (running) {
        const float frameTime = timer.timeInSecond();
        timer.restart();
        time += frameTime;

        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        const SDL_FRect rect{sin(time)*50+100,100,50,50};
        SDL_RenderFillRectF(renderer, &rect);

        drawEntity(renderer, pos);

        SDL_RenderPresent(renderer);
    }

    idGenerator.destroy(entity);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
