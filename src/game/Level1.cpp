#include <iostream>
#include "Level1.h"

Level1::Level1() {}

Level1::~Level1() {}

void Level1::start() {
    player.registerAndStart();
    map.registerAndStart();
}

void Level1::update() {
    map.updateScreenTransform(player.getWorldPos());
}