#include "render.h"

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

void drawPrefixes(SDLContext *ctx, SDL_Color textColor, BufferType type) {

    float decimalY;
    float binaryY;
    float hexY;

    if (type == Decimal) {
        decimalY = 50.0;
        binaryY = 100.0;
        hexY = 150.0;
    } else if (type == Binary) {
        binaryY = 50.0;
        hexY = 100.0;
        decimalY = 150.0;
    } else if (type == Hex) {
        hexY = 50.0;
        binaryY = 100.0;
        decimalY = 150.0;
    }

    renderTextLine(ctx->font, ctx->renderer, "Decimal:", 50.0, decimalY, textColor);
    renderTextLine(ctx->font, ctx->renderer, "Binary :", 50.0, binaryY, textColor);
    renderTextLine(ctx->font, ctx->renderer, "Hex    :", 50.0, hexY, textColor);
}

void drawDigits(SDLContext *ctx, SDL_Color textColor, StringBuffers *buffers, BufferType type) {

    float decimalY;
    float binaryY;
    float hexY;

    if (type == Decimal) {
        decimalY = 50.0;
        binaryY = 100.0;
        hexY = 150.0;
    } else if (type == Binary) {
        binaryY = 50.0;
        hexY = 100.0;
        decimalY = 150.0;
    } else if (type == Hex) {
        hexY = 50.0;
        binaryY = 100.0;
        decimalY = 150.0;
    }

    SDL_SetRenderDrawColor(ctx->renderer, 245, 255, 250, 255);
    SDL_RenderClear(ctx->renderer);

    drawPrefixes(ctx, textColor, type);
    renderTextLine(ctx->font, ctx->renderer, buffers->decimalBuffer, 180.0, decimalY, textColor);
    renderTextLine(ctx->font, ctx->renderer, buffers->binaryBuffer, 180.0, binaryY, textColor);
    renderTextLine(ctx->font, ctx->renderer, buffers->hexBuffer, 180.0, hexY, textColor);

    SDL_RenderPresent(ctx->renderer);
}
