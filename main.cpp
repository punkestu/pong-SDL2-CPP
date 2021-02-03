#include <SDL.h>
#include <iostream>

class player{
private:
    bool p1;
    SDL_Rect body;
    short mdir;
public:
    player(bool p1){
        this->p1 = p1;
        if(p1){
            body = {20,225, 10,30};
        }else{
            body = {430,225, 10,30};
        }
        mdir = 0;
    }

    void render(SDL_Renderer* renderer){
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        SDL_RenderFillRect(renderer, &body);
    }
};

int main(int argc, char* argv[])
{
    SDL_Window* window = SDL_CreateWindow("apps", 100,100,480,480,false);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Event event;
    player player1 = player(true);
    while(true){
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);

        player1.render(renderer);

        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)){
            break;
        }


        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
