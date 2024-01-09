#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "abertura.h"

int main()
{
    // Inicializacao
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Abertura do jogo");

    // Musica
    InitAudioDevice();
    Music music = LoadMusicStream("assets/mini1111.wav");
    music.looping = false;

    PlayMusicStream(music);

    bool pause = false; // Fazer um botao de mudo dps

    // Fonte
    Font font = LoadFont("resources/fonts/pixantiqua.png");

    SetTargetFPS(60);

    // Imagem
    Image image = LoadImage("assets/nomeJogo.png");
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);

    SetTargetFPS(60);

    // Botoes do menu
    Button startButton = {(Rectangle){330, 200, 140, 40}, PINK, "COMEÇAR"};
    Button howToPLayButton = {(Rectangle){330, 250, 140, 40}, PINK, "COMO JOGAR"};
    Button creditsButton = {(Rectangle){330, 300, 140, 40}, PINK, "CRÉDITOS"};
    Button exitButton = {(Rectangle){330, 350, 140, 40}, PINK, "SAIR"};
    Button backButton = {(Rectangle){330, 350, 140, 40}, PINK, "VOLTAR"};

    GameState gameState = STATE_MENU;

    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);

        BeginDrawing();

        ClearBackground(BLACK);
        DrawBorders(8, 5, 5, PINK, BLACK, PINK);

        switch (gameState)
        {
        case STATE_MENU:
            int screenWidth = GetScreenWidth();
            int textureWidth = texture.width;
            int posX = (screenWidth - textureWidth) / 2;
            // Nome do jogo
            DrawTexture(texture, posX, 50, WHITE);

            // Desenha botoes
            DrawButton(startButton, 2, PINK, 4, BLACK);
            DrawButton(howToPLayButton, 2, PINK, 4, BLACK);
            DrawButton(creditsButton, 2, PINK, 4, BLACK);
            DrawButton(exitButton, 2, PINK, 4, BLACK);

            // Menu
            if (CheckCollisionPointRec(GetMousePosition(), startButton.rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                // Inicia jogo
                gameState = STATE_PLAY;
            }
            if (CheckCollisionPointRec(GetMousePosition(), howToPLayButton.rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                // Como Jogar
                gameState = STATE_HOW_TO_PLAY;
            }
            if (CheckCollisionPointRec(GetMousePosition(), creditsButton.rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                // Creditos
                gameState = STATE_CREDITS;
            }
            if (CheckCollisionPointRec(GetMousePosition(), exitButton.rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                // Sai do jogo
                gameState = STATE_EXIT;
            }
            break;
        case STATE_PLAY:
            DrawMaze();
            break;
        case STATE_HOW_TO_PLAY:
            DrawButton(backButton, 2, PINK, 4, BLACK);
            if (CheckCollisionPointRec(GetMousePosition(), backButton.rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                gameState = STATE_MENU;
            }
            break;
        case STATE_CREDITS:
            DrawButton(backButton, 2, PINK, 4, BLACK);
            if (CheckCollisionPointRec(GetMousePosition(), backButton.rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                gameState = STATE_MENU;
            }
            break;
        case STATE_EXIT:
            // Encerramento
            // Musica
            UnloadMusicStream(music);
            CloseAudioDevice();
            // Descarregamento da fonte
            UnloadFont(font);

            CloseWindow();
            return 0;
            break;
            // Nao sei se pode fazer isso
        }

        EndDrawing();
    }
}

void DrawBorders(int borderWidth1, int borderWidth2, int borderWidth3, Color color1, Color color2, Color color3)
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    DrawRectangle(0, 0, screenWidth, borderWidth1, color1);
    DrawRectangle(0, screenHeight - borderWidth1, screenWidth, borderWidth1, color1);

    DrawRectangle(borderWidth1, borderWidth1, screenWidth - 2 * borderWidth1, borderWidth2, color2);
    DrawRectangle(borderWidth1, screenHeight - borderWidth1 - borderWidth2, screenWidth - 2 * borderWidth1, borderWidth2, color2);

    DrawRectangle(borderWidth1 + borderWidth2, borderWidth1 + borderWidth2, screenWidth - 2 * borderWidth1 - 2 * borderWidth2, borderWidth3, color3);
    DrawRectangle(borderWidth1 + borderWidth2, screenHeight - borderWidth1 - borderWidth2 - borderWidth3, screenWidth - 2 * borderWidth1 - 2 * borderWidth2, borderWidth3, color3);

    DrawRectangle(0, 0, borderWidth1, screenHeight, color1);
    DrawRectangle(screenWidth - borderWidth1, 0, borderWidth1, screenHeight, color1);

    DrawRectangle(borderWidth1, borderWidth1, borderWidth2, screenHeight - 2 * borderWidth1, color2);
    DrawRectangle(screenWidth - borderWidth1 - borderWidth2, borderWidth1, borderWidth2, screenHeight - 2 * borderWidth1, color2);

    DrawRectangle(borderWidth1 + borderWidth2, borderWidth1 + borderWidth2, borderWidth3, screenHeight - 2 * borderWidth1 - 2 * borderWidth2, color3);
    DrawRectangle(screenWidth - borderWidth1 - borderWidth2 - borderWidth3, borderWidth1 + borderWidth2, borderWidth3, screenHeight - 2 * borderWidth1 - 2 * borderWidth2, color3);
}

void DrawButton(Button button, int borderWidth1, Color borderColor1, int borderWidth2, Color borderColor2)
{
    // Desenha retangulo
    DrawRectangleRec(button.rect, button.color);

    // Bordas duplas
    DrawRectangleLinesEx(button.rect, borderWidth1, borderColor1);
    DrawRectangleLinesEx((Rectangle){button.rect.x + borderWidth1, button.rect.y + borderWidth1, button.rect.width - 2 * borderWidth1, button.rect.height - 2 * borderWidth1}, borderWidth2, borderColor2);

    float textX = button.rect.x + (button.rect.width - MeasureText(button.text, 18)) / 2;
    // Texto
    DrawText(button.text, textX, button.rect.y + 10, 18, BLACK);
}

void DrawMaze()
{

    for (int i = 0; i < mazeWidth; i++)
    {
        for (int j = 0; j < mazeHeight; j++)
        {
            if (maze[i][j] == 1)
            {
                DrawRectangle((j * cellSize) + 25, (i * cellSize) + 22, cellSize, cellSize, PINK);
            }
            else
            {
                DrawRectangle((j * cellSize) + 25, (i * cellSize) + 22, cellSize, cellSize, BLACK);
            }
        }
    }
}