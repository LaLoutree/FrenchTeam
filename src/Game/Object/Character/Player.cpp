/*
** File description:
** Player
*/

#include "Engine.hpp"

Player::Player()
{
}

Player::~Player()
{
    // UnloadModelAnimations(walkAnims, _walkAnimsCount);
    for (unsigned int i = 0; i < _walkAnimsCount; i++) {
        UnloadModelAnimation(walkAnims[i]);
    }
    RL_FREE(walkAnims);
    for (unsigned int i = 0; i < _idleAnimsCount; i++)
        UnloadModelAnimation(idleAnims[i]);
    RL_FREE(idleAnims);
    for (unsigned int i = 0; i < _deadAnimsCount; i++)
        UnloadModelAnimation(deadAnims[i]);
    RL_FREE(deadAnims);
    UnloadModel(player);
    UnloadTexture(texturePlayer);
}

void Player::initPlayer(const char *pathTexture)
{
    player = LoadModel("assets/Models/bombermanModel.iqm");
    texturePlayer = LoadTexture(pathTexture);
    SetMaterialTexture(&player.materials[0], MATERIAL_MAP_DIFFUSE, texturePlayer);

    // _walkAnimsCount = 0;
    walkAnims = LoadModelAnimations("assets/Animations/bombermanWalkAnim.iqm", &_walkAnimsCount);
    idleAnims = LoadModelAnimations("assets/Animations/bombermanIdleAnim.iqm", &_idleAnimsCount);
    deadAnims = LoadModelAnimations("assets/Animations/bombermanDeadAnim.iqm", &_idleAnimsCount);
    _nbBomb = 1;
    _powerBomb = 1;
    _speed = 0.05f;
    _passWall = false;

    _life = true;

    _idleAnimsCount = 0;
    _deadAnimsCount = 0;

    _walkAnimFrameCounter = 0;
    _idleAnimFrameCounter = 0;
    _deadAnimFrameCounter = 0;

    playerPos = { -6.0f, 1.0f, 4.7f };
    rotationAxis = { 2000.0f, 0.0f, 100.0f };
    scale = { 0.005f, 0.005f, 0.005f};
    playerSize = { 1.0f, 2.0f, 1.0f };
    rotationAngle = 1000.0f;
    color = WHITE;
    roll = 0;

    // keyRight = 262;
    // keyLeft = 263;
    // keyDown = 264;
    // keyUp = 265;
    // keyPlant = KEY_RIGHT_CONTROL;

    _colliBomb = false;
    _collision = false;
}

void Player::setPlayerPos(Vector3 pos)
{
    playerPos = pos;
}

Vector3 Player::getPlayerPos(void) const
{
    return playerPos;
}

Vector3 Player::getPlayerSize(void) const
{
    return playerSize;
}

void Player::setCollision(bool collision)
{
    _collision = collision;
}

bool Player::getCollision(void) const
{
    return _collision;
}

void Player::setWalkAnimsCount(unsigned int walkAnimsCount)
{
    _walkAnimsCount = walkAnimsCount;
}

void Player::setIdleAnimsCount(unsigned int idleAnimsCount)
{
    _idleAnimsCount = idleAnimsCount;
}

unsigned int Player::getWalkAnimsCount(void) const
{
    return _walkAnimsCount;
}

unsigned int Player::getIdleAnimsCount(void) const
{
    return _idleAnimsCount;
}

void Player::setWalkAnimFrameCounter(int walkAnimFrameCounter)
{
    _walkAnimFrameCounter = walkAnimFrameCounter;
}

void Player::setIdleAnimFrameCounter(int idleAnimFrameCounter)
{
    _idleAnimFrameCounter = idleAnimFrameCounter;
}

Model Player::getModelPlayer(void) const
{
    return player;
}

Texture2D Player::getTexturePlayer(void) const
{
    return texturePlayer;
}

int Player::getNbBomb(void) const
{
    return _nbBomb;
}

void Player::setNbBomb(int nb_bomb)
{
    _nbBomb = nb_bomb;
}

float Player::getPlayerSpeed() const
{
    return _speed;
}

Vector3 Player::getRotationAxis(void) const
{
    return rotationAxis;
}

Vector3 Player::getScale(void) const
{
    return scale;
}

int Player::getPowerBomb(void) const
{
    return _powerBomb;
}

void Player::setPowerBomb(int p)
{
    _powerBomb = p;
}

void Player::setPlayerLife(bool l)
{
    _life = l;
}

bool Player::getPlayerLife(void) const
{
    return _life;
}

