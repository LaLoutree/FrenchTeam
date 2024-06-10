/*
** File description:
** Bomb
*/

#include "Bomb.hpp"
#include "Player.hpp"

Bomb::Bomb()
{
}
Bomb::~Bomb()
{
}

void Bomb::initBomb(Model bomb, ModelAnimation *bombAnims, int powerBomb)
{
    _bomb = bomb;
    _bombAnims = bombAnims;
    _powerBomb = 1;
    _idleBombAnimFrameCounter = 0;

    _powerBomb = powerBomb;

    rotationAxis = { 2000.0f, 0.0f, 100.0f };
    rotationAngle = 1000.0f;
    scale = { 1.0f, 1.0f, 1.0f };
    color = WHITE;
    explosionTime = 0.0f;
    exploded = false;
}

void Bomb::animIdleBomb(void)
{
    _idleBombAnimFrameCounter++;
    UpdateModelAnimation(_bomb, _bombAnims[0], _idleBombAnimFrameCounter);
    if (_idleBombAnimFrameCounter >= _bombAnims[0].frameCount)
        _idleBombAnimFrameCounter = 0;
}

void destroyBrick(Map &map, std::array<int, 195> *m, Vector3 destroy)
{
    Vector3 BlockPos = {-7.0f, 1.0f, 5.7f};

    for (auto &a: *m) {
        if (floor(BlockPos.x) == floor(destroy.x) && floor(BlockPos.z) == floor(destroy.z)) {
            if (a == 13)
                a = 3;
            if (a == 14)
                a = 4;
            if (a == 15)
                a = 5;
            if (a == 16)
                a = 6;
            if (a == 2)
                a = 0;
        }
        if (a == 9) {
            BlockPos.z -= 1;
            BlockPos.x = -8.0;
        }
        BlockPos.x += 1;
    }
    map.setMapPos(*m);
    map.setMap(*m);
}

void Bomb::draw(Map &map, uVector<Player> &players)
{
    double t = GetTime();

    if (explosionTime == 0)
        explosionTime = t + 3;
    if (t < explosionTime) {
        DrawModelEx(_bomb, bombPos, rotationAxis, rotationAngle, scale, color);
        animIdleBomb();
    } else {
        doExplosion(map, players);
        explosionTime = 0.0f;
        exploded = true;
    }
}

void Bomb::doExplosion(Map &map, uVector<Player> &players)
{
    std::array<int, 195> m = map.getMap();
    bool right = true;
    bool left = true;
    bool down = true;
    bool up = true;
    bool *directions[4] = { &right, &left, &down, &up };

    DrawCube(bombPos, 1, 1, 1, RED);
    for (int bombPower = 0; bombPower < _powerBomb + 1; bombPower++) {
        checkExplosionBlock(map, directions, bombPower);
        doExplosionBrick(map, directions, m, bombPower);
        doExplosionEmpty(map, directions, bombPower);
        checkExplosionPlayer(directions, players, bombPower);
    }
}

void Bomb::checkExplosionBlock(Map &map, bool *directions[4], int bombPower)
{
    std::vector<Vector3> block = map.getMapBlock();

    for (int i = 0; i < block.size(); i++) {
        if (floor(bombPos.x + bombPower) == floor(block[i].x) && floor(bombPos.z) == floor(block[i].z)) {
            *directions[B_RIGHT] = false;
        }
        if (floor(bombPos.x - bombPower) == floor(block[i].x) && floor(bombPos.z) == floor(block[i].z)) {
            *directions[B_LEFT] = false;
        }
        if (floor(bombPos.x) == floor(block[i].x) && floor(bombPos.z + bombPower) == floor(block[i].z)) {
            *directions[B_DOWN] = false;
        }
        if (floor(bombPos.x) == floor(block[i].x) && floor(bombPos.z - bombPower) == floor(block[i].z)) {
            *directions[B_UP] = false;
        }
    }
}

