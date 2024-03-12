#include "maze.h"
#include "raylib.h"

int perdeu = 0;

int maze[26][51] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

void DrawMaze()
{
    for (int i = 0; i < mazeWidth; i++)
    {
        for (int j = 0; j < mazeHeight; j++)
        {
            if (maze[i][j] == 1)
            {

                DrawRectangle((j * cellSize) + cellSize * 2.3, (i * cellSize) + cellSize * 4, cellSize, cellSize, RED);
            }
        }
    }
}

void ShowPlay(int screenWidth, int screenHeight, int tempominutos, int temposegundos, int pontuacaoPlacar)
{
    DrawText(TextFormat("%d:%d", tempominutos, temposegundos), screenWidth / 5, screenHeight / 15, 30, WHITE);
    DrawFPS(screenWidth / 10, screenHeight / 15);
    DrawText(TextFormat("SCORE: %d/12", pontuacaoPlacar), screenWidth / 2, screenHeight / 15, 30, WHITE);
}

void DrawPoster(Texture2D textureP, Poster poster, float scale)
{
    if (poster.isVisible)
    {
        DrawTextureEx(textureP, (Vector2){poster.x, poster.y}, 0.1f, scale, WHITE);
    }
}

// funcao responsavel por mudar 2 elementos na vertical da maze para formar as paredes

void drawwallvertical(int coluna, int linha1, int linha2)
{ // 1 coluna e 2 linhas

    int *ponteiro = &maze[linha1][coluna];  // Ponteiro apontando para o elemento da matriz
    int *ponteiro2 = &maze[linha2][coluna]; // Ponteiro apontando para o elemento da matriz
    if (*ponteiro == 1)
    {
        // Muda o valor do elemento para 0
        *ponteiro = 0;
        *ponteiro2 = 0;
    }
}
// funcao responsavel por mudar 2 elementos na horizontal da maze para formar as paredes
void drawwallhorizontal(int linha, int coluna1, int coluna2)
{ // 1 linhas e 2 coluna

    int *ponteiro = &maze[linha][coluna1];  // Ponteiro apontando para o elemento da matriz
    int *ponteiro2 = &maze[linha][coluna2]; // Ponteiro apontando para o elemento da matriz
    if (*ponteiro == 1)
    {
        // Muda o valor do elemento para 0
        *ponteiro = 0;
        *ponteiro2 = 0;
    }
}


void  drawwallverticalbloqueio(int coluna, int linha1, int linha2)
{ // 1 coluna e 2 linhas

    int *ponteiro = &maze[linha1][coluna];  // Ponteiro apontando para o elemento da matriz
    int *ponteiro2 = &maze[linha2][coluna]; // Ponteiro apontando para o elemento da matriz
    if (*ponteiro == 0)
    {
        // Muda o valor do elemento para 0
        *ponteiro = 1;
        *ponteiro2 = 1;
    }
}


void drawwallhorizontalbloqueio(int linha, int coluna1, int coluna2)
{ // 1 linhas e 2 coluna

    int *ponteiro = &maze[linha][coluna1];  // Ponteiro apontando para o elemento da matriz
    int *ponteiro2 = &maze[linha][coluna2]; // Ponteiro apontando para o elemento da matriz
    if (*ponteiro == 0)
    {
        // Muda o valor do elemento para 0
        *ponteiro = 1;
        *ponteiro2 = 1;
    }
}

//funcao que chama outras funcoes para fechar as passagens
void recomeco(){
         drawwallverticalbloqueio(4, 15, 16); // 1 coluna e 2 linhas
         drawwallhorizontalbloqueio(14, 8, 9); // 1 linhas e 2 coluna
         drawwallverticalbloqueio(37, 1, 2); // 1 coluna e 2 linhas
         drawwallhorizontalbloqueio(7, 43, 44); // 1 linhas e 2 coluna
         drawwallverticalbloqueio(4, 1, 2); // 1 coluna e 2 linhas
         drawwallhorizontalbloqueio(13, 22, 23); // 1 linhas e 2 coluna
         drawwallhorizontalbloqueio(11, 5, 6); // 1 linhas e 2 coluna
         drawwallverticalbloqueio(21, 1, 2); // 1 coluna e 2 linhas
         drawwallverticalbloqueio(20, 11, 12); // 1 coluna e 2 linhas
         drawwallhorizontalbloqueio(0, 46, 47); // 1 linhas e 2 coluna
                
}

 
 bool derrota( Vector2 quinhasmovimento, int radius, 
  Rectangle  retangulonalaurita1D, 
  Rectangle retangulonalaurita1E,  
  Rectangle retangulonalaurita2B ,
    Rectangle retangulonalaurita2C,
     Rectangle retangulonalaurita3C ,  
      Rectangle retangulonalaurita3B , 
       Rectangle retangulonalaurita4D,
       Rectangle retangulonalaurita4E,
         Rectangle retangulonalaurita5D,//
         Rectangle retangulonalaurita5E,
           Rectangle etangulonalaurita6D,
              Rectangle   retangulonalaurita7D,
                Rectangle  retangulonalaurita7E  ){

      if ( CheckCollisionCircleRec((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius,  retangulonalaurita1D)){
                         
                }

                  if ( CheckCollisionCircleRec((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius,  retangulonalaurita1E)){
                     return true;
                }

                  if ( CheckCollisionCircleRec((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius,  retangulonalaurita2B)){
                        return true;
                }

                  if ( CheckCollisionCircleRec((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius,  retangulonalaurita2C)){
                         return true;
                }

                  if ( CheckCollisionCircleRec((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius,  retangulonalaurita3C)){
                         return true;
                }

                  if ( CheckCollisionCircleRec((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius,  retangulonalaurita3B)){
                         return true;
                }

                  if ( CheckCollisionCircleRec((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius,  retangulonalaurita4D)){
                         return true;
                }
                if ( CheckCollisionCircleRec((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius,   retangulonalaurita4E)){
                         return true;
                }
                 if ( CheckCollisionCircleRec((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius,   retangulonalaurita5D)){
                         return true;
                }
                 if ( CheckCollisionCircleRec((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius,   retangulonalaurita5E)){
                         return true;
                }
                 if ( CheckCollisionCircleRec((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius,   etangulonalaurita6D)){
                         return true;
                }
                 if ( CheckCollisionCircleRec((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius,   retangulonalaurita7D)){
                         return true;
                }
                 if ( CheckCollisionCircleRec((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius,   retangulonalaurita7E)){
                         return true;
                }
            return false;

 }

 