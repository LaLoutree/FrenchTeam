/*
** File description:
** Main
*/

#ifndef MAIN_HPP_
#define MAIN_HPP_

#include <iostream>
#include <raylib.h>
#include <atomic>
#include "pthread.h"
#include <time.h>
#include <sstream>
#include <fstream>
#include <string>

#include "Map.hpp"
#include "BombManager.hpp"
#include "Player.hpp"

typedef enum GameScreen
{
    LOGO,
    TITLE,
    PAUSE,
    GAMEPLAY,
    SETTINGS,
    ENDING,
    CHOOSEPLAYER,
    EXIT,
} GameScreen;

class Menu
{
public:
    Menu();
    ~Menu();

    void runMenu(bool *_startDrawing, bool *_isLoad, int *nbPlayers);
    void initSound();
    void changeScreen(Vector2 *mouse, Rectangle positionButton, GameScreen *currentScreen, GameScreen SCREEN, bool *startGame);
    void manageButtonSettings(Vector2 *mouse, Rectangle positionButton, int check);
    Rectangle positionButton(float x, float y);
    Texture2D getTextureBackground();
    Vector2 getMouse();
    Rectangle getSourceRec();
    Rectangle getSourceRecArrow();

    void setSourceRecY(float y);
    float getFrameHeight();
    int getButtonState();

    Texture2D getTextureExitButton();
    Texture2D getTexturePlayButton();
    Texture2D getTextureSettingsButton();
    Texture2D getTextureBackButton();
    Texture2D getTextureMusicButton();
    Texture2D getTextureSaveButton();
    Texture2D getTextureArrowLeftButton();
    Texture2D getTextureArrowRightButton();

    Rectangle GetPlayButtonPos();
    Rectangle GetExitButtonPos();
    Rectangle GetSettingsButtonPos();
    Rectangle GetBackButtonPos();
    Rectangle GetMusicButtonPos();
    Rectangle GetSaveButtonPos();
    Rectangle GetArrowLeftButtonPos();
    Rectangle GetArrowRightButtonPos();
    Rectangle GetPlayChooseButtonPos();


    Rectangle *GetTextBox1();
    Rectangle *GetTextBox2();
    Rectangle *GetTextBox3();
    Rectangle *GetTextBox4();
    Rectangle *GetPlayerRec();

    std::array<std::string, 5> GetKey1();
    std::array<std::string, 5> GetKey2();
    std::array<std::string, 5> GetKey3();
    std::array<std::string, 5> GetKey4();

    bool *GetMouseOnText1();
    bool* GetMouseOnText2();
    bool* GetMouseOnText3();
    bool* GetMouseOnText4();
    bool* GetMouseOnText5();

    Sound GetSoundButton();
    Music GetMusic();

    void SetKey1(char key, int index);
    void SetKey2(char key, int index);
    void SetKey3(char key, int index);
    void SetKey4(char key, int index);
    void SetKey5(char key, int index);

    void SetCommands();
    void EditCommandsFile();


private:
    Vector2 mouse;

    // Button Variable
    int buttonState;
    bool buttonAction;
    float frameHeight;
    Rectangle buttonPos;
    Rectangle sourceRec;
    Rectangle sourceRecArrow;
    Sound fxButton;
    Music fxMusic;
    bool pauseMusic;

    // Textures & Image Menu
    Image backgroundImage;
    Texture2D background;
    Texture2D playButton;
    Texture2D exitButton;
    Texture2D settingsButton;
    Texture2D backButton;
    Texture2D musicButton;
    Texture2D saveButton;
    Texture2D arrowLeftButton;
    Texture2D arrowRightButton;
    Texture2D playChooseButton;

    Rectangle playButtonPos;
    Rectangle exitButtonPos;
    Rectangle settingsButtonPos;
    Rectangle musicButtonPos;
    Rectangle saveButtonPos;
    Rectangle backButtonPos;
    Rectangle arrowLeftButtonPos;
    Rectangle arrowRightButtonPos;
    Rectangle playChooseButtonPos;

    Rectangle players[4] = {
        { 25, 100, 350, 400, },
        { 525, 100, 350, 400, },
        { 1025, 100, 350, 400, },
        { 1525, 100, 350, 400, },
    };

    Rectangle textBox1[5] = {
        { 275, 225, 45, 40 },
        { 275, 275, 45, 40 },
        { 275, 325, 45, 40 },
        { 275, 375, 45, 40 },
        { 275, 425, 45, 40 },
    };
    Rectangle textBox2[5] = {
        { 775, 225, 45, 40 },
        { 775, 275, 45, 40 },
        { 775, 325, 45, 40 },
        { 775, 375, 45, 40 },
        { 775, 425, 45, 40 },
    };
    Rectangle textBox3[5] = {
        { 1275, 225, 45, 40 },
        { 1275, 275, 45, 40 },
        { 1275, 325, 45, 40 },
        { 1275, 375, 45, 40 },
        { 1275, 425, 45, 40 },
    };
    Rectangle textBox4[5] = {
        { 1775, 225, 45, 40 },
        { 1775, 275, 45, 40 },
        { 1775, 325, 45, 40 },
        { 1775, 375, 45, 40 },
        { 1775, 425, 45, 40 },
    };

    std::array<std::string, 5> key1;
    std::array<std::string, 5> key2;
    std::array<std::string, 5> key3;
    std::array<std::string, 5> key4;
    bool mouseOnText1[5] = { false, false, false, false, false };
    bool mouseOnText2[5] = { false, false, false, false, false };
    bool mouseOnText3[5] = { false, false, false, false, false };
    bool mouseOnText4[5] = { false, false, false, false, false };

};

#endif /* !MAIN_HPP_ */