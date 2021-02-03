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
    void control(SDL_Event* event){
        if(event->type == SDL_KEYDOWN){
            if(p1){
                if(event->key.keysym.sym == SDLK_w){
                    mdir = -1;
                }if(event->key.keysym.sym == SDLK_s){
                    mdir = 1;
                }if(event->key.keysym.sym == SDLK_w && event->key.keysym.sym == SDLK_s){
                    mdir = 0;
                }
            }else{
                if(event->key.keysym.sym == SDLK_i){
                    mdir = -1;
                }if(event->key.keysym.sym == SDLK_k){
                    mdir = 1;
                }if(event->key.keysym.sym == SDLK_i && event->key.keysym.sym == SDLK_k){
                    mdir = 0;
                }
            }
        }
        if(event->type == SDL_KEYUP){
            if(p1){
                if(event->key.keysym.sym == SDLK_w){
                    mdir = 0;
                }if(event->key.keysym.sym == SDLK_s){
                    mdir = 0;
                }
            }else{
                if(event->key.keysym.sym == SDLK_i){
                    mdir = 0;
                }if(event->key.keysym.sym == SDLK_k){
                    mdir = 0;
                }
            }
        }
    }

    void AI(SDL_Rect ball){
        if(body.y+body.h/2-ball.h/2<ball.y){
            mdir = 1;
        }
        if(body.y+body.h/2+ball.h/2>ball.y+ball.h){
            mdir = -1;
        }
    }

    void update(){
        body.y+=mdir;
    }

    void render(SDL_Renderer* renderer){
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        SDL_RenderFillRect(renderer, &body);
    }
    SDL_Rect* getBody(){return &body;}
};

class ball{
private:
    SDL_Rect body;
    short dirX,dirY;
public:
    ball(short dirX, short dirY){
        this->dirX = dirX; this->dirY = dirY;
        body = {235,235,10,10};
    }
    void update(SDL_Rect* p1, SDL_Rect* p2){
        if(dirX == 1){
            body.x+=1;
            if(body.x+body.w<=p2->x+p2->w && body.x+body.w>=p2->x &&
               body.y<p2->y+p2->h && body.y+body.h>p2->y){
                dirX = -1;
                if(body.y+body.h>p2->y&&body.y<p2->y+10){
                    dirY = -1;
                }
                if(body.y==p2->y+10){
                    dirY = 0;
                }
                if(body.y+body.h>p2->y+20&&body.y<p2->y+30){
                    dirY = 1;
                }
            }
        }
        if(dirX == -1){
            body.x-=1;
            if(body.x>=p1->x && body.x<=p1->x+p1->w &&
               body.y<p1->y+p1->h && body.y+body.h>p1->y){
                dirX = 1;
                if(body.y+body.h>p1->y&&body.y<p1->y+10){
                    dirY = -1;
                }
                if(body.y==p1->y+10){
                    dirY = 0;
                }
                if(body.y+body.h>p1->y+20&&body.y<p1->y+30){
                    dirY = 1;
                }
            }
        }
        if(dirY == 1){
            body.y+=1;
            if(body.y+body.h>=480){
                dirY = -1;
            }
        }
        if(dirY == -1){
            body.y-=1;
            if(body.y<=0){
                dirY = 1;
            }
        }
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
    player player2 = player(false);
    ball mball = ball(-1,0);

    int frame = SDL_GetTicks();
    while(true){
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);

        player1.render(renderer);
        player2.render(renderer);
        mball.render(renderer);

        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)){
            break;
        }
        player1.control(&event);
        player2.control(&event);

        if(SDL_GetTicks()-frame>=1000/120){
            player1.update();
            player2.update();
            mball.update(player1.getBody(), player2.getBody());
            frame = SDL_GetTicks();
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