void Player::setPlayerKey(int up, int left, int right, int down, int plant)
{
    keyRight = right;
    keyLeft = left;
    keyDown = down;
    keyUp = up;
    keyPlant = plant;
}

void destroyPower(Map &map, std::array<int, 195> *m, Vector3 destroy)
{
    Vector3 BlockPos = {-7.0f, 1.0f, 5.7f};

    for (auto &a: *m) {
        if (floor(BlockPos.x) == floor(destroy.x) && floor(BlockPos.z) == floor(destroy.z))
            a = 0;
        if (a == 9) {
            BlockPos.z -= 1;
            BlockPos.x = -8.0;
        }
        BlockPos.x += 1;
    }
    map.setMapPos(*m);
    map.setMap(*m);
}

void Player::checkCollisionPowerWall(Map &map, float offset1, float offset2)
{
    std::vector<Vector3> powerWall = map.getMapPowerWall();
    Vector3 BlockSize = map.getBlockSize();
    std::array<int, 195> m = map.getMap();

    for (int i = 0; i < powerWall.size(); i++) {
        if (CheckCollisionBoxes(
            (BoundingBox){(Vector3){ (playerPos.x + offset1) - playerSize.x/2,
                                     playerPos.y - playerSize.y/2,
                                     (playerPos.z + offset2)- playerSize.z/2 },
                          (Vector3){ (playerPos.x + offset1) + playerSize.x/2,
                                     playerPos.y + playerSize.y/2,
                                     (playerPos.z + offset2) + playerSize.z/2 }},
            (BoundingBox){(Vector3){ powerWall[i].x - 1/2,
                                     powerWall[i].y - 1/2,
                                     powerWall[i].z - 1/2 },
                          (Vector3){ powerWall[i].x + 1/2,
                                     powerWall[i].y + 1/2,
                                     powerWall[i].z + 1/2 }})) {
                                         destroyPower(map, &m, powerWall[i]);
                                         _passWall = true;
                                     }
    }
}

void Player::checkCollisionPowerSpeed(Map &map, float offset1, float offset2)
{
    std::vector<Vector3> powerSpeed = map.getMapPowerSpeed();
    Vector3 BlockSize = map.getBlockSize();
    std::array<int, 195> m = map.getMap();

    for (int i = 0; i < powerSpeed.size(); i++) {
        if (CheckCollisionBoxes(
            (BoundingBox){(Vector3){ (playerPos.x + offset1) - playerSize.x/2,
                                     playerPos.y - playerSize.y/2,
                                     (playerPos.z + offset2)- playerSize.z/2 },
                          (Vector3){ (playerPos.x + offset1) + playerSize.x/2,
                                     playerPos.y + playerSize.y/2,
                                     (playerPos.z + offset2) + playerSize.z/2 }},
            (BoundingBox){(Vector3){ powerSpeed[i].x - 1/2,
                                     powerSpeed[i].y - 1/2,
                                     powerSpeed[i].z - 1/2 },
                          (Vector3){ powerSpeed[i].x + 1/2,
                                     powerSpeed[i].y + 1/2,
                                     powerSpeed[i].z + 1/2 }})) {
                                         destroyPower(map, &m, powerSpeed[i]);
                                         _speed += 0.02f;
                                     }
    }
}

void Player::checkCollisionPowerNb(Map &map, float offset1, float offset2)
{
    std::vector<Vector3> powerNb = map.getMapPowerNb();
    Vector3 BlockSize = map.getBlockSize();
    std::array<int, 195> m = map.getMap();

    for (int i = 0; i < powerNb.size(); i++) {
        if (CheckCollisionBoxes(
            (BoundingBox){(Vector3){ (playerPos.x + offset1) - playerSize.x/2,
                                     playerPos.y - playerSize.y/2,
                                     (playerPos.z + offset2)- playerSize.z/2 },
                          (Vector3){ (playerPos.x + offset1) + playerSize.x/2,
                                     playerPos.y + playerSize.y/2,
                                     (playerPos.z + offset2) + playerSize.z/2 }},
            (BoundingBox){(Vector3){ powerNb[i].x - 1/2,
                                     powerNb[i].y - 1/2,
                                     powerNb[i].z - 1/2 },
                          (Vector3){ powerNb[i].x + 1/2,
                                     powerNb[i].y + 1/2,
                                     powerNb[i].z + 1/2 }})) {
                                         destroyPower(map, &m, powerNb[i]);
                                         _nbBomb += 1;
                                     }
    }
}

