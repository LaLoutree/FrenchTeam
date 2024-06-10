#include "Menu.hpp"

Menu::Menu()
{
    // Initialize Texture & Image
    backgroundImage = LoadImage("assets/Menu/Background.png");
    ImageResize(&backgroundImage, GetScreenWidth(), GetScreenHeight());
    background = LoadTextureFromImage(backgroundImage);

    playButton = LoadTexture("assets/Menu/PlayButton.png");
    exitButton = LoadTexture("assets/Menu/ExitButton.png");
    settingsButton = LoadTexture("assets/Menu/SettingsButton.png");
    backButton = LoadTexture("assets/Menu/BackButton.png");
    musicButton = LoadTexture("assets/Menu/MusicButton.png");
    saveButton = LoadTexture("assets/Menu/SaveButton.png");
    backButton = LoadTexture("assets/Menu/BackButton.png");
    arrowLeftButton = LoadTexture("assets/Menu/ArrowLeftButton.png");
    arrowRightButton = LoadTexture("assets/Menu/ArrowRightButton.png");

    // Initialize Button
    buttonState = 0;
    buttonAction = false;
    // frameHeight = playButton.height / 3;
    sourceRec = { 0, 0, (float)playButton.width, (float)playButton.height };
    playButtonPos = { GetScreenWidth() / 2.0f - (playButton.width) - 2.0f - (float)playButton.width,
        GetScreenHeight() / 2.0f - (playButton.height) - 2.0f - (float)playButton.height,
        (float)playButton.width * 5.0f,
        (float)playButton.height * 5.0f };
    settingsButtonPos = { GetScreenWidth() / 2.0f - (settingsButton.width) - 2.0f - (float)settingsButton.width,
        GetScreenHeight() / 2.0f - (settingsButton.height) - 2.0f - (float)settingsButton.height + 100,
        (float)settingsButton.width * 5.0f,
        (float)settingsButton.height * 5.0f
    };
    exitButtonPos = { GetScreenWidth() / 2.0f - (exitButton.width) - 2.0f - (float)exitButton.width,
        GetScreenHeight() / 2.0f - (exitButton.height) - 2.0f - (float)exitButton.height + 205,
        (float)exitButton.width * 5.0f,
        (float)exitButton.height * 5.0f };

    musicButtonPos = { GetScreenWidth() / 2.0f - (musicButton.width) - 2.0f - (float)musicButton.width,
                     GetScreenHeight() / 2.0f - (musicButton.height) - 2.0f - (float)musicButton.height + 305,
                     (float)musicButton.width * 5.0f,
                     (float)musicButton.height * 5.0f };
    saveButtonPos = { GetScreenWidth() / 2.0f - (saveButton.width) - 2.0f - (float)saveButton.width + 305,
                     GetScreenHeight() / 2.0f - (saveButton.height) - 2.0f - (float)saveButton.height + 305,
                     (float)saveButton.width * 5.0f,
                     (float)saveButton.height * 5.0f };

    backButtonPos = { GetScreenWidth() / 2.0f - (backButton.width) - 2.0f - (float)backButton.width - 305,
                     GetScreenHeight() / 2.0f - (backButton.height) - 2.0f - (float)backButton.height + 305,
                     (float)backButton.width * 5.0f,
                     (float)backButton.height * 5.0f };

    arrowLeftButtonPos = { GetScreenWidth() / 2.0f - (arrowLeftButton.width) - 2.0f - (float)arrowLeftButton.width + 305,
                     GetScreenHeight() / 2.0f - (arrowLeftButton.height) - 2.0f - (float)arrowLeftButton.height,
                     (float)arrowLeftButton.width * 5.0f,
                     (float)arrowLeftButton.height * 5.0f };

    arrowRightButtonPos = { GetScreenWidth() / 2.0f - (arrowRightButton.width) - 2.0f - (float)arrowRightButton.width - 305,
                     GetScreenHeight() / 2.0f - (arrowRightButton.height) - 2.0f - (float)arrowRightButton.height,
                     (float)arrowRightButton.width * 5.0f,
                     (float)arrowRightButton.height * 5.0f };

    playChooseButtonPos = { GetScreenWidth() / 2.0f - (playButton.width) - 2.0f - (float)playButton.width,
        GetScreenHeight() / 2.0f - (playButton.height) - 2.0f - (float)playButton.height + 305,
        (float)playButton.width * 5.0f,
        (float)playButton.height * 5.0f };
    sourceRecArrow = { 0, 0, (float)arrowLeftButton.width, (float)arrowLeftButton.height };
    fxButton = LoadSound("assets/Sounds/buttonfx.mp3");
    // SetCommands();
}

