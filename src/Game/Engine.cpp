/*
** File description:
** Engine
*/

#include "Engine.hpp"
#include "Serialize.hpp"

Engine::Engine()
{
    _camera = { {0.0f, 20.0f, 5.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, 45.0f, 0 };

    _startDrawing = false;
    _map.initMap();

    _bombManager.initBombManager();
    startGame = false;
    winCheck = false;
    nbPlayer = 1;
}

Engine::~Engine()
{
}

void CheckMouseOnText(Menu& _menu, Rectangle* textBoxes, bool* mouseOnText, int* indexTextBox) {
    for (int i = 0; i < 5; ++i) {
        if (CheckCollisionPointRec(GetMousePosition(), textBoxes[i])) {
            mouseOnText[i] = true;
            *indexTextBox = i;
        }
        else
            mouseOnText[i] = false;
    }
}

bool IsAnyMouseOnText(Menu& _menu, int& activeTextBoxIndex)
{
    bool* mouseOnTextArrays[] = { _menu.GetMouseOnText1(), _menu.GetMouseOnText2(), _menu.GetMouseOnText3(), _menu.GetMouseOnText4() };
    const int numArrays = sizeof(mouseOnTextArrays) / sizeof(mouseOnTextArrays[0]);

    for (int i = 0; i < numArrays; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (mouseOnTextArrays[i][j]) {
                activeTextBoxIndex = i;
                return true;
            }
        }
    }

    return false;
}

