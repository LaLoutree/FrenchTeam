/*
** File description:
** Bomb
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <istream>
#include "raylib.h"
#include <memory>
#include "Map.hpp"
#include "uVector.hpp"

class Player;

enum bombDirections { B_RIGHT = 0, B_LEFT = 1, B_DOWN = 2, B_UP = 3 };

class Bomb {
    public:
        Bomb();
        ~Bomb();
        void animIdleBomb(void);
        void doExplosion(Map &map, uVector<Player> &players);
        void initBomb(Model bomb, ModelAnimation *bombAnims, int powerBomb);
        void draw(Map &map, uVector<Player> &players);
        void setBombPos(Vector3 position, Map &map);
        bool hasExploded(void) const;
        void collisionExplosion(Vector3 BombPos, Vector3);
        void doExplosionBrick(Map &map, bool *directions[4], std::array<int, 195> &m, int bombPower);
        void doExplosionEmpty(Map &map, bool *directions[4], int bombPower);
        void checkExplosionPlayer(bool *directions[4], uVector<Player> &players, int bombPower);
        void checkCollisionBomb(uVector<Player> &players, int index);
        void checkExplosionBlock(Map &map, bool *directions[4], int bombPower);
        int *_playerNbBomb;

    protected:
    private:
        ModelAnimation *_bombAnims;
        Model _bomb;
        Texture2D _textureBomb;
        unsigned int _bombAnimsCount;
        int _idleBombAnimFrameCounter;
        Vector3 rotationAxis;
        float rotationAngle;
        Vector3 scale;
        Color color;

        Vector3 bombPos;
        double explosionTime;
        bool exploded;
        int _powerBomb;
};

#endif /* !BOMB_HPP_ */