Menu::~Menu()
{
    UnloadTexture(playButton);
    UnloadTexture(exitButton);
    UnloadTexture(settingsButton);
    UnloadTexture(backButton);
    UnloadTexture(background);
    UnloadImage(backgroundImage);
    UnloadMusicStream(fxMusic);
    UnloadSound(fxButton);
}

void Menu::initSound()
{
    fxButton = LoadSound("assets/Sounds/buttonfx.mp3");
    fxMusic = LoadMusicStream("assets/Sounds/2.mp3");
}

Music Menu::GetMusic()
{
    return fxMusic;
}

Rectangle Menu::GetPlayButtonPos()
{
    return playButtonPos;
}

Rectangle Menu::GetExitButtonPos()
{
    return exitButtonPos;
}

Rectangle Menu::GetSettingsButtonPos()
{
    return settingsButtonPos;
}

Rectangle Menu::GetMusicButtonPos()
{
    return musicButtonPos;
}

Rectangle Menu::GetSaveButtonPos()
{
    return saveButtonPos;
}

Rectangle Menu::GetBackButtonPos()
{
    return backButtonPos;
}

Rectangle Menu::GetArrowLeftButtonPos()
{
    return arrowLeftButtonPos;
}

Rectangle Menu::GetArrowRightButtonPos()
{
    return arrowRightButtonPos;
}

Rectangle Menu::GetPlayChooseButtonPos()
{
    return playChooseButtonPos;
}

Texture2D Menu::getTextureBackground()
{
    return background;
}

Vector2 Menu::getMouse()
{
    return mouse;
}

Rectangle Menu::getSourceRec()
{
    return sourceRec;
}

Rectangle Menu::getSourceRecArrow()
{
    return sourceRecArrow;
}

void Menu::setSourceRecY(float y)
{
    sourceRec.y = y;
}

float Menu::getFrameHeight()
{
    return frameHeight;
}

int Menu::getButtonState()
{
    return buttonState;
}

Texture2D Menu::getTextureExitButton()
{
    return exitButton;
}
Texture2D Menu::getTexturePlayButton()
{
    return playButton;
}

Texture2D Menu::getTextureSettingsButton()
{
    return settingsButton;
}

Texture2D Menu::getTextureBackButton()
{
    return backButton;
}

Texture2D Menu::getTextureMusicButton()
{
    return musicButton;
}

Texture2D Menu::getTextureSaveButton()
{
    return saveButton;
}

Texture2D Menu::getTextureArrowLeftButton()
{
    return arrowLeftButton;
}

Texture2D Menu::getTextureArrowRightButton()
{
    return arrowRightButton;
}

Sound Menu::GetSoundButton()
{
    return fxButton;
}

Rectangle* Menu::GetTextBox1()
{
    return textBox1;
}

Rectangle* Menu::GetTextBox2()
{
    return textBox2;
}

Rectangle* Menu::GetTextBox3()
{
    return textBox3;
}

Rectangle* Menu::GetTextBox4()
{
    return textBox4;
}

Rectangle* Menu::GetPlayerRec()
{
    return players;
}

bool* Menu::GetMouseOnText1()
{
    return mouseOnText1;
}

bool* Menu::GetMouseOnText2()
{
    return mouseOnText2;
}

bool* Menu::GetMouseOnText3()
{
    return mouseOnText3;
}

bool* Menu::GetMouseOnText4()
{
    return mouseOnText4;
}

std::array<std::string, 5> Menu::GetKey1()
{
    return key1;
}

std::array<std::string, 5> Menu::GetKey2()
{
    return key2;
}

std::array<std::string, 5> Menu::GetKey3()
{
    return key3;
}

std::array<std::string, 5> Menu::GetKey4()
{
    return key4;
}

void Menu::SetKey1(char key, int index)
{
    key1[index] = key;
}

