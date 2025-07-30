#include "sdl_context.h"
#include "buffers.h"
#include <SDL3/SDL_rect.h>

#ifndef RENDER_H
#define RENDER_H

int renderTextLine(TTF_Font *font, SDL_Renderer *renderer, const char *text, float x, float y, SDL_Color textColor); 
void drawPrefixes(SDLContext *ctx, SDL_Color textColor, BufferType type); 
void drawDigits(SDLContext *ctx, SDL_Color textColor, StringBuffers *buffers, BufferType type); 

#endif
