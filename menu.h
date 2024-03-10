#ifndef _MENU_H_
#define _MENU_H_

#include "raylib.h"

typedef enum
{
    STATE_MENU,
    STATE_CREDITS,
    STATE_PLAY,
    STATE_STORY,
    STATE_HOW_TO_PLAY,
    STATE_EXIT,
    STATE_WIN,
    STATE_LOSE
} GameState;

typedef struct
{
    Rectangle rect;
    Color color;
    Color hoverColor;
    const char *text;
} Button;

void DrawBorders(int borderWidth1, int borderWidth2, int borderWidth3, Color color1, Color color2, Color color3);
void DrawBase();
void DrawButton(Button button, int borderWidth1, Color borderColor1, int borderWidth2, Color borderColor2);
void ShowMenu(Texture2D background, Button startButton, Button howToPLayButton, Button creditsButton, Button exitButton);
void ShowStory(Texture2D texture);
void ShowHowToPlay(int screenWidth, int screenHeight, Texture2D textureHowToPlay, Button backButton);
void ShowCredits(int screenWidth, int screenHeight, Texture2D textureCredits, Button backButton);
void ShowWin(int screenWidth, int screenHeight, Texture2D textureWin, Button backButtonWin, Button exitButtonWin);
void ShowLose(int screenWidth, int screenHeight, Texture2D textureLose, Button backButtonLose, Button exitButtonLose);

#endif