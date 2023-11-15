#include <iostream>
#include <SDL2/SDL.h>
#include "Constants.h"
#include "StartScreen.h"
#include "Engine.h"
#include "Renderer.h"

StartScreen::StartScreen() {
    renderer = new StartScreenRenderer(this);
}

StartScreen::~StartScreen() {}

void StartScreen::start() {}

void StartScreen::update() {}

StartScreen::StartScreenRenderer::StartScreenRenderer(StartScreen *object)
    : Renderer(object) {
    // AlteHaasBold = TTF_OpenFont("assets/AlteHaasGroteskBold.ttf", 288);
    // if (!AlteHaasBold) {
    //     std::cout << "Error: " << SDL_GetError() << std::endl;
    // }
    
    // titleSurface = TTF_RenderText_Blended(
    //     AlteHaasBold,
    //     "Skywatch",
    //     {255, 255, 255}
    // );
    // titleTexture = SDL_CreateTextureFromSurface(sdlRenderer, titleSurface);
    // titleRect.x = pos.x;
    // titleRect.y = pos.y;
    // titleRect.w = titleSurface->w;
    // titleRect.h = titleSurface->h;
    // SDL_QueryTexture(titleTexture, NULL, NULL, &titleRect.x, &titleRect.y);
}

StartScreen::StartScreenRenderer::~StartScreenRenderer() {
    // SDL_FreeSurface(titleSurface);
    // SDL_DestroyTexture(titleTexture);
    // TTF_CloseFont(AlteHaasBold);
}

void StartScreen::StartScreenRenderer::render() {
    // SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 255, 255);
    // SDL_RenderCopy(sdlRenderer, titleTexture, NULL, &titleRect);
    
    // title.draw(globalPos);
}