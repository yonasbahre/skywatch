#include <SDL2/SDL_ttf.h>
#include "EngineObject.h"

class StartScreen : public EngineObject {
    class StartScreenRenderer : public Renderer {
    public:
        TTF_Font *AlteHaasBold;
        SDL_Surface *titleSurface;
        SDL_Texture *titleTexture;
        SDL_Rect titleRect;

        StartScreenRenderer(StartScreen *object);
        ~StartScreenRenderer();    
        void render();
    };

public:
    StartScreen();
    ~StartScreen();

    void start();
    void update();
};