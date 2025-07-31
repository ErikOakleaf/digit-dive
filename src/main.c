#include "buffers.h"
#include "render.h"
#include "sdl_context.h"

#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_main.h>

int main(int argc, char *argv[]) {
    bool run = true;

    StringBuffers buffers;
    initBuffers(&buffers);

    BufferType currentBufferType = Decimal;

    SDLContext ctx = initSDL();
    if (!ctx.window || !ctx.renderer || !ctx.font) {
        return 1;
    }

    SDL_Color textColor = {0, 0, 0, 255};

    SDL_SetRenderDrawColor(ctx.renderer, 245, 255, 250, 255);
    SDL_RenderClear(ctx.renderer);

    drawPrefixes(&ctx, textColor, currentBufferType);

    SDL_RenderPresent(ctx.renderer);

    while (run) {
        SDL_Event event;
        if (SDL_WaitEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                run = false;
            } else if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.key == SDLK_ESCAPE) {
                    run = false;
                }
                if (event.key.key == SDLK_D && (SDL_GetModState() & SDL_KMOD_SHIFT)) {
                    currentBufferType = Decimal;
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_B && (SDL_GetModState() & SDL_KMOD_SHIFT)) {
                    currentBufferType = Binary;
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_H && (SDL_GetModState() & SDL_KMOD_SHIFT)) {
                    currentBufferType = Hex;
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_BACKSPACE) {
                    removeFromBuffer(&buffers, currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_RETURN) {
                    resetBuffers(&buffers);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_0) {
                    addToBuffer(&buffers, '0', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_1) {
                    addToBuffer(&buffers, '1', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_2) {
                    addToBuffer(&buffers, '2', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_3) {
                    addToBuffer(&buffers, '3', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_4) {
                    addToBuffer(&buffers, '4', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_5) {
                    addToBuffer(&buffers, '5', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_6) {
                    addToBuffer(&buffers, '6', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_7) {
                    addToBuffer(&buffers, '7', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_8) {
                    addToBuffer(&buffers, '8', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_9) {
                    addToBuffer(&buffers, '9', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_A) {
                    addToBuffer(&buffers, 'A', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_B) {
                    addToBuffer(&buffers, 'B', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_C) {
                    addToBuffer(&buffers, 'C', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_D) {
                    addToBuffer(&buffers, 'D', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_E) {
                    addToBuffer(&buffers, 'E', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_F) {
                    addToBuffer(&buffers, 'F', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
            }
        }
    }

    cleanupSDL(&ctx);

    return 0;
}