void Menu::SetKey2(char key, int index)
{
    key2[index] = key;
}
void Menu::SetKey3(char key, int index)
{
    key3[index] = key;
}
void Menu::SetKey4(char key, int index)
{
    key4[index] = key;
}

void Menu::changeScreen(Vector2* mouse, Rectangle positionButton, GameScreen* currentScreen, GameScreen SCREEN, bool *startGame)
{
    if (CheckCollisionPointRec(*mouse, positionButton)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            PlaySound(fxButton);
            if (SCREEN == GAMEPLAY)
                *startGame = true;
            *currentScreen = SCREEN;
        }
    }
}

void Menu::manageButtonSettings(Vector2* mouse, Rectangle positionButton, int check)
{
    if (CheckCollisionPointRec(*mouse, positionButton)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && check == 1) {
            pauseMusic = !pauseMusic;

            if (pauseMusic) PauseMusicStream(fxMusic);
            else ResumeMusicStream(fxMusic);
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && check == 2) {
            PlaySound(fxButton);
            EditCommandsFile();
        }
    }
}

Rectangle Menu::positionButton(float x, float y)
{
    Rectangle buttonPos = { GetScreenWidth() / 2.0f - playButton.width / 2.0f - x, GetScreenHeight() / 2.0f - playButton.height / 3 / 2.0f + y, (float)playButton.width, frameHeight };

    return buttonPos;
}

void Menu::EditCommandsFile() {
    std::ostringstream text;
    std::ifstream in_file("src/Game/Loop/Display/commands.txt");

    if (!in_file.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return;
    }

    text << in_file.rdbuf();
    std::string str = text.str();
    in_file.close();

    std::vector<std::string> searchStrings = {
        "up1:", "down1:", "left1:", "right1:", "action1:",
        "up2:", "down2:", "left2:", "right2:", "action2:",
        "up3:", "down3:", "left3:", "right3:", "action3:",
        "up4:", "down4:", "left4:", "right4:", "action4:"
    };

    std::array<std::string, 5> keyArrays[] = { key1, key2, key3, key4 };

    std::string modifiedStr = str;
    size_t offset = 0;

    for (size_t i = 0; i < 4; ++i) {  // Pour chaque joueur
        for (size_t j = 0; j < 5; ++j) {  // Pour chaque commande
            size_t pos = modifiedStr.find(searchStrings[i * 5 + j], offset);
            if (pos != std::string::npos) {
                if (!keyArrays[i][j].empty()) {
                    size_t endPos = modifiedStr.find_first_of("\n", pos);
                    std::string existingKey = modifiedStr.substr(pos + searchStrings[i * 5 + j].length(), endPos - pos - searchStrings[i * 5 + j].length());
                    if (!existingKey.empty()) {
                        modifiedStr.replace(pos + searchStrings[i * 5 + j].length(), existingKey.length(), keyArrays[i][j]);
                    }
                    else {
                        modifiedStr.insert(pos + searchStrings[i * 5 + j].length(), keyArrays[i][j]);
                    }
                }
                offset = pos + searchStrings[i * 5 + j].length() + keyArrays[i][j].length();
            }
        }
    }

    std::ofstream out_file("src/Game/Loop/Display/commands.txt");
    out_file << modifiedStr;
    out_file.close();
}


// void Menu::SetCommands()
// {
//     std::ifstream inputFile("src/Game/Loop/Display/commands.txt");
//     int i = 0;
//     int index = 0;

//     if (!inputFile.is_open()) {
//         std::cerr << "Error opening the file!" << std::endl;
//         return;
//     }

//     key1.fill("");
//     key2.fill("");
//     key3.fill("");
//     key4.fill("");

//     std::string currentPlayer;
//     std::string line;
//     while (std::getline(inputFile, line) && !line.empty()) {
//         if (line.find("player") != std::string::npos) {
//             currentPlayer = line;
//             index = 0;
//         }
//         else {
//             size_t pos = line.find(':');
//             if (pos != std::string::npos) {
//                 std::string value = line.substr(pos + 1);
//                 if (currentPlayer == "player1")
//                     key1[index] = value;
//                 else if (currentPlayer == "player2")
//                     key2[index] = value;
//                 else if (currentPlayer == "player3")
//                     key3[index] = value;
//                 else if (currentPlayer == "player4")
//                     key4[index] = value;
//             }
//         }
//     }
//     inputFile.close();
// }