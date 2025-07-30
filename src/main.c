#include "sdl_context.h"
#include "buffers.h"
#include "render.h"

#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_main.h>

int main(int argc, char *argv[]) {
    bool run = true;

    StringBuffers buffers;
    initBuffers(&buffers);

    BufferType currentBufferType = Decimal;

    int cursor = 0;

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
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                run = false;

            else if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.key == SDLK_ESCAPE) {
                    run = false;
                }
                if (event.key.key == SDLK_BACKSPACE) {
                    removeFromBuffer(&buffers, &cursor, currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_RETURN) {
                    resetBuffers(&buffers, &cursor);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_0) {
                    addToBuffer(&buffers, &cursor, '0', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_1) {
                    addToBuffer(&buffers, &cursor, '1', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_2) {
                    addToBuffer(&buffers, &cursor, '2', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_3) {
                    addToBuffer(&buffers, &cursor, '3', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_4) {
                    addToBuffer(&buffers, &cursor, '4', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_5) {
                    addToBuffer(&buffers, &cursor, '5', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_6) {
                    addToBuffer(&buffers, &cursor, '6', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_7) {
                    addToBuffer(&buffers, &cursor, '7', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_8) {
                    addToBuffer(&buffers, &cursor, '8', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_9) {
                    addToBuffer(&buffers, &cursor, '9', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_9) {
                    addToBuffer(&buffers, &cursor, 'A', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_9) {
                    addToBuffer(&buffers, &cursor, 'B', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_9) {
                    addToBuffer(&buffers, &cursor, 'C', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_9) {
                    addToBuffer(&buffers, &cursor, 'D', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_9) {
                    addToBuffer(&buffers, &cursor, 'E', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_9) {
                    addToBuffer(&buffers, &cursor, 'F', currentBufferType);
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_D) {
                    currentBufferType = Decimal;
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_B) {
                    currentBufferType = Binary;
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
                if (event.key.key == SDLK_H) {
                    currentBufferType = Hex;
                    drawDigits(&ctx, textColor, &buffers, currentBufferType);
                }
            }
        }

        SDL_Delay(16);
    }

    cleanupSDL(&ctx);

    return 0;
}
