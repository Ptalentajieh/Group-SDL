#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("SDL3 Gallery", 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    // --- Load background brick texture ---
    SDL_Surface* sBg = IMG_Load("C:/Users/talen/Downloads/SDL_Base_Project/SDL_Base_Project/a.png");
    SDL_Texture* texBg = SDL_CreateTextureFromSurface(renderer, sBg);
    SDL_DestroySurface(sBg);

    // --- Load image textures ---
    SDL_Surface* s0 = IMG_Load("C:/Users/talen/Downloads/SDL_Base_Project/SDL_Base_Project/b.png");
    SDL_Texture* texGarage = SDL_CreateTextureFromSurface(renderer, s0);
    SDL_DestroySurface(s0);

    SDL_Surface* s1 = IMG_Load("C:/Users/talen/Downloads/SDL_Base_Project/SDL_Base_Project/c.png");
    SDL_Texture* texRoom = SDL_CreateTextureFromSurface(renderer, s1);
    SDL_DestroySurface(s1);

    SDL_Surface* s2 = IMG_Load("C:/Users/talen/Downloads/SDL_Base_Project/SDL_Base_Project/d.png");
    SDL_Texture* texThird = SDL_CreateTextureFromSurface(renderer, s2);
    SDL_DestroySurface(s2);

    
    float tileW = 0, tileH = 0;
    SDL_GetTextureSize(texBg, &tileW, &tileH);

    const float B = 8.0f;

    SDL_FRect img0 = { 30,  80, 340, 210 };  // top-left
    SDL_FRect img1 = { 430,  80, 340, 210 };  // top-right
    SDL_FRect img2 = { 230, 340, 340, 210 };  // bottom-center

    // --- Gold frame rects ---
    SDL_FRect frame0 = { img0.x - B, img0.y - B, img0.w + B * 2, img0.h + B * 2 };
    SDL_FRect frame1 = { img1.x - B, img1.y - B, img1.w + B * 2, img1.h + B * 2 };
    SDL_FRect frame2 = { img2.x - B, img2.y - B, img2.w + B * 2, img2.h + B * 2 };

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

        // --- Draw gold frames ---
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
        SDL_SetRenderDrawColor(renderer, 212, 175, 55, 255);
        SDL_RenderFillRect(renderer, &frame0);
        SDL_RenderFillRect(renderer, &frame1);
        SDL_RenderFillRect(renderer, &frame2);

        
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