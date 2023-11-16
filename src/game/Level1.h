#include "EngineObject.h"
#include "Player.h"
#include "LevelMap.h"

class Level1 : public EngineObject {
    Player player = Player(this);
    LevelMap map = LevelMap(this);

public:
    Level1();
    ~Level1();

    void start();
    void update();
};