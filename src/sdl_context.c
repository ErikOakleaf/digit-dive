#include "sdl_context.h"

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

    ctx.window = SDL_CreateWindow("digit dive", 680, 250, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

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

void cleanupSDL(SDLContext *ctx) {
    TTF_CloseFont(ctx->font);
    SDL_DestroyWindow(ctx->window);
    SDL_DestroyRenderer(ctx->renderer);
    TTF_Quit();
    SDL_Quit();
}