void Player::checkCollisionPowerBomb(Map &map, float offset1, float offset2)
{
    std::vector<Vector3> powerBomb = map.getMapPowerBomb();
    Vector3 BlockSize = map.getBlockSize();
    std::array<int, 195> m = map.getMap();

    for (int i = 0; i < powerBomb.size(); i++) {
        if (CheckCollisionBoxes(
            (BoundingBox){(Vector3){ (playerPos.x + offset1) - playerSize.x/2,
                                     playerPos.y - playerSize.y/2,
                                     (playerPos.z + offset2)- playerSize.z/2 },
                          (Vector3){ (playerPos.x + offset1) + playerSize.x/2,
                                     playerPos.y + playerSize.y/2,
                                     (playerPos.z + offset2) + playerSize.z/2 }},
            (BoundingBox){(Vector3){ powerBomb[i].x - 1/2,
                                     powerBomb[i].y - 1/2,
                                     powerBomb[i].z - 1/2 },
                          (Vector3){ powerBomb[i].x + 1/2,
                                     powerBomb[i].y + 1/2,
                                     powerBomb[i].z + 1/2 }})) {
                                         destroyPower(map, &m, powerBomb[i]);
                                         _powerBomb += 1;
                                     }
    }
}

void Player::checkCollisionBlock(Map &map, float offset1, float offset2)
{
    std::vector<Vector3> block = map.getMapBlock();
    Vector3 BlockSize = map.getBlockSize();

    for (int i = 0; i < block.size(); i++) {
        if (CheckCollisionBoxes(
            (BoundingBox){(Vector3){ (playerPos.x + offset1) - playerSize.x/2,
                                     playerPos.y - playerSize.y/2,
                                     (playerPos.z + offset2)- playerSize.z/2 },
                          (Vector3){ (playerPos.x + offset1) + playerSize.x/2,
                                     playerPos.y + playerSize.y/2,
                                     (playerPos.z + offset2) + playerSize.z/2 }},
            (BoundingBox){(Vector3){ block[i].x - 1/2,
                                     block[i].y - 1/2,
                                     block[i].z - 1/2 },
                          (Vector3){ block[i].x + 1/2,
                                     block[i].y + 1/2,
                                     block[i].z + 1/2 }})) _collision = true;
    }
}

void Player::checkCollisionBrick(Map &map, float offset1, float offset2)
{
    std::vector<Vector3> brick = map.getMapBrick();

    for (int i = 0; i < brick.size(); i++) {
        if (CheckCollisionBoxes(
            (BoundingBox){(Vector3){ (playerPos.x + offset1) - playerSize.x/2,
                                     playerPos.y - playerSize.y/2,
                                     (playerPos.z + offset2)- playerSize.z/2 },
                          (Vector3){ (playerPos.x + offset1) + playerSize.x/2,
                                     playerPos.y + playerSize.y/2,
                                     (playerPos.z + offset2) + playerSize.z/2 }},
            (BoundingBox){(Vector3){ brick[i].x - 1/2,
                                     brick[i].y - 1/2,
                                     brick[i].z - 1/2 },
                          (Vector3){ brick[i].x + 1/2,
                                     brick[i].y + 1/2,
                                     brick[i].z + 1/2 }})) {
            // if (_passWall == true) {
            //     _collision = false;
            //     _passWall = false;
            // } else
                _collision = true;
                                     }
    }
}

void Player::checkCollisionBomb(float offset1, float offset2)
{
    for (int i = 0; i < BombPos.size(); i++) {
        if (CheckCollisionBoxes(
            (BoundingBox){(Vector3){ (playerPos.x + offset1) - playerSize.x/2,
                                     playerPos.y - playerSize.y/2,
                                     (playerPos.z + offset2)- playerSize.z/2 },
                          (Vector3){ (playerPos.x + offset1) + playerSize.x/2,
                                     playerPos.y + playerSize.y/2,
                                     (playerPos.z + offset2) + playerSize.z/2 }},
            (BoundingBox){(Vector3){ BombPos[i].x - 1/2,
                                     BombPos[i].y - 1/2,
                                     BombPos[i].z - 1/2 },
                          (Vector3){ BombPos[i].x + 1/2,
                                     BombPos[i].y + 1/2,
                                     BombPos[i].z + 1/2 }})) _collision = true;
    }
}

