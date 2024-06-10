/*
** File description:
** BombManager
*/

#ifndef BOMBMANAGER_HPP_
#define BOMBMANAGER_HPP_

#include "Bomb.hpp"

class Player;

class BombManager {
    public:
        BombManager();
        ~BombManager();
        void draw(Map &map, uVector<Player> &players);
        void createBomb(Vector3 position, int powerBomb, Map &map, int *playerNbBomb);
        void initBombManager(void);
        void checkExplodedBomb();

    protected:
    private:
        Sound _bombSound;
        uVector<Bomb> _bombs;
        ModelAnimation *_bombAnims;
        Model _bomb;
        Texture2D _explosion;
        Texture2D _textureBomb;
        unsigned int _bombAnimsCount;
};

#endif /* !BOMBMANAGER_HPP_ */
