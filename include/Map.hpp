/*
** Map.hpp
** File description:
** map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include <iostream>
#include <vector>
#include "raylib.h"
#include <math.h>
#include "raymath.h"
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <array>
#include "uVector.hpp"

#include "rlgl.h"

class Map {
    public:
        Map();
        ~Map();
        void drawMap();
        void createMap();
        void setMap(std::array<int, 195> m);
        void setMapPos(std::array<int, 195> m);
        int getMapHeight(void) const;
        int getMapWidth(void) const;
        void setMapHeight(int height);
        void setMapWidth(int width);
        std::vector<Vector3> getMapBrick(void) const;
        std::vector<Vector3> getMapBlock(void) const;
        std::vector<Vector3> getMapEmpty(void) const;
        std::vector<Vector3> getMapPowerBomb(void) const;
        std::vector<Vector3> getMapPowerNb(void) const;
        std::vector<Vector3> getMapPowerSpeed(void) const;
        std::vector<Vector3> getMapPowerWall(void) const;
    
        Texture2D getPowerBombTexture(void) const;
        Texture2D getPowerSpeedTexture(void) const;
        Texture2D getPowerNbTexture(void) const;

        void setMapBrick(std::vector<Vector3> br);
        void setMapEmpty(std::vector<Vector3> em);

        Vector3 getBlockSize(void) const;
        std::array<int, 195> getMap(void) const;
        void initMap();

    private:
        int mapHeight = 13;
        int mapWidth = 15;
        Vector3 BlockSize;
        std::vector<Vector3> brickPos;
        std::vector<Vector3> blockPos;
        std::vector<Vector3> emptyPos;
        std::vector<Vector3> powerBombPos;
        std::vector<Vector3> powerNbPos;
        std::vector<Vector3> powerSpeedPos;
        std::vector<Vector3> powerWallPos;
        Model brick;
        Texture pillar;
        Texture powerBomb;
        Texture powerNb;
        Texture powerSpeed;
        Texture powerWall;

        std::array<int, 195> map = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,9,
                                      1,8,8,0,0,0,0,0,0,0,0,0,8,8,9,
                                      1,8,1,0,1,0,1,0,1,0,1,0,1,8,9,
                                      1,0,0,0,0,0,0,0,0,0,0,0,0,0,9,
                                      1,0,1,0,1,0,1,0,1,0,1,0,1,0,9,
                                      1,0,0,0,0,0,0,0,0,0,0,0,0,0,9,
                                      1,0,1,0,1,0,1,0,1,0,1,0,1,0,9,
                                      1,0,0,0,0,0,0,0,0,0,0,0,0,0,9,
                                      1,0,1,0,1,0,1,0,1,0,1,0,1,0,9,
                                      1,0,0,0,0,0,0,0,0,0,0,0,0,0,9,
                                      1,8,1,0,1,0,1,0,1,0,1,0,1,8,9,
                                      1,8,8,0,0,0,0,0,0,0,0,0,8,8,9,
                                      1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };
};

#endif