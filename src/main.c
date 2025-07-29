#include <SDL3/SDL.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
} SDLContext;

SDLContext initSDL() {
    SDLContext ctx = {NULL};

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_Init failed %s", SDL_GetError());
        return ctx;
    }

    if (TTF_Init() == 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "TTF_Init failed %s", SDL_GetError());
        return ctx;
    }

    ctx.window = SDL_CreateWindow("digit dive", 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!ctx.window) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return ctx;
    }

    ctx.renderer = SDL_CreateRenderer(ctx.window, NULL);
    if (!ctx.renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create renderer: %s\n", SDL_GetError());
        return ctx;
    }

    ctx.font = TTF_OpenFont("assets/IBMPlexMono-Medium.ttf", 24);
    if (!ctx.font) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not load font: %s", SDL_GetError());
        return ctx;
    }

    return ctx;
}

int renderTextLine(TTF_Font *font, SDL_Renderer *renderer, const char *text, float x, float y, SDL_Color textColor) {
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, text, 0, textColor);
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

    SDL_FRect textRect = {x, y, (float)textW, (float)textH};

    SDL_RenderTexture(renderer, textTexture, NULL, &textRect);
    SDL_DestroyTexture(textTexture);

    return 0;
};

int main(int argc, char *argv[]) {
    bool run = true;

    SDLContext ctx = initSDL();
    if (!ctx.window || !ctx.renderer || !ctx.font) {
        return 1;
    }

    SDL_Color textColor = {0, 0, 0, 255};

    SDL_SetRenderDrawColor(ctx.renderer, 245, 255, 250, 255);
    SDL_RenderClear(ctx.renderer);
    renderTextLine(ctx.font, ctx.renderer, "hello world", 50.0, 50.0, textColor);
    SDL_RenderPresent(ctx.renderer);

    while (run) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                run = false;
        }

        SDL_Delay(16);
    }

    TTF_CloseFont(ctx.font);
    SDL_DestroyWindow(ctx.window);
    SDL_DestroyRenderer(ctx.renderer);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
