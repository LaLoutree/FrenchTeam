#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <string.h>
#include <assert.h>
#include <queue>
#include <random>
#include <iomanip>
#include <ios>
#include <ostream>
#include "raylib.h"
#include <vector>
#include <unordered_map>
#include <stdexcept>

#include "Player.hpp"
#include "Map.hpp"
#include "BombManager.hpp"
#include "Menu.hpp"

class Engine {
    public:
        Engine();
        ~Engine();
        void runGame(void);

        void SaveGame(void);
        void LoadGame(int *nbPlayer);

        bool getbLoad();
        void setbLoad(bool _b_loaded);

        std::string getFilename();
        void setFilename(std::string _filename);

    protected:
    private:
        uVector<Player> _players;
        Map _map;
        BombManager _bombManager;
        Menu _menu;
        Camera _camera;
        void startDrawing(void);
        void endDrawing(int nbPlayers);
        void createPlayers(int nbPlayers);
        void createPlayer(int index);
        void updatePlayers();
        void drawPlayers();
        bool _startDrawing;
        void winCondition();

        bool _isLoad = false;
        bool fxButtonOff = true;

        std::string filename = "restore.bin";
        bool b_loaded = false;
        std::vector<Vector3> _brickPos;

        bool mouseOnText = false;
        Vector2 mouse = GetMousePosition();

        int nbPlayer;
        bool startGame;
        bool winCheck;
        std::string winnerText;
};

#endif /* !ENGINE_HPP_ */