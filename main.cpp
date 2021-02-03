#include <SDL.h>
#include <iostream>
#include <conio.h>

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
            body = {450,225, 10,30};
        }
        mdir = 0;
    }
    void reinit(){
        if(p1){
            body = {20,225, 10,30};
        }else{
            body = {450,225, 10,30};
        }
        mdir = 0;
    }
    void control(SDL_Event* event){
        if(event->type == SDL_KEYDOWN){
            if(p1){
                if(event->key.keysym.sym == SDLK_w){
                    if(body.y>0){
                        mdir = -1;
                    }else{
                        mdir = 0;
                    }
                }if(event->key.keysym.sym == SDLK_s){
                    if(body.y<450){
                        mdir = 1;
                    }else{
                        mdir = 0;
                    }
                }if(event->key.keysym.sym == SDLK_w && event->key.keysym.sym == SDLK_s){
                    mdir = 0;
                }
            }else{
                if(event->key.keysym.sym == SDLK_i){
                    if(body.y>0){
                        mdir = -1;
                    }else{
                        mdir = 0;
                    }
                }if(event->key.keysym.sym == SDLK_k){
                    if(body.y<450){
                        mdir = 1;
                    }else{
                        mdir = 0;
                    }
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

    void AI(SDL_Rect ball, short dirX){
        if(p1){
            //if(dirX==-1){
                if(body.y+body.h/2-ball.h/2<ball.y){
                    mdir = 1;
                }
                if(body.y+body.h/2+ball.h/2>ball.y+ball.h){
                    mdir = -1;
                }
//            }else{
//                mdir = 0;
//            }
        }else{
            //if(dirX==1){
                if(body.y+body.h/2-ball.h/2<ball.y){
                    if(body.y<450){
                        mdir = 1;
                    }else{
                        mdir = 0;
                    }
                }
                if(body.y+body.h/2+ball.h/2>ball.y+ball.h){
                    if(body.y>0){
                        mdir = -1;
                    }else{
                        mdir = 0;
                    }
                }
//            }
//            else{
//                mdir = 0;
//            }
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
    void reinit(short dirX, short dirY){
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
            body.y+=2;
            if(body.y+body.h>=480){
                dirY = -1;
            }
        }
        if(dirY == -1){
            body.y-=2;
            if(body.y<=0){
                dirY = 1;
            }
        }
    }

    void render(SDL_Renderer* renderer){
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        SDL_RenderFillRect(renderer, &body);
    }
    SDL_Rect* getBody(){return &body;}
    short getDirX(){return dirX;}
};

int main(int argc, char* argv[])
{
    char opsi;
    std::cout<<"pvp[y/n/q]?";
    std::cin>>opsi;

    if(opsi != 'q'){

    SDL_Window* window = SDL_CreateWindow("apps", 100,100,480,480,false);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_RaiseWindow(window);
    short x,y;

    SDL_Event event;
    player player1 = player(true);
    player player2 = player(false);
    for(int i = 0; i < 10; i++){
        srand(SDL_GetTicks()+rand()-rand()/2+101);
        x = rand()%2==0?-1:1;
        y = rand()%3-1;
    }
    ball mball = ball(x,y);

    int frame;
    bool play = false;
    frame = SDL_GetTicks();
    while(true){
        for(int i = 0; i < 10; i++){
            x = rand()%6>2?-1:1;
            y = (rand()%100)%3-1;
        }
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
        if(opsi == 'y'){
            player2.control(&event);
        }else{
            player2.AI(*(mball.getBody()),mball.getDirX());
        }

        if(SDL_GetTicks()-frame>=3*1000){
            play = true;
        }

        if(play){
            if(SDL_GetTicks()-frame>=1000/120){
                player1.update();
                player2.update();
                mball.update(player1.getBody(), player2.getBody());
                frame = SDL_GetTicks();
            }
        }else{
            //frame = SDL_GetTicks();
            player1.reinit();
            player2.reinit();
            mball.reinit(x,y);
        }
        if(mball.getBody()->x+10<=0){
            play = false;
        }
        if(mball.getBody()->x>=480){
            play = false;
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    }
    SDL_Quit();

    return 0;
}
