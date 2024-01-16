#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "abertura.h"

int main()
{
    // Inicializacao
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(0, 0, "Abertura do jogo");
    if (!IsWindowFullscreen())
    {
        ToggleFullscreen();
    }

    // Musica
    InitAudioDevice();
    Music music = LoadMusicStream("assets/mini1111.wav");
    music.looping = false;
    PlayMusicStream(music);
    bool pause = false; // Fazer um botao de mudo dps

    // Fonte
    Font font = LoadFont("resources/fonts/pixantiqua.png");

    // Imagem
    Image image = LoadImage("assets/nomeJogo.png");
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);

    // Botoes do menu
    int screenWidth = GetScreenWidth();
    int posXbutton = (screenWidth - 200) / 2;
    Button startButton = {(Rectangle){posXbutton, 350, 200, 50}, SKYBLUE, "COMEÇAR"};
    Button howToPLayButton = {(Rectangle){posXbutton, 425, 200, 50}, SKYBLUE, "COMO JOGAR"};
    Button creditsButton = {(Rectangle){posXbutton, 500, 200, 50}, SKYBLUE, "CRÉDITOS"};
    Button exitButton = {(Rectangle){posXbutton, 575, 200, 50}, SKYBLUE, "SAIR"};
    Button backButton = {(Rectangle){posXbutton, 650, 200, 50}, SKYBLUE, "VOLTAR"};

    // Status do jogo
    GameState gameState = STATE_MENU;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);
        BeginDrawing();
        ClearBackground(BLACK);
        DrawBorders(8, 5, 5, SKYBLUE, BLACK, SKYBLUE);

        switch (gameState)
        {
        case STATE_MENU:
            int screenWidth = GetScreenWidth();
            int textureWidth = texture.width;
            int posX = (screenWidth - textureWidth) / 2;
            // Nome do jogo
            DrawTexture(texture, posX, 150, WHITE);

            // Desenha botoes
            DrawButton(startButton, 3, SKYBLUE, 5, BLACK);
            DrawButton(howToPLayButton, 3, SKYBLUE, 5, BLACK);
            DrawButton(creditsButton, 3, SKYBLUE, 5, BLACK);
            DrawButton(exitButton, 3, SKYBLUE, 5, BLACK);

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
            DrawButton(backButton, 3, SKYBLUE, 5, BLACK);
            if (CheckCollisionPointRec(GetMousePosition(), backButton.rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                gameState = STATE_MENU;
            }
            break;
        case STATE_CREDITS:
            DrawButton(backButton, 3, SKYBLUE, 5, BLACK);
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

    float textX = button.rect.x + (button.rect.width - MeasureText(button.text, 26)) / 2;
    float textY = button.rect.y + (button.rect.height - 26) / 2;
    // Texto
    DrawText(button.text, textX, textY, 26, BLACK);
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