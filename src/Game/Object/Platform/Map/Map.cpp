/*
** File description:
** Map
*/

#include "Map.hpp"

Map::Map()
{
    brick = LoadModel("assets/Map/Brick/Brick.obj");
    pillar = LoadTexture("assets/Map/Pillar.png");
    powerBomb = LoadTexture("assets/PowerUps/PowerBomb.png");
    powerNb = LoadTexture("assets/PowerUps/NbBomb.png");
    powerSpeed = LoadTexture("assets/PowerUps/Speed.png");
    powerWall = LoadTexture("assets/PowerUps/ThrowBomb.png");

    createMap();
    setMapPos(map);
    BlockSize = {1.0f, 1.0f, 1.0f};
}

void Map::initMap(void)
{
}

Map::~Map()
{
    UnloadTexture(pillar);
    UnloadTexture(powerBomb);
    UnloadTexture(powerNb);
    UnloadTexture(powerSpeed);
    UnloadTexture(powerWall);
    UnloadModel(brick);
}

int Map::getMapHeight(void) const
{
    return mapHeight;
}

int Map::getMapWidth(void) const
{
    return mapWidth;
}

void Map::setMapHeight(int height)
{
    mapHeight = height;
}

void Map::setMapWidth(int width)
{
    mapWidth = width;
}

std::vector<Vector3> Map::getMapBrick(void) const
{
    return brickPos;
}

std::vector<Vector3> Map::getMapBlock(void) const
{
    return blockPos;
}

std::vector<Vector3> Map::getMapEmpty(void) const
{
    return emptyPos;
}

Vector3 Map::getBlockSize(void) const
{
    return BlockSize;
}

std::vector<Vector3> Map::getMapPowerBomb(void) const
{
    return powerBombPos;
}

std::vector<Vector3> Map::getMapPowerNb(void) const
{
    return powerNbPos;
}
std::vector<Vector3> Map::getMapPowerSpeed(void) const
{
    return powerSpeedPos;
}
std::vector<Vector3> Map::getMapPowerWall(void) const
{
    return powerWallPos;
}

std::array<int, 195> Map::getMap(void) const
{
    return map;
}

void Map::setMapBrick(std::vector<Vector3> br)
{
    brickPos = br;
}

Texture2D Map::getPowerBombTexture() const
{
    return powerBomb;
}

Texture2D Map::getPowerSpeedTexture() const
{
    return powerSpeed;
}

Texture2D Map::getPowerNbTexture() const
{
    return powerNb;
}

void Map::setMapPos(std::array<int, 195> m)
{
    Vector3 BlockPos = {-7.0f, 1.0f, 5.7f};

    brickPos.clear();
    emptyPos.clear();
    powerBombPos.clear();
    powerNbPos.clear();
    powerSpeedPos.clear();
    powerWallPos.clear();

    for (auto &a : m)
    {
        if (a == 1)
            blockPos.push_back(BlockPos);
        else if (a == 2)
            brickPos.push_back(BlockPos);
        else if (a == 0 || a == 8)
            emptyPos.push_back(BlockPos);
        else if (a == 13)
            brickPos.push_back(BlockPos);
        else if (a == 3)
            powerBombPos.push_back(BlockPos);
        else if (a == 14)
            brickPos.push_back(BlockPos);
        else if (a == 4)
            powerNbPos.push_back(BlockPos);
        else if (a == 15)
            brickPos.push_back(BlockPos);
        else if (a == 5)
            powerSpeedPos.push_back(BlockPos);
        else if (a == 16)
            brickPos.push_back(BlockPos);
        else if (a == 6)
            powerWallPos.push_back(BlockPos);
        else if (a == 9)
        {
            blockPos.push_back(BlockPos);
            BlockPos.z -= 1;
            BlockPos.x = -8.0;
        }
        BlockPos.x += 1;
    }
}

void Map::setMap(std::array<int, 195> m)
{
    map = m;
}