void Bomb::doExplosionBrick(Map &map, bool *directions[4], std::array<int, 195> &m, int bombPower)
{
    std::vector<Vector3> brick = map.getMapBrick();

     for (int i = 0; i < brick.size(); i++) {
        if (*directions[B_RIGHT] && floor(bombPos.x + bombPower) == floor(brick[i].x) && floor(bombPos.z) == floor(brick[i].z)) {
            *directions[B_RIGHT] = false;
            bombPos.x += bombPower;
            DrawCube(bombPos, 1, 1, 1, RED);
            destroyBrick(map, &m, bombPos);
            bombPos.x -= bombPower;
        }
        if (*directions[B_LEFT] && floor(bombPos.x - bombPower) == floor(brick[i].x) && floor(bombPos.z) == floor(brick[i].z)) {
            *directions[B_LEFT] = false;
            bombPos.x -= bombPower;
            DrawCube(bombPos, 1, 1, 1, RED);
            destroyBrick(map, &m, bombPos);
            bombPos.x += bombPower;
        }
        if (*directions[B_DOWN] && floor(bombPos.x) == floor(brick[i].x) && floor(bombPos.z + bombPower) == floor(brick[i].z)) {
            *directions[B_DOWN] = false;
            bombPos.z += bombPower;
            DrawCube(bombPos, 1, 1, 1, RED);
            destroyBrick(map, &m, bombPos);
            bombPos.z -= bombPower;
        }
        if (*directions[B_UP] && floor(bombPos.x) == floor(brick[i].x) && floor(bombPos.z - bombPower) == floor(brick[i].z)) {
            *directions[B_UP] = false;
            bombPos.z -= bombPower;
            DrawCube(bombPos, 1, 1, 1, RED);
            destroyBrick(map, &m, bombPos);
            bombPos.z += bombPower;
        }
    }
}

void Bomb::doExplosionEmpty(Map &map, bool *directions[4], int bombPower)
{
    std::vector<Vector3> empty = map.getMapEmpty();

    for (int i = 0; i < empty.size(); i++) {
        if (*directions[B_RIGHT] && floor(bombPos.x + bombPower) == floor(empty[i].x) && floor(bombPos.z) == floor(empty[i].z)) {
            bombPos.x += bombPower;
            DrawCube(bombPos, 1, 1, 1, RED);
            bombPos.x -= bombPower;
        }
        if (*directions[B_LEFT] && floor(bombPos.x - bombPower) == floor(empty[i].x) && floor(bombPos.z) == floor(empty[i].z)) {
            bombPos.x -= bombPower;
            DrawCube(bombPos, 1, 1, 1, RED);
            bombPos.x += bombPower;
        }
        if (*directions[B_DOWN] && floor(bombPos.x) == floor(empty[i].x) && floor(bombPos.z + bombPower) == floor(empty[i].z)){
            bombPos.z += bombPower;
            DrawCube(bombPos, 1, 1, 1, RED);
            bombPos.z -= bombPower;
        }
        if (*directions[B_UP] && floor(bombPos.x) == floor(empty[i].x) && floor(bombPos.z - bombPower) == floor(empty[i].z)){
            bombPos.z -= bombPower;
            DrawCube(bombPos, 1, 1, 1, RED);
            bombPos.z += bombPower;
        }
    }
}

