#include "SDLUtils.h"

int setSDLDrawColor(SDL_Renderer *renderer, SDL_Color color) {
    return SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}