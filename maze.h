#ifndef _MAZE_H_
#define _MAZE_H_

#include "raylib.h"

#define cellSize 34
#define mazeWidth 25
#define mazeHeight 50
#define NUM_POSTERS 12

typedef struct
{
    int x;
    int y;
    bool isVisible;
} Poster;

void DrawMaze();
void ShowPlay(int screenWidth, int screenHeight, int tempominutos, int temposegundos, int pontuacaoPlacar);
void DrawPoster(Texture2D textureP, Poster poster, float scale);
void drawwallvertical(int coluna, int linha1, int linha2);
void drawwallhorizontal(int linha, int coluna1, int coluna2);
/*void DrawPoster(Texture2D textureP, int posX, int posY, float scale)
{
    DrawTextureEx(textureP, (Vector2){posX, posY}, 0.1f, scale, WHITE);
}
void DrawPoster(Texture2D textureP, Poster poster, float scale) {
    if (poster.isVisible) {
        DrawTextureEx(textureP, (Vector2){poster.x, poster.y}, 0.1f, scale, WHITE);
    }
}*/

#endif