void DrawTextBox(Rectangle rect, const std::string& text, bool mouseOn)
{
    DrawRectangleRec(rect, LIGHTGRAY);
    if (mouseOn)
        DrawRectangleLines((int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height, RED);
    else
        DrawRectangleLines((int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height, DARKGRAY);
    DrawText(text.c_str(), (int)rect.x + 17, (int)rect.y + 8, 20, MAROON);
}


void Engine::runGame(void)
{
    Vector3 BombPos = { 0 };

    GameScreen currentScreen = LOGO;
    int framesCounter = 0;
    pthread_t threadId = { 0 };

    SetTargetFPS(60);
    InitAudioDevice();
    _menu.initSound();
    PlayMusicStream(_menu.GetMusic());

    while (!WindowShouldClose()) {
        UpdateCamera(&_camera);
        UpdateMusicStream(_menu.GetMusic());
        switch (currentScreen) {
        case LOGO: {
            framesCounter++;
            if (framesCounter > 120)
                currentScreen = TITLE;
        } break;
        case TITLE: {
            Vector2 mouse = GetMousePosition();
            // Button play
            _menu.changeScreen(&mouse, _menu.GetPlayButtonPos(), &currentScreen, CHOOSEPLAYER, &startGame);
            // _menu.setSourceRecY(_menu.getButtonState() * _menu.getFrameHeight());

            // Button settings
            _menu.changeScreen(&mouse, _menu.GetSettingsButtonPos(), &currentScreen, SETTINGS, &startGame);
            // _menu.setSourceRecY(_menu.getButtonState() * _menu.getFrameHeight());

            // Button exit
            _menu.changeScreen(&mouse, _menu.GetExitButtonPos(), &currentScreen, EXIT, &startGame);

            // _menu.etSourceRecY(_menu.etButtonState() * _menu.etFrameHeight());
        } break;
        case SETTINGS: {
            Vector2 mouse = GetMousePosition();
            int letterCount = 0;
            int indexTextBox1 = -1;
            int indexTextBox2 = -1;
            int indexTextBox3 = -1;
            int indexTextBox4 = -1;

            // void CheckMouseOnText(Menu & _menu, Rectangle * textBoxes, bool* mouseOnText, int* indexTextBox) {

            CheckMouseOnText(_menu, _menu.GetTextBox1(), _menu.GetMouseOnText1(), &indexTextBox1);
            CheckMouseOnText(_menu, _menu.GetTextBox2(), _menu.GetMouseOnText2(), &indexTextBox2);
            CheckMouseOnText(_menu, _menu.GetTextBox3(), _menu.GetMouseOnText3(), &indexTextBox3);
            CheckMouseOnText(_menu, _menu.GetTextBox4(), _menu.GetMouseOnText4(), &indexTextBox4);

            int activeTextBoxIndex = -1;

            if (IsAnyMouseOnText(_menu, activeTextBoxIndex)) {
                SetMouseCursor(MOUSE_CURSOR_IBEAM);
                int key = GetCharPressed();
                if (key > 0) {
                    switch (activeTextBoxIndex) {
                    case 0:
                        _menu.SetKey1((char)key, indexTextBox1);
                        break;
                    case 1:
                        _menu.SetKey2((char)key, indexTextBox2);
                        break;
                    case 2:
                        _menu.SetKey3((char)key, indexTextBox3);
                        break;
                    case 3:
                        _menu.SetKey4((char)key, indexTextBox4);
                        break;
                    default:
                        letterCount++;
                        break;
                    };
                    key = GetCharPressed();
                }
                if (IsKeyPressed(KEY_BACKSPACE)) {
                    letterCount--;
                    if (letterCount < 0) letterCount = 0;
                    switch (activeTextBoxIndex) {
                    case 0:
                        _menu.SetKey1('\0', indexTextBox1);
                        break;
                    case 1:
                        _menu.SetKey2('\0', indexTextBox2);
                        break;
                    case 2:
                        _menu.SetKey3('\0', indexTextBox3);
                        break;
                    case 3:
                        _menu.SetKey4('\0', indexTextBox4);
                        break;
                    default:
                        break;
                    };
                }
                else SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
            _menu.manageButtonSettings(&mouse, _menu.GetMusicButtonPos(), 1);
            _menu.manageButtonSettings(&mouse, _menu.GetSaveButtonPos(), 2);
            _menu.changeScreen(&mouse, _menu.GetBackButtonPos(), &currentScreen, TITLE, &startGame);
        } break;
        case CHOOSEPLAYER:
        {
            mouse = GetMousePosition();

            if (CheckCollisionPointRec(mouse, _menu.GetArrowLeftButtonPos())) {
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                    if (nbPlayer < 4)
                        nbPlayer++;
                    else nbPlayer = 4;
                }
            }
            if (CheckCollisionPointRec(mouse, _menu.GetArrowRightButtonPos())) {
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                    if (nbPlayer > 1)
                        nbPlayer--;
                    else nbPlayer = 1;
                }
            }
            _menu.changeScreen(&mouse, _menu.GetPlayChooseButtonPos(), &currentScreen, GAMEPLAY, &startGame);
            _menu.changeScreen(&mouse, _menu.GetBackButtonPos(), &currentScreen, TITLE, &startGame);

        } break;
        case GAMEPLAY: {
            mouse = GetMousePosition();
            if (startGame == true) {
                createPlayers(nbPlayer);
                startGame = false;
            }
            Rectangle backButtonPos = { static_cast<float>(GetScreenWidth()) / 2 - ((float)_menu.getTextureBackButton().width * 5.0f) / 2, static_cast<float>(GetScreenHeight()) / 2 - ((float)_menu.getTextureBackButton().height * 5.0f) / 2, (float)_menu.getTextureBackButton().width * 5.0f, (float)_menu.getTextureBackButton().height * 5.0f };

            _menu.changeScreen(&mouse, backButtonPos, &currentScreen, EXIT, &startGame);

            updatePlayers();
            winCondition();
        } break;
        case EXIT: {
            exit(true);
        } break;
        default:
            break;
        };

        startDrawing();
        switch (currentScreen)
        {
        case LOGO:
        {
            int textWidth = MeasureText("MADE BY THE FRENCH TEAM.", 20);
            DrawText("MADE BY THE FRENCH TEAM.", GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2, 20, BLACK);
        }
        break;
        case TITLE:
        {
            DrawTexture(_menu.getTextureBackground(), (GetScreenWidth() / 2) - (_menu.getTextureBackground().width / 2), (GetScreenHeight() / 2) - (_menu.getTextureBackground().height / 2), WHITE);
            // DrawTextureRec(_menu.getTexturePlayButton(), _menu.getSourceRec(), playButtonPos, WHITE);
            DrawTexturePro(_menu.getTexturePlayButton(), _menu.getSourceRec(), _menu.GetPlayButtonPos(), (Vector2) { 5, 5.0 }, 0, WHITE);
            DrawTexturePro(_menu.getTextureExitButton(), _menu.getSourceRec(), _menu.GetExitButtonPos(), (Vector2) { 5, 5.0 }, 0, WHITE);
            DrawTexturePro(_menu.getTextureSettingsButton(), _menu.getSourceRec(), _menu.GetSettingsButtonPos(), (Vector2) { 5, 5.0 }, 0, WHITE);
        }
        break;
        case SETTINGS:
        {
            ClearBackground(DARKBLUE);

            DrawRectangleLinesEx(_menu.GetPlayerRec()[0], 4, RED);
            DrawText("PLAYER 1", 75, 125, 40, BLACK);
            DrawRectangleLinesEx(_menu.GetPlayerRec()[1], 4, BLACK);
            DrawText("PLAYER 2", 575, 125, 40, BLACK);
            DrawRectangleLinesEx(_menu.GetPlayerRec()[2], 4, ORANGE);
            DrawText("PLAYER 3", 1075, 125, 40, BLACK);
            DrawRectangleLinesEx(_menu.GetPlayerRec()[3], 4, GREEN);
            DrawText("PLAYER 4", 1575, 125, 40, BLACK);
            for (int i = 0, x = 0; i < 5; ++i, x += 500) {
                DrawText("UP:", 75 + x, 225, 20, WHITE);
                DrawText("LEFT:", 75 + x, 275, 20, WHITE);
                DrawText("RIGHT:", 75 + x, 325, 20, WHITE);
                DrawText("DOWN:", 75 + x, 375, 20, WHITE);
                DrawText("ACTION:", 75 + x, 425, 20, WHITE);
                // Joueur 1
                DrawTextBox(_menu.GetTextBox1()[i], _menu.GetKey1()[i], _menu.GetMouseOnText1()[i]);
                // Joueur 2
                DrawTextBox(_menu.GetTextBox2()[i], _menu.GetKey2()[i], _menu.GetMouseOnText2()[i]);
                // Joueur 3
                DrawTextBox(_menu.GetTextBox3()[i], _menu.GetKey3()[i], _menu.GetMouseOnText3()[i]);
                // Joueur 4
                DrawTextBox(_menu.GetTextBox4()[i], _menu.GetKey4()[i], _menu.GetMouseOnText4()[i]);
            }
            DrawTexturePro(_menu.getTextureMusicButton(), _menu.getSourceRec(), _menu.GetMusicButtonPos(), (Vector2) { 5, 5.0 }, 0, WHITE);
            DrawTexturePro(_menu.getTextureSaveButton(), _menu.getSourceRec(), _menu.GetSaveButtonPos(), (Vector2) { 5, 5.0 }, 0, WHITE);
            DrawTexturePro(_menu.getTextureBackButton(), _menu.getSourceRec(), _menu.GetBackButtonPos(), (Vector2) { 5, 5.0 }, 0, WHITE);

        }
        break;
        case CHOOSEPLAYER: {
            ClearBackground(DARKBLUE);

            int textWidth = MeasureText("NB OF PLAYER: 0", 20);
            DrawText(TextFormat("NB OF PLAYER: %d", nbPlayer), GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2, 30, WHITE);
            DrawTexturePro(_menu.getTextureArrowLeftButton(), _menu.getSourceRecArrow(), _menu.GetArrowLeftButtonPos(), (Vector2) { 5, 5.0 }, 0, WHITE);
            DrawTexturePro(_menu.getTextureArrowRightButton(), _menu.getSourceRecArrow(), _menu.GetArrowRightButtonPos(), (Vector2) { 5, 5.0 }, 0, WHITE);
            DrawTexturePro(_menu.getTexturePlayButton(), _menu.getSourceRec(), _menu.GetPlayChooseButtonPos(), (Vector2) { 5, 5.0 }, 0, WHITE);
            DrawTexturePro(_menu.getTextureBackButton(), _menu.getSourceRec(), _menu.GetBackButtonPos(), (Vector2) { 5, 5.0 }, 0, WHITE);

        } break;
        case GAMEPLAY:
        {
            ClearBackground(GRAY);
            BeginMode3D(_camera);
            _map.drawMap();
            _bombManager.draw(_map, _players);
            drawPlayers();
            EndMode3D();

            if (!_players.empty()) {
                for (size_t i = 0; i < _players.size(); ++i) {

                    if (i == 0)
                        DrawText("PLAYER 1", 10, 10, 30, RED);
                    if (i == 1)
                        DrawText("PLAYER 2", GetScreenWidth() - 160, GetScreenHeight() - 40, 30, BLACK);
                    if (i == 2)
                        DrawText("PLAYER 3", GetScreenWidth() - 160, 10, 30, GREEN);
                    if (i == 3)
                        DrawText("PLAYER 4", 10, GetScreenHeight() - 40, 30, ORANGE);
                    // Position de départ pour dessiner les informations du joueur i
                    Vector2 startPos;
                    const float xOffset = 15.0f;
                    const float yOffset = 45.0f;

                    if (i == 0) { // Player 1 en haut à gauche
                        startPos.x = xOffset;
                        startPos.y = yOffset;
                    }
                    else if (i == 1) { // Player 2 en bas à droite
                        startPos.x = GetScreenWidth() - 200.0f;
                        startPos.y = GetScreenHeight() - 230.0f;
                    }
                    else if (i == 2) { // Player 3 en haut à droite
                        startPos.x = GetScreenWidth() - 200.0f;
                        startPos.y = yOffset;
                    }
                    else if (i == 3) { // Player 4 en bas à gauche
                        startPos.x = xOffset;
                        startPos.y = GetScreenHeight() - 230.0f;
                    }

                    // Dessiner les informations du joueur i
                    DrawTextureEx(_map.getPowerBombTexture(), startPos, 0, 0.5, WHITE);
                    DrawText(TextFormat(": %d", _players[i]->getPowerBomb()), startPos.x + 65, startPos.y + 20, 30, RED);
                    DrawTextureEx(_map.getPowerNbTexture(), { startPos.x, startPos.y + 55 }, 0, 0.5, WHITE);
                    DrawText(TextFormat(": %d", _players[i]->getNbBomb()), startPos.x + 65, startPos.y + 75, 30, RED);
                    DrawTextureEx(_map.getPowerSpeedTexture(), { startPos.x, startPos.y + 110 }, 0, 0.5, WHITE);
                    DrawText(TextFormat(": %0.2f", _players[i]->getPlayerSpeed()), startPos.x + 65, startPos.y + 135, 30, RED);
                }
            }
            if (winCheck == true) {
                Rectangle modalPos = { static_cast<float>(GetScreenWidth()) / 2 - 500 / 2, static_cast<float>(GetScreenHeight()) / 2 - 150 / 2, 500, 350 };
                DrawRectangleRounded(modalPos, 0, 20, GRAY);
                DrawText(winnerText.c_str(), GetScreenWidth() / 2 - MeasureText(winnerText.c_str(), 30) / 2, GetScreenHeight() / 2, 30, WHITE);
                Rectangle backButtonPos = { static_cast<float>(GetScreenWidth()) / 2 - ((float)_menu.getTextureBackButton().width * 5.0f) / 2, static_cast<float>(GetScreenHeight()) / 2 - ((float)_menu.getTextureBackButton().height * 5.0f) / 2, (float)_menu.getTextureBackButton().width * 5.0f, (float)_menu.getTextureBackButton().height * 5.0f};
                DrawTexturePro(_menu.getTextureExitButton(), _menu.getSourceRec(), backButtonPos, (Vector2) { 5, 5.0 }, 0, WHITE);
            }
        }
        break;
        default:
            break;
        };
        EndDrawing();
    }
    CloseAudioDevice();
    CloseWindow();
}

void Engine::winCondition()
{
    int count = nbPlayer;
    int index = 0;

    for (int i = 0; i < nbPlayer; i++) {
        if (_players[i]->getPlayerLife() == false)
            count--;
        else
            index = i + 1;
    }

    if (count == 1 && nbPlayer != 1) {
        winnerText = TextFormat("PLAYER %d WON !", index);
        winCheck = true;
    } else winCheck = false;
}

void Engine::startDrawing(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
}

KeyboardKey stringToKeyboardKey(const std::string& str) {
    static const std::unordered_map<std::string, KeyboardKey> keyMap = {
        {"a", KEY_A}, {"b", KEY_B}, {"c", KEY_C}, {"d", KEY_D}, {"e", KEY_E},
        {"f", KEY_F}, {"g", KEY_G}, {"h", KEY_H}, {"i", KEY_I}, {"j", KEY_J},
        {"k", KEY_K}, {"l", KEY_L}, {"m", KEY_M}, {"n", KEY_N}, {"o", KEY_O},
        {"p", KEY_P}, {"q", KEY_Q}, {"r", KEY_R}, {"s", KEY_S}, {"t", KEY_T},
        {"u", KEY_U}, {"v", KEY_V}, {"w", KEY_W}, {"x", KEY_X}, {"y", KEY_Y},
        {"z", KEY_Z}, {"ZERO", KEY_ZERO}, {"ONE", KEY_ONE}, {"TWO", KEY_TWO},
        {"THREE", KEY_THREE}, {"FOUR", KEY_FOUR}, {"FIVE", KEY_FIVE}, {"SIX", KEY_SIX},
        {"SEVEN", KEY_SEVEN}, {"EIGHT", KEY_EIGHT}, {"NINE", KEY_NINE}, {"SPACE", KEY_SPACE},
        {"ENTER", KEY_ENTER}, {"ESCAPE", KEY_ESCAPE}, {"LEFT_SHIFT", KEY_LEFT_SHIFT},
        {"RIGHT_SHIFT", KEY_RIGHT_SHIFT}, {"LEFT_CONTROL", KEY_LEFT_CONTROL},
        {"RIGHT_CONTROL", KEY_RIGHT_CONTROL}, {"LEFT_ALT", KEY_LEFT_ALT},
        {"RIGHT_ALT", KEY_RIGHT_ALT}, {"BACKSPACE", KEY_BACKSPACE},
        {"TAB", KEY_TAB}, {"DELETE", KEY_DELETE}, {"UP", KEY_UP}, {"DOWN", KEY_DOWN},
        {"LEFT", KEY_LEFT}, {"RIGHT", KEY_RIGHT}, {"F1", KEY_F1}, {"F2", KEY_F2},
        {"F3", KEY_F3}, {"F4", KEY_F4}, {"F5", KEY_F5}, {"F6", KEY_F6}, {"F7", KEY_F7},
        {"F8", KEY_F8}, {"F9", KEY_F9}, {"F10", KEY_F10}, {"F11", KEY_F11}, {"F12", KEY_F12}
        // Ajoutez les autres touches nécessaires
    };

    auto it = keyMap.find(str);
    if (it != keyMap.end()) {
        return it->second;
    }
    else {
        throw std::invalid_argument("Invalid keyboard key string: " + str);
    }
}

void Engine::createPlayers(int nbPlayers)
{
    const char* modelPaths[4] = {
        "assets/Models/textures/WhiteBomberMan.png",
        "assets/Models/textures/BlackBomberMan.png",
        "assets/Models/textures/GreenBomberMan.png",
        "assets/Models/textures/OrangeBomberMan.png" };

    std::array<KeyboardKey, 5> keyboardKeys1;
    std::array<KeyboardKey, 5> keyboardKeys2;
    std::array<KeyboardKey, 5> keyboardKeys3;
    std::array<KeyboardKey, 5> keyboardKeys4;

    KeyboardKey defaultKeys[4][5] = {
           {KEY_UP, KEY_LEFT, KEY_RIGHT, KEY_DOWN, KEY_RIGHT_CONTROL},
           {KEY_TWO, KEY_Q, KEY_E, KEY_W, KEY_R},
           {KEY_S, KEY_Z, KEY_C, KEY_X, KEY_V},
           {KEY_I, KEY_J, KEY_L, KEY_K, KEY_H},
    };

    try {
        auto keys1 = _menu.GetKey1();
        auto keys2 = _menu.GetKey2();
        auto keys3 = _menu.GetKey3();
        auto keys4 = _menu.GetKey4();

        for (size_t i = 0; i < 5; ++i) {
            keyboardKeys1[i] = keys1[i].empty() ? KEY_NULL : stringToKeyboardKey(keys1[i]);
            keyboardKeys2[i] = keys2[i].empty() ? KEY_NULL : stringToKeyboardKey(keys2[i]);
            keyboardKeys3[i] = keys3[i].empty() ? KEY_NULL : stringToKeyboardKey(keys3[i]);
            keyboardKeys4[i] = keys4[i].empty() ? KEY_NULL : stringToKeyboardKey(keys4[i]);
        }
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error initializing keyboard keys: " << e.what() << std::endl;
    }
    // Array to hold the final keybindings
    KeyboardKey keybindings[4][5];

    // Initialize keybindings
    for (int i = 0; i < 5; ++i) {
        keybindings[0][i] = (keyboardKeys1[i] == KEY_NULL) ? defaultKeys[0][i] : keyboardKeys1[i];
        keybindings[1][i] = (keyboardKeys2[i] == KEY_NULL) ? defaultKeys[1][i] : keyboardKeys2[i];
        keybindings[2][i] = (keyboardKeys3[i] == KEY_NULL) ? defaultKeys[2][i] : keyboardKeys3[i];
        keybindings[3][i] = (keyboardKeys4[i] == KEY_NULL) ? defaultKeys[3][i] : keyboardKeys4[i];
    }

    Vector3 positions[4] = {
        {-6.0f, 1.0f, -5.5f},
        {6.0f, 1.0f, 4.5f},
        {6.0f, 1.0f, -5.5f},
        {-6.0f, 1.0f, 4.5f} };

    for (int i = 0; i < nbPlayers; i++)
    {
        std::unique_ptr<Player> player = std::make_unique<Player>();

        player->initPlayer(modelPaths[i]);
        player->setPlayerPos(positions[i]);
        player->setPlayerKey(keybindings[i][0], keybindings[i][1], keybindings[i][2], keybindings[i][3], keybindings[i][4]);
        _players.push_back(std::move(player));
    }
}

void Engine::updatePlayers()
{
    for (size_t i = 0; i < _players.size(); i++)
        _players[i]->update(_map, _bombManager);
}

void Engine::drawPlayers()
{
    for (size_t i = 0; i < _players.size(); i++)
    {
        if (_players[i]->getPlayerLife())
            _players[i]->draw();
    }
}