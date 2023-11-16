#include "EngineObject.h"
#include "EventManager.h"
#include "Text.h"

class StartScreen : public EngineObject {
    class StartScreenRenderer : public Renderer {
    public:
        Text title = Text(
            this->sdlRenderer, 
            "assets/Imperator Bold.ttf", 
            196
        );

        Text pressToStart = Text(
            this->sdlRenderer,
            "assets/Imperator.ttf",
            72
        );

        StartScreenRenderer(StartScreen *object);
        ~StartScreenRenderer();    
        void render();
    };

    EventManager *eventMgr = nullptr;
    SDL_Thread *flasherThread = nullptr;
    bool isFlashing = true;

    // Stupid hack because you can't start an SDL thread with an
    // instance method. I refuse to use Win32 threads
    static int flashPressStartText(void *data);
    void togglePressStartVisibility();

public:
    StartScreen();
    ~StartScreen();

    void start();
    void update();
};