void Bomb::checkExplosionPlayer(bool *directions[4], uVector<Player> &players, int bombPower)
{
    // for (int i = 0; i < players.size(); i++) {
    //     checkCollisionBomb(players, i);
    // }
    for (int i = 0; i < players.size(); i++) {
        Vector3 playerPos = players[i]->getPlayerPos();
        Vector3 playerSize = players[i]->getPlayerSize();
        BoundingBox playerBoundingBox = (BoundingBox) {
            (Vector3) {
                floor(playerPos.x) - playerSize.x/2, floor(playerPos.y) - playerSize.y/2, floor(playerPos.z) - playerSize.z/2
            },
            (Vector3) {
                floor(playerPos.x) + playerSize.x/2, floor(playerPos.y) + playerSize.y/2, floor(playerPos.z) + playerSize.z/2
            }
        };
        BoundingBox bombMidBoundingBox = (BoundingBox) {
            (Vector3) {
                floor(bombPos.x) - 1/2, floor(bombPos.y) - 1/2, floor(bombPos.z) - 1/2
            },
            (Vector3) {
                floor(bombPos.x) + 1/2, floor(bombPos.y) + 1/2, floor(bombPos.z) + 1/2
            }
        };
        BoundingBox bombRightBoundingBox = (BoundingBox) {
            (Vector3) {
                floor(bombPos.x + bombPower) - 1/2, floor(bombPos.y) - 1/2, floor(bombPos.z) - 1/2
            },
            (Vector3) {
                floor(bombPos.x + bombPower) + 1/2, floor(bombPos.y) + 1/2, floor(bombPos.z) + 1/2
            }
        };
        BoundingBox bombLeftBoundingBox = (BoundingBox) {
            (Vector3) {
                floor(bombPos.x - bombPower) - 1/2, floor(bombPos.y) - 1/2, floor(bombPos.z) - 1/2
            },
            (Vector3) {
                floor(bombPos.x - bombPower) + 1/2, floor(bombPos.y) + 1/2, floor(bombPos.z) + 1/2
            }
        };
        BoundingBox bombDownBoundingBox = (BoundingBox) {
            (Vector3) {
                floor(bombPos.x) - 1/2, floor(bombPos.y) - 1/2, floor(bombPos.z + bombPower) - 1/2
            },
            (Vector3) {
                floor(bombPos.x) + 1/2, floor(bombPos.y) + 1/2, floor(bombPos.z + bombPower) + 1/2
            }
        };
        BoundingBox bombUpBoundingBox = (BoundingBox) {
            (Vector3) {
                floor(bombPos.x) - 1/2, floor(bombPos.y) - 1/2, floor(bombPos.z - bombPower) - 1/2
            },
            (Vector3) {
                floor(bombPos.x) + 1/2, floor(bombPos.y) + 1/2, floor(bombPos.z - bombPower) + 1/2
            }
        };

        if (CheckCollisionBoxes(playerBoundingBox, bombMidBoundingBox) ||
            (*directions[B_RIGHT] && CheckCollisionBoxes(playerBoundingBox, bombRightBoundingBox)) ||
            (*directions[B_LEFT] && CheckCollisionBoxes(playerBoundingBox, bombLeftBoundingBox)) ||
            (*directions[B_DOWN] && CheckCollisionBoxes(playerBoundingBox, bombDownBoundingBox)) ||
            (*directions[B_UP] && CheckCollisionBoxes(playerBoundingBox, bombUpBoundingBox))) {
            players[i]->setPlayerLife(false);
        }
    }
}

void Bomb::checkCollisionBomb(uVector<Player> &players, int index)
{
    Vector3 playerPos = players[index]->getPlayerPos();
    Vector3 playerSize = players[index]->getPlayerSize();
    BoundingBox playerBoundingBox = (BoundingBox) {
        (Vector3) {
            floor(playerPos.x) - playerSize.x/2, floor(playerPos.y) - playerSize.y/2, floor(playerPos.z) - playerSize.z/2
        },
        (Vector3) {
            floor(playerPos.x) + playerSize.x/2, floor(playerPos.y) + playerSize.y/2, floor(playerPos.z) + playerSize.z/2
        }
    };
    BoundingBox bombBoundingBox = (BoundingBox) {
        (Vector3) {
            floor(bombPos.x) - 1/2, floor(bombPos.y) - 1/2, floor(bombPos.z) - 1/2
        },
        (Vector3) {
            floor(bombPos.x) + 1/2, floor(bombPos.y) + 1/2, floor(bombPos.z) + 1/2
        }
    };

    if (CheckCollisionBoxes(playerBoundingBox, bombBoundingBox))
        players[index]->setCollision(true);
}

void Bomb::setBombPos(Vector3 position, Map &map)
{
    float x = floor(position.x);
    // float x = position.x > 0 ? floor(position.x - 1): floor(position.x + 1);
    float z = floor(position.z);
    std::vector<Vector3> m = map.getMapEmpty();
    Vector3 neww = { 0 };

    if (x <= -7)
        x = -6;
    if (x >= 7)
        x = 6;
    if (z <= -7)
        z = -6;
    if (z >= 5)
        z = 4;

    // std::cout << "X = " << position.x << " Posx = " << floor(position.x) <<  "\n";

    neww = {x, position.y, z + 0.6f};
    bombPos = neww;
}

bool Bomb::hasExploded(void) const
{
    return exploded;
}