void Player::checkCollision(Map &map, std::string direction)
{
    _collision = false;
    if (direction == "RIGHT") {
        checkCollisionBlock(map, 0.5, 0);
        checkCollisionBrick(map, 0.5, 0);
        checkCollisionPowerBomb(map, 0.5, 0);
        checkCollisionPowerNb(map, 0.5, 0);
        checkCollisionPowerSpeed(map, 0.5, 0);
        checkCollisionPowerWall(map, 0.5, 0);
    } else if (direction == "LEFT") {
        checkCollisionBlock(map, -0.5, 0);
        checkCollisionBrick(map, -0.5, 0);
        checkCollisionPowerBomb(map, -0.5, 0);
        checkCollisionPowerNb(map, -0.5, 0);
        checkCollisionPowerSpeed(map, -0.5, 0);
        checkCollisionPowerWall(map, -0.5, 0);
    } else if (direction == "DOWN") {
        checkCollisionBlock(map, 0, 0.5);
        checkCollisionBrick(map, 0, 0.5);
        checkCollisionPowerBomb(map, 0, 0.5);
        checkCollisionPowerNb(map, 0, 0.5);
        checkCollisionPowerSpeed(map, 0, 0.5);
        checkCollisionPowerWall(map, 0, 0.5);
    } else if (direction == "UP") {
        checkCollisionBlock(map, 0, -0.5);
        checkCollisionBrick(map, 0, -0.5);
        checkCollisionPowerBomb(map, 0, -0.5);
        checkCollisionPowerNb(map, 0, -0.5);
        checkCollisionPowerSpeed(map, 0, -0.5);
        checkCollisionPowerWall(map, 0, -0.5);
    }
}

void Player::animWalk(void)
{
    _walkAnimFrameCounter++;
    UpdateModelAnimation(player, walkAnims[0], _walkAnimFrameCounter);
    if (_walkAnimFrameCounter >= walkAnims[0].frameCount)
        _walkAnimFrameCounter = 0;

}

void Player::animIdle(void)
{
    _idleAnimFrameCounter++;
    UpdateModelAnimation(player, idleAnims[0], _idleAnimFrameCounter);
    if (_idleAnimFrameCounter >= idleAnims[0].frameCount)
        _idleAnimFrameCounter = 0;
}

void Player::animDead(void)
{
    _deadAnimFrameCounter++;
    UpdateModelAnimation(player, deadAnims[0], _deadAnimFrameCounter);
    if (_deadAnimFrameCounter >= deadAnims[0].frameCount)
        _deadAnimFrameCounter = 0;
}

void Player::movePlayer(std::string dir)
{
    if (dir == "RIGHT")
        playerPos.x += _speed;
    else if (dir == "LEFT")
        playerPos.x -= _speed;
    else if (dir == "DOWN")
        playerPos.z += _speed;
    else if (dir == "UP")
        playerPos.z -= _speed;
}

void Player::getRotation(void)
{
    if (IsKeyDown(keyDown)) roll = 1.0f;
    else if (IsKeyDown(keyUp)) roll = -540.0f;
    if (IsKeyDown(keyLeft)) roll = -90.0f;
    else if (IsKeyDown(keyRight)) roll = 90.0f;

    player.transform = MatrixRotateXYZ((Vector3){0, 0, DEG2RAD*roll });
}

void Player::animate()
{
    if (IsKeyDown(keyRight) || IsKeyDown(keyLeft) || IsKeyDown(keyDown) || IsKeyDown(keyUp))
        animWalk();
    else
        animIdle();
}

void Player::move(Map &map)
{
    if (IsKeyDown(keyRight)) {
        checkCollision(map, "RIGHT");
        if (getCollision() == false)
            movePlayer("RIGHT");
    } else if (IsKeyDown(keyLeft)) {
        checkCollision(map, "LEFT");
        if (getCollision() == false)
            movePlayer("LEFT");
    } else if (IsKeyDown(keyDown)) {
        checkCollision(map, "DOWN");
        if (getCollision() == false)
            movePlayer("DOWN");
    } else if (IsKeyDown(keyUp)) {
        checkCollision(map, "UP");
        if (getCollision() == false)
            movePlayer("UP");
    }
}

void Player::draw(void)
{
    if (_life)
        DrawModelEx(player, playerPos, rotationAxis, rotationAngle, scale, color);
    else
        animDead();
}

void Player::plantBomb(BombManager &bombManager, Map &map)
{
    if (IsKeyPressed(keyPlant) && _nbBomb > 0 && _life == true) {
        _nbBomb -= 1;
        bombManager.createBomb(playerPos, _powerBomb, map, &_nbBomb);
    }
}

void Player::update(Map &map, BombManager &bombManager)
{
    getRotation();
    animate();
    move(map);
    plantBomb(bombManager, map);
}