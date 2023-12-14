#include <functional>
#include <unordered_set>
#include "EngineObject.h"
#include "Player.h"
#include "LevelMap.h"
#include "LevelUI.h"

class Level1 : public EngineObject {
    const Vec2D baseScreenTransform = 
        Vec2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    Vec2D screenTransform = baseScreenTransform;

    LevelMap map = LevelMap(this, screenTransform);
    LevelUI ui = LevelUI(this);

    Player player = Player(
        this,
        ui,
        getRoadSegmentOfPoint(),
        updateCurrRoadSegment()
    );
    
    // Empty parent node that contains everything that renders in segments
    // This hack is necessary to make sure everything renders in the correct order
    // Lesson learned: dont tie render order to when an object's start() method is called
    struct SegmentParent : public EngineObject {
        void start() {}
        void update() {}

        SegmentParent(EngineObject *parent) : EngineObject(parent) {}
    };
    SegmentParent segmentParent = SegmentParent(this);

    std::vector<std::unordered_set<EngineObject*>> segments;
    int currSegment = 0;
    const int LEFT_WINDOW_SIZE = 2;
    const int RIGHT_WINDOW_SIZE = 2;

    void loadSegment(int index);
    void unloadSegment(int index);
    void startSegment(int index);

    void loadEnemiesInSegment(int index);
    void loadCrowsInSegment(int index);
    void loadBreadInSegment(int index);
    void loadPebblesInSegment(int index);

    std::function<int(Vec2D)> getRoadSegmentOfPoint();
    std::function<void(int)> updateCurrRoadSegment();
    
    // Items are not actually deleted from a segment until
    // the start of the next frame
    std::function<void(EngineObject*)> queueForDeletion();
    std::vector<EngineObject*> deletionQueue;
    void deleteObjectFromSegment(EngineObject *object);

public:
    Level1();
    ~Level1();

    void start();
    void update();
};