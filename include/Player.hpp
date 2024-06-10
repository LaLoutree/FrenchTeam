/*
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <iostream>
#include <vector>
#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include "Map.hpp"
#include <chrono>

class BombManager;

class Player {
    public:
        Player();
        ~Player();
        void checkCollision(Map &map, std::string direction);
        void checkCollisionBrick(Map &map, float offset1, float offset2);
        void checkCollisionBlock(Map &map, float offset1, float offset2);
        void checkCollisionPowerBomb(Map &map, float offset1, float offset2);
        void checkCollisionPowerNb(Map &map, float offset1, float offset2);
        void checkCollisionPowerSpeed(Map &map, float offset1, float offset2);
        void checkCollisionPowerWall(Map &map, float offset1, float offset2);
        void checkCollisionBomb(float offset1, float offset2);

        void animWalk(void);
        void animIdle(void);
        void animDead(void);
        void movePlayer(std::string);
        void initPlayer(const char *);
        void animate(void);
        void move(Map &map);
        void draw(void);
        void plantBomb(BombManager &bombManager, Map &map);
        void update(Map &map, BombManager &bombManager);

        void setPlayerPos(Vector3 pos);
        Vector3 getPlayerPos(void) const;
        Vector3 getPlayerSize(void) const;
        Vector3 getRotationAxis(void) const;
        Vector3 getScale(void) const;

        void setCollision(bool collision);
        bool getCollision(void) const;

        void setWalkAnimsCount(unsigned int walkAnimsCount);
        void setIdleAnimsCount(unsigned int idleAnimsCount);
        unsigned int getWalkAnimsCount(void) const;
        unsigned int getIdleAnimsCount(void) const;

        void setWalkAnimFrameCounter(int walkAnimFrameCounter);
        void setIdleAnimFrameCounter(int idelAnimFrameCounter);
        int getWalkAnimFrameCounter(void) const;
        int getIdleAnimFrameCounter(void) const;

        Model getModelPlayer(void) const;
        void getRotation(void);
        Texture2D getTexturePlayer(void) const;

        int getNbBomb(void) const;
        void setNbBomb(int);

        int getPowerBomb(void) const;
        void setPowerBomb(int p);

        float getPlayerSpeed(void) const;
    
        void setPlayerLife(bool l);
        bool getPlayerLife(void) const;

        void setPlayerKey(int right, int left, int down, int up, int plant);

    protected:
    private:
        bool _collision;
        bool _colliBomb;
        Vector3 playerPos;
        Vector3 playerSize;
        Vector3 rotationAxis;
        Vector3 scale;
        float rotationAngle;
        Color color;

        unsigned int _walkAnimsCount;
        unsigned int _idleAnimsCount;
        unsigned int _deadAnimsCount;
        int _walkAnimFrameCounter;
        int _idleAnimFrameCounter;
        int _deadAnimFrameCounter;
        ModelAnimation *walkAnims;
        ModelAnimation *idleAnims;
        ModelAnimation *deadAnims;
        Model player;
        Texture2D texturePlayer;

        int _nbBomb;
        float _speed;
        int _powerBomb;
        bool _passWall;
        bool _life;

        float roll;

        int keyRight;
        int keyLeft;
        int keyDown;
        int keyUp;
        int keyPlant;
        std::vector<Vector3> BombPos;
};


#endif /* !PLAYER_HPP_ */
