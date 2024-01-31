#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "abertura.h"
#include "raylib.h"

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

    // Fonte
    Font font = LoadFont("resources/fonts/pixantiqua.png");

    // Imagem
    Image image = LoadImage("assets/nomeJogo.png");
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);

    Image imageCredits = LoadImage("assets/creditos.png");
    Texture2D textureCredits = LoadTextureFromImage(imageCredits);
    UnloadImage(imageCredits);

    // Botoes do menu
    int screenWidth = GetScreenWidth();
    int posXbutton = (screenWidth - 200) / 2;
    Color colorButton = SKYBLUE;
    Button startButton = {(Rectangle){posXbutton, 385, 200, 50}, colorButton, BLUE, "COMEÇAR"};
    Button howToPLayButton = {(Rectangle){posXbutton, 460, 200, 50}, colorButton, BLUE, "COMO JOGAR"};
    Button creditsButton = {(Rectangle){posXbutton, 535, 200, 50}, colorButton, BLUE, "CRÉDITOS"};
    Button exitButton = {(Rectangle){posXbutton, 610, 200, 50}, colorButton, BLUE, "SAIR"};
    Button backButton = {(Rectangle){posXbutton, 610, 200, 50}, colorButton, BLUE, "VOLTAR"};

    // Animacao de Ana Laura
    Texture2D anaR = LoadTexture("assets/analaura.direita.png");
    Vector2 positionAna = {175.0f, 380.0f};
    Rectangle frameRecAna = {0.0f, 0.0f, (float)anaR.width / 4, (float)anaR.height};
    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 8;

    // Animacao de Quinhas
    Texture2D quinhasR = LoadTexture("assets/quinhas.direita.png");
    Vector2 positionQuinhas = {925.0f, 380.f};
    Rectangle frameRecQuinhas = {0.0f, 0.0f, (float)quinhasR.width / 4, (float)quinhasR.height};

    // Status do jogo
    GameState gameState = STATE_MENU;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Atualizacao
        UpdateMusicStream(music);

        // Frames das animacões
        framesCounter++;
        if (framesCounter >= (60 / framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;
            if (currentFrame > 3)
            {
                frameRecAna.x = (float)currentFrame * (float)anaR.width / 4;
                frameRecQuinhas.x = (float)currentFrame * (float)quinhasR.width / 4;
            }
        }

        // Desenho
        BeginDrawing();
        ClearBackground(BLACK);
        DrawBorders(8, 5, 5, SKYBLUE, BLACK, SKYBLUE);

        switch (gameState)
        {
        case STATE_MENU:
            // Nome do jogo
            int screenWidth = GetScreenWidth();
            int textureWidth = texture.width;
            int posX = (screenWidth - textureWidth) / 2;
            DrawTexture(texture, posX, 45, WHITE);

            // Ana Laura e Quinhas na entrada
            DrawTextureRec(anaR, frameRecAna, positionAna, WHITE);
            DrawTextureRec(quinhasR, frameRecQuinhas, positionQuinhas, WHITE);

            // Desenha botoes
            DrawButton(startButton, 3, SKYBLUE, 5, BLACK);
            DrawButton(howToPLayButton, 3, SKYBLUE, 5, BLACK);
            DrawButton(creditsButton, 3, SKYBLUE, 5, BLACK);
            DrawButton(exitButton, 3, SKYBLUE, 5, BLACK);

            // Menu
            if (CheckCollisionPointRec(GetMousePosition(), startButton.rect))
            {
                DrawButton(startButton, 3, BLUE, 5, BLACK);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    // Inicia jogo
                    gameState = STATE_PLAY;
                }
            }
            if (CheckCollisionPointRec(GetMousePosition(), howToPLayButton.rect))
            {
                DrawButton(howToPLayButton, 3, BLUE, 5, BLACK);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    // Como Jogar
                    gameState = STATE_HOW_TO_PLAY;
                }
            }
            if (CheckCollisionPointRec(GetMousePosition(), creditsButton.rect))
            {
                DrawButton(creditsButton, 3, BLUE, 5, BLACK);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    // Creditos
                    gameState = STATE_CREDITS;
                }
            }
            if (CheckCollisionPointRec(GetMousePosition(), exitButton.rect))
            {
                DrawButton(exitButton, 3, BLUE, 5, BLACK);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    // Sai do jogo
                    gameState = STATE_EXIT;
                }
            }
            break;
        case STATE_PLAY:
            DrawMaze();
            break;
        case STATE_HOW_TO_PLAY:
            DrawButton(backButton, 3, SKYBLUE, 5, BLACK);
            if (CheckCollisionPointRec(GetMousePosition(), backButton.rect))
            {
                DrawButton(backButton, 3, BLUE, 5, BLACK);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    gameState = STATE_MENU;
                }
            }
            break;
        case STATE_CREDITS:
            // Adicionando creditos
            int textureWidthcredits = textureCredits.width;
            int posXcredits = (screenWidth - textureWidthcredits) / 2;
            DrawTexture(textureCredits, posXcredits, 50, WHITE);
            DrawButton(backButton, 3, SKYBLUE, 5, BLACK);
            if (CheckCollisionPointRec(GetMousePosition(), backButton.rect))
            {

                DrawButton(backButton, 3, BLUE, 5, BLACK);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    gameState = STATE_MENU;
                }
            }
            break;
        case STATE_EXIT:
            // Encerramento
            // Descarregamento da musica
            UnloadMusicStream(music);
            CloseAudioDevice();
            // Descarregamento da fonte
            UnloadFont(font);
            // Descarregamento das animacoes
            UnloadTexture(anaR);
            UnloadTexture(quinhasR);
            // FechandoS
            CloseWindow();
            return 0;
            break;
        }

        EndDrawing();
    }
    // Encerramento
    // Descarregamento da musica
    UnloadMusicStream(music);
    CloseAudioDevice();
    // Descarregamento da fonte
    UnloadFont(font);
    // Descarregamento das animacoes
    UnloadTexture(anaR);
    UnloadTexture(quinhasR);
    // Fechando
    CloseWindow();
    return 0;
}