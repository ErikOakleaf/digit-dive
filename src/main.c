#include <SDL3/SDL.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    SDL_Window *window;
    bool done = false;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    // Create an application
    window = SDL_CreateWindow("digit dive", 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create renderer: %s\n", SDL_GetError());
        return 1;
    }

    TTF_Font *font = TTF_OpenFont("assets/IBMPlexMono-Medium.ttf", 24);
    if (!font) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not load font: %s", SDL_GetError());
        return 1;
    }

    SDL_Color textColor = {0, 0, 0, 255};

    SDL_Surface *textSurface = TTF_RenderText_Blended(font, "Hello, World", 0, textColor);
    if (!textSurface) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not render texture: %s", SDL_GetError());
    }

    int textW = textSurface->w;
    int textH = textSurface->h;

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create texture: %s", SDL_GetError());
        return 1;
    }
    SDL_DestroySurface(textSurface);

    SDL_FRect textRect = {50.0f, 50.0f, (float)textW, (float)textH};

    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                done = true;
        }

        SDL_SetRenderDrawColor(renderer, 245, 255, 250, 255);
        SDL_RenderClear(renderer);

        SDL_RenderTexture(renderer, textTexture, NULL, &textRect);

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    TTF_CloseFont(font);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
