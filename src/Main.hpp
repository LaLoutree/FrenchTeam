/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-abdoulaye.doucoure
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

class Main {
    public:
        Main();
        ~Main();
        void setscreenWidth(int);
        int getscreenWidth();
        void setscreenHeight(int);
        int getscreenHeight();
        void setgame(Image i);
        Image getgame();
        void setimage(Image i);
        Image getimage();
        void settexturep(Texture2D t);
        Texture2D gettexturep();
        void settextureg(Texture2D tg);
        Texture2D gettextureg();
        void setpositionp(Vector2 v);
        Vector2 getpositionp();
        void setpositiong(Vector2 p);
        Vector2 getpositiong();

    private:
    int screenWidth;
    int screenHeight;
    Image parrots;
    Image game;
    Texture2D texturep;
    Texture2D textureg;
    Vector2 positionp;
    Vector2 positiong;
};

typedef enum GameScreen
{
    LOGO = 0,
    TITLE,
    TIT,
    GAMEPLAY,
    ENDING
} GameScreen;
#endif /* !MAIN_HPP_ */
