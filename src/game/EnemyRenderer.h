#pragma once
#include "Renderer.h"
#include "Sprite.h"

class Enemy;

class EnemyRenderer : public Renderer {
    Enemy *enemy = nullptr;
public:
    Sprite sprite = Sprite(this->sdlRenderer, "assets/enemy.png");

    EnemyRenderer(Enemy *enemy);
    ~EnemyRenderer();
    void render();
};