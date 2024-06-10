/*
** File description:
** BombManager
*/

#include "BombManager.hpp"

BombManager::BombManager()
{
}

BombManager::~BombManager()
{
    // Unload texture
    UnloadSound(_bombSound);
    UnloadTexture(_textureBomb);
    UnloadModelAnimations(_bombAnims, _bombAnimsCount);
    UnloadModel(_bomb);
    // UnloadSound(fxBoom);
}

void BombManager::initBombManager(void)
{
    _bombAnimsCount = 0;
    _bombSound = LoadSound("assets/Sound/bombSound.mp3");
    _bomb = LoadModel("assets/Bomb/Bomb.iqm");
    _textureBomb = LoadTexture("assets/Bomb/textures/Bomb.png");
    SetMaterialTexture(&_bomb.materials[0], MATERIAL_MAP_DIFFUSE, _textureBomb);
    _bombAnims = LoadModelAnimations("assets/Bomb/BombIdleAnim.iqm", &_bombAnimsCount);
}

void BombManager::createBomb(Vector3 position, int powerBomb, Map &map, int *playerNbBomb)
{
    std::unique_ptr<Bomb> bomb = std::make_unique<Bomb>();

    bomb->initBomb(_bomb, _bombAnims, powerBomb);
    bomb->setBombPos(position, map);
    bomb->_playerNbBomb = playerNbBomb;
    _bombs.push_back(std::move(bomb));
}

void BombManager::draw(Map &map, uVector<Player> &players)
{
    for (int i = 0; i < _bombs.size(); i++) {
        _bombs[i]->draw(map, players);
    }
    checkExplodedBomb();
}

void BombManager::checkExplodedBomb()
{
    if (_bombs.size() > 0 && _bombs[0]->hasExploded()) {
        PlaySound(_bombSound);
        *(_bombs[0]->_playerNbBomb) += 1;
        _bombs.erase(_bombs.begin());
    }
}
