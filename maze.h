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
    int isVisible;
} Poster;

void DrawMaze();
void recomeco();
bool derrota ();
void  drawwallverticalbloqueio();
void  drawwallhorizontalbloqueio();
void ShowPlay(int screenWidth, int screenHeight, int tempominutos, int temposegundos, int pontuacaoPlacar);
void DrawPoster(Texture2D textureP, Poster poster, float scale);
void drawwallvertical(int coluna, int linha1, int linha2);
void drawwallhorizontal(int linha, int coluna1, int coluna2);


#endif