void Map::createMap()
{
    int r = 0;
    std::srand(std::time(nullptr));

    for (auto &a : map)
    {
        if (a == 0)
            r = std::rand() % 10;
        if (r == 1 && a == 0)
            a = 2;
        if (r == 2 && a == 0)
            a = 13;
        if (r == 3 && a == 0)
            a = 14;
        if (r == 4 && a == 0)
            a = 15;
        if (r == 5 && a == 0)
            a = 16;
        if (r == 6 && a == 0)
            a = 0;
        if (r <= 7 && a == 0)
            a = 2;
    }
}

void DrawCubeTexture(Texture2D texture, Vector3 position, float width, float height, float length, Color color)
{
    float x = position.x;
    float y = position.y;
    float z = position.z;

    // Set desired texture to be enabled while drawing following vertex data
    rlSetTexture(texture.id);

    // Vertex data transformation can be defined with the commented lines,
    // but in this example we calculate the transformed vertex data directly when calling rlVertex3f()
    // rlPushMatrix();
    // NOTE: Transformation is applied in inverse order (scale -> rotate -> translate)
    // rlTranslatef(2.0f, 0.0f, 0.0f);
    // rlRotatef(45, 0, 1, 0);
    // rlScalef(2.0f, 2.0f, 2.0f);

    rlBegin(RL_QUADS);
    rlColor4ub(color.r, color.g, color.b, color.a);
    // Front Face
    rlNormal3f(0.0f, 0.0f, 1.0f); // Normal Pointing Towards Viewer
    rlTexCoord2f(0.0f, 0.0f);
    rlVertex3f(x - width / 2, y - height / 2, z + length / 2); // Bottom Left Of The Texture and Quad
    rlTexCoord2f(1.0f, 0.0f);
    rlVertex3f(x + width / 2, y - height / 2, z + length / 2); // Bottom Right Of The Texture and Quad
    rlTexCoord2f(1.0f, 1.0f);
    rlVertex3f(x + width / 2, y + height / 2, z + length / 2); // Top Right Of The Texture and Quad
    rlTexCoord2f(0.0f, 1.0f);
    rlVertex3f(x - width / 2, y + height / 2, z + length / 2); // Top Left Of The Texture and Quad
    // Back Face
    rlNormal3f(0.0f, 0.0f, -1.0f); // Normal Pointing Away From Viewer
    rlTexCoord2f(1.0f, 0.0f);
    rlVertex3f(x - width / 2, y - height / 2, z - length / 2); // Bottom Right Of The Texture and Quad
    rlTexCoord2f(1.0f, 1.0f);
    rlVertex3f(x - width / 2, y + height / 2, z - length / 2); // Top Right Of The Texture and Quad
    rlTexCoord2f(0.0f, 1.0f);
    rlVertex3f(x + width / 2, y + height / 2, z - length / 2); // Top Left Of The Texture and Quad
    rlTexCoord2f(0.0f, 0.0f);
    rlVertex3f(x + width / 2, y - height / 2, z - length / 2); // Bottom Left Of The Texture and Quad
    // Top Face
    rlNormal3f(0.0f, 1.0f, 0.0f); // Normal Pointing Up
    rlTexCoord2f(0.0f, 1.0f);
    rlVertex3f(x - width / 2, y + height / 2, z - length / 2); // Top Left Of The Texture and Quad
    rlTexCoord2f(0.0f, 0.0f);
    rlVertex3f(x - width / 2, y + height / 2, z + length / 2); // Bottom Left Of The Texture and Quad
    rlTexCoord2f(1.0f, 0.0f);
    rlVertex3f(x + width / 2, y + height / 2, z + length / 2); // Bottom Right Of The Texture and Quad
    rlTexCoord2f(1.0f, 1.0f);
    rlVertex3f(x + width / 2, y + height / 2, z - length / 2); // Top Right Of The Texture and Quad
    // Bottom Face
    rlNormal3f(0.0f, -1.0f, 0.0f); // Normal Pointing Down
    rlTexCoord2f(1.0f, 1.0f);
    rlVertex3f(x - width / 2, y - height / 2, z - length / 2); // Top Right Of The Texture and Quad
    rlTexCoord2f(0.0f, 1.0f);
    rlVertex3f(x + width / 2, y - height / 2, z - length / 2); // Top Left Of The Texture and Quad
    rlTexCoord2f(0.0f, 0.0f);
    rlVertex3f(x + width / 2, y - height / 2, z + length / 2); // Bottom Left Of The Texture and Quad
    rlTexCoord2f(1.0f, 0.0f);
    rlVertex3f(x - width / 2, y - height / 2, z + length / 2); // Bottom Right Of The Texture and Quad
    // Right face
    rlNormal3f(1.0f, 0.0f, 0.0f); // Normal Pointing Right
    rlTexCoord2f(1.0f, 0.0f);
    rlVertex3f(x + width / 2, y - height / 2, z - length / 2); // Bottom Right Of The Texture and Quad
    rlTexCoord2f(1.0f, 1.0f);
    rlVertex3f(x + width / 2, y + height / 2, z - length / 2); // Top Right Of The Texture and Quad
    rlTexCoord2f(0.0f, 1.0f);
    rlVertex3f(x + width / 2, y + height / 2, z + length / 2); // Top Left Of The Texture and Quad
    rlTexCoord2f(0.0f, 0.0f);
    rlVertex3f(x + width / 2, y - height / 2, z + length / 2); // Bottom Left Of The Texture and Quad
    // Left Face
    rlNormal3f(-1.0f, 0.0f, 0.0f); // Normal Pointing Left
    rlTexCoord2f(0.0f, 0.0f);
    rlVertex3f(x - width / 2, y - height / 2, z - length / 2); // Bottom Left Of The Texture and Quad
    rlTexCoord2f(1.0f, 0.0f);
    rlVertex3f(x - width / 2, y - height / 2, z + length / 2); // Bottom Right Of The Texture and Quad
    rlTexCoord2f(1.0f, 1.0f);
    rlVertex3f(x - width / 2, y + height / 2, z + length / 2); // Top Right Of The Texture and Quad
    rlTexCoord2f(0.0f, 1.0f);
    rlVertex3f(x - width / 2, y + height / 2, z - length / 2); // Top Left Of The Texture and Quad
    rlEnd();
    // rlPopMatrix();

    rlSetTexture(0);
}
void Map::drawMap()
{
    Vector3 BlockPos = {-7.0f, 1.0f, 5.7f};
    int i = 0;

    for (auto &a : map)
    {
        if (i == 0)
        {
            BlockPos.y -= 1;
            DrawCube(BlockPos, 1, 1, 1, DARKGRAY);
            BlockPos.y += 1;
            i++;
        }
        else
        {
            BlockPos.y -= 1;
            DrawCube(BlockPos, 1, 1, 1, DARKGREEN);
            BlockPos.y += 1;
            i = 0;
        }
        if (a == 1)
            DrawCubeTexture(pillar, BlockPos, 1, 1, 1, WHITE);
        else if (a == 2 || a == 13 || a == 14 || a == 15 || a == 16)
            DrawModel(brick, BlockPos, 0.47f, WHITE);
        else if (a == 3)
            DrawCubeTexture(powerBomb, BlockPos, 0.5, 1, 0.5, WHITE);
        else if (a == 4)
            DrawCubeTexture(powerNb, BlockPos, 0.5, 1, 0.5, WHITE);
        else if (a == 5)
            DrawCubeTexture(powerSpeed, BlockPos, 0.5, 1, 0.5, WHITE);
        // else if (a == 6)
        //     DrawCubeTexture(powerWall, BlockPos, 0.5, 1, 0.5, WHITE);
        else if (a == 9)
        {
            DrawCubeTexture(pillar, BlockPos, 1, 1, 1, WHITE);
            BlockPos.z -= 1;
            BlockPos.x = -8.0;
        }
        BlockPos.x += 1;
    }
}
