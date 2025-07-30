#include <SDL3/SDL.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structs

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
} SDLContext;

typedef struct {
    char decimalBuffer[11];
    char binaryBuffer[33];
    char hexBuffer[9];
} StringBuffers;

// Enums

typedef enum {
    Decimal,
    Binary,
    Hex,
} BufferType;

// SDL Functions

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

    ctx.window = SDL_CreateWindow("digit dive", 800, 250, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

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
    if (strlen(text) == 0) {
        return 0;
    }

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

void drawPrefixes(SDLContext *ctx, SDL_Color textColor) {
    renderTextLine(ctx->font, ctx->renderer, "Decimal:", 50.0, 50.0, textColor);
    renderTextLine(ctx->font, ctx->renderer, "Binary :", 50.0, 100.0, textColor);
    renderTextLine(ctx->font, ctx->renderer, "Hex    :", 50.0, 150.0, textColor);
}

void drawDigits(SDLContext *ctx, SDL_Color textColor, StringBuffers *buffers) {
    SDL_SetRenderDrawColor(ctx->renderer, 245, 255, 250, 255);
    SDL_RenderClear(ctx->renderer);

    drawPrefixes(ctx, textColor);
    renderTextLine(ctx->font, ctx->renderer, buffers->decimalBuffer, 180.0, 50.0, textColor);
    renderTextLine(ctx->font, ctx->renderer, buffers->binaryBuffer, 180.0, 100.0, textColor);

    SDL_RenderPresent(ctx->renderer);
}

// String functions

void reverseString(char *str) {
    if (!str) {
        return;
    }

    char *start = str;
    char *end = str;

    while (*end != '\0') {
        end++;
    }
    end--;

    while (start < end) {
        char tmp = *start;
        *start++ = *end;
        *end-- = tmp;
    }
}

void decimalToBinary(char *decimalBuffer, char *binaryBuffer) {
    long long decimal = atoll(decimalBuffer);

    if (decimal == 0) {
        binaryBuffer[0] = '0';
        binaryBuffer[1] = '\0';
        return;
    }

    int i = 0;
    while (decimal > 0) {
        int bit = decimal & 1;
        binaryBuffer[i++] = '0' + bit;

        decimal = decimal >> 1;
    }

    binaryBuffer[i] = '\0';

    reverseString(binaryBuffer);
}

void addToBufferDecimal(StringBuffers *buffers, int *bufferIndex, char c) {
    if (*bufferIndex < 10) {
        buffers->decimalBuffer[(*bufferIndex)++] = c;
        buffers->decimalBuffer[*bufferIndex] = '\0';
    }

    decimalToBinary(buffers->decimalBuffer, buffers->binaryBuffer);
}

void addToBuffer(StringBuffers *buffers, int *bufferIndex, char c, BufferType type) {
    switch (type) {
        case Decimal: {
            if (!(c >= '0' && c <= '9')) {
                return;
            }
            addToBufferDecimal(buffers, bufferIndex, c);
            break;
        }
        case Binary: {

            break;
        }
        case Hex: {

            break;
        }
        default:
            return;
    }
}

void removeFromBufferDecimal(StringBuffers *buffers, int *bufferIndex) {
    (*bufferIndex)--;
    buffers->decimalBuffer[*bufferIndex] = '\0';

    decimalToBinary(buffers->decimalBuffer, buffers->binaryBuffer);
}

void removeFromBuffer(StringBuffers *buffers, int *bufferIndex, BufferType type) {
    if (*bufferIndex <= 0) {
        return;
    }

    switch (type) {
        case Decimal: {
            removeFromBufferDecimal(buffers, bufferIndex);
            break;
        }
        case Binary: {

            break;
        }
        case Hex: {

            break;
        }
        default:
            return;
    }
}

int main(int argc, char *argv[]) {
    bool run = true;

    StringBuffers buffers;
    memset(buffers.decimalBuffer, 0, sizeof(buffers.decimalBuffer));
    memset(buffers.binaryBuffer, 0, sizeof(buffers.binaryBuffer));
    memset(buffers.hexBuffer, 0, sizeof(buffers.hexBuffer));

    int cursor = 0;

    SDLContext ctx = initSDL();
    if (!ctx.window || !ctx.renderer || !ctx.font) {
        return 1;
    }

    SDL_Color textColor = {0, 0, 0, 255};

    SDL_SetRenderDrawColor(ctx.renderer, 245, 255, 250, 255);
    SDL_RenderClear(ctx.renderer);

    drawPrefixes(&ctx, textColor);

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
                    removeFromBuffer(&buffers, &cursor, Decimal);
                    drawDigits(&ctx, textColor, &buffers);
                }
                if (event.key.key == SDLK_0) {
                    addToBuffer(&buffers, &cursor, '0', Decimal);
                    drawDigits(&ctx, textColor, &buffers);
                }
                if (event.key.key == SDLK_1) {
                    addToBuffer(&buffers, &cursor, '1', Decimal);
                    drawDigits(&ctx, textColor, &buffers);
                }
                if (event.key.key == SDLK_2) {
                    addToBuffer(&buffers, &cursor, '2', Decimal);
                    drawDigits(&ctx, textColor, &buffers);
                }
                if (event.key.key == SDLK_3) {
                    addToBuffer(&buffers, &cursor, '3', Decimal);
                    drawDigits(&ctx, textColor, &buffers);
                }
                if (event.key.key == SDLK_4) {
                    addToBuffer(&buffers, &cursor, '4', Decimal);
                    drawDigits(&ctx, textColor, &buffers);
                }
                if (event.key.key == SDLK_5) {
                    addToBuffer(&buffers, &cursor, '5', Decimal);
                    drawDigits(&ctx, textColor, &buffers);
                }
                if (event.key.key == SDLK_6) {
                    addToBuffer(&buffers, &cursor, '6', Decimal);
                    drawDigits(&ctx, textColor, &buffers);
                }
                if (event.key.key == SDLK_7) {
                    addToBuffer(&buffers, &cursor, '7', Decimal);
                    drawDigits(&ctx, textColor, &buffers);
                }
                if (event.key.key == SDLK_8) {
                    addToBuffer(&buffers, &cursor, '8', Decimal);
                    drawDigits(&ctx, textColor, &buffers);
                }
                if (event.key.key == SDLK_9) {
                    addToBuffer(&buffers, &cursor, '9', Decimal);
                    drawDigits(&ctx, textColor, &buffers);
                }
            }
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
