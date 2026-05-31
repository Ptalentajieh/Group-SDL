#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

void DrawFrame(SDL_Renderer* renderer, SDL_FRect img)
{
    //outer dark gold shadow
    SDL_SetRenderDrawColor(renderer, 120, 90, 20, 255);
    SDL_FRect f1 = { img.x - 14, img.y - 14, img.w + 28, img.h + 28 };
    SDL_RenderFillRect(renderer, &f1);

    //bright gold
    SDL_SetRenderDrawColor(renderer, 212, 175, 55, 255);
    SDL_FRect f2 = { img.x - 11, img.y - 11, img.w + 22, img.h + 22 };
    SDL_RenderFillRect(renderer, &f2);

    //light gold highlight
    SDL_SetRenderDrawColor(renderer, 240, 210, 90, 255);
    SDL_FRect f3 = { img.x - 7, img.y - 7, img.w + 14, img.h + 14 };
    SDL_RenderFillRect(renderer, &f3);

    //inner dark edge
    SDL_SetRenderDrawColor(renderer, 80, 60, 10, 255);
    SDL_FRect f4 = { img.x - 3, img.y - 3, img.w + 6, img.h + 6 };
    SDL_RenderFillRect(renderer, &f4);
}

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Window", 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    // --- Load background brick texture ---
    SDL_Surface* sBg = IMG_Load("img/a.png");
    SDL_Texture* texBg = SDL_CreateTextureFromSurface(renderer, sBg);
    SDL_DestroySurface(sBg);

    // --- Load image textures ---
    SDL_Surface* s0 = IMG_Load("img/b.png");
    SDL_Texture* texGarage = SDL_CreateTextureFromSurface(renderer, s0);
    SDL_DestroySurface(s0);

    SDL_Surface* s1 = IMG_Load("img/c.png");
    SDL_Texture* texRoom = SDL_CreateTextureFromSurface(renderer, s1);
    SDL_DestroySurface(s1);

    SDL_Surface* s2 = IMG_Load("img/d.png");
    SDL_Texture* texThird = SDL_CreateTextureFromSurface(renderer, s2);
    SDL_DestroySurface(s2);


    float tileW = 0, tileH = 0;
    SDL_GetTextureSize(texBg, &tileW, &tileH);

    SDL_FRect img0 = { 30,  80, 340, 210 };  // top-left
    SDL_FRect img1 = { 430,  80, 340, 210 };  // top-right
    SDL_FRect img2 = { 230, 340, 340, 210 };  // bottom-center

    SDL_Event event;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) running = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        for (float y = 0; y < 600; y += tileH) {
            for (float x = 0; x < 800; x += tileW) {
                SDL_FRect dest = { x, y, tileW, tileH };
                SDL_RenderTexture(renderer, texBg, NULL, &dest);
            }
        }

    
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 80, 0, 60);
        SDL_FRect fullscreen = { 0, 0, 800, 600 };
        SDL_RenderFillRect(renderer, &fullscreen);

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
        DrawFrame(renderer, img0);
        DrawFrame(renderer, img1);
        DrawFrame(renderer, img2);

        SDL_RenderTexture(renderer, texGarage, NULL, &img0);
        SDL_RenderTexture(renderer, texRoom, NULL, &img1);
        SDL_RenderTexture(renderer, texThird, NULL, &img2);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texBg);
    SDL_DestroyTexture(texGarage);
    SDL_DestroyTexture(texRoom);
    SDL_DestroyTexture(texThird);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}