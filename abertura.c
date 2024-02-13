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
    Texture2D story = LoadTexture("assets/historia.png");

    // Botoes do menu
    int screenHeight = GetScreenHeight();
    int screenWidth = GetScreenWidth();
    int posXbutton = (screenWidth - 200) / 2;
    int posYbuttonS = (screenHeight - 200) * 2 / 3;
    int posYbuttonH = posYbuttonS + 75;
    int posYbuttonC = posYbuttonH + 75;
    int posYbuttonE = posYbuttonC + 75;
    int posYbuttonB = posYbuttonC + 75;
    Color colorButton = SKYBLUE;
    Button startButton = {(Rectangle){posXbutton, posYbuttonS, 200, 50}, colorButton, BLUE, "COMEÇAR"};
    Button howToPLayButton = {(Rectangle){posXbutton, posYbuttonH, 200, 50}, colorButton, BLUE, "COMO JOGAR"};
    Button creditsButton = {(Rectangle){posXbutton, posYbuttonC, 200, 50}, colorButton, BLUE, "CRÉDITOS"};
    Button exitButton = {(Rectangle){posXbutton, posYbuttonE, 200, 50}, colorButton, BLUE, "SAIR"};
    Button backButton = {(Rectangle){posXbutton, posYbuttonB, 200, 50}, colorButton, BLUE, "VOLTAR"};

    // Animacao de Ana Laura Menu
    Texture2D anaR = LoadTexture("assets/analaura.direita.png");
    int textureAx = anaR.width;
    int textureAy = anaR.height;
    float posXa = (screenWidth - textureAx) * 4 / 5;
    float posYa = (screenHeight - textureAy) * 4 / 5;
    Vector2 positionAna = {posXa, posYa};
    Rectangle frameRecAna = {0.0f, 0.0f, (float)anaR.width / 4, (float)anaR.height};
    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 8;

    // Animacao de Quinhas Menu
    Texture2D quinhasR = LoadTexture("assets/quinhas.direita.png");
    int textureQx = quinhasR.width;
    int textureQy = quinhasR.height;
    float posXq = (screenWidth - textureQx) * 15 / 5;
    float posYq = (screenHeight - textureQy) * 4 / 5;
    Vector2 positionQuinhas = {posXq, posYq};
    Rectangle frameRecQuinhas = {0.0f, 0.0f, (float)quinhasR.width / 4, (float)quinhasR.height};

    // Coisas do temporizador
    int segundospassados = 0;
    int tempominutos = 0;
    int temposegundos = 0;
    int confirmador = 0;

    // Status do jogo
    GameState gameState = STATE_MENU;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Atualizacao
        UpdateMusicStream(music);

        // Identificar quantos segundo se passaram antes do comeco do jogo para o temporizador comecar do 0
        if (gameState != STATE_PLAY)
        {
            segundospassados = (int)GetTime();
        }

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

        switch (gameState)
        {
        case STATE_MENU:
            // Menu
            if (CheckCollisionPointRec(GetMousePosition(), startButton.rect))
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    // Inicia jogo
                    gameState = STATE_STORY;
                }
            }
            if (CheckCollisionPointRec(GetMousePosition(), howToPLayButton.rect))
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    // Como Jogar
                    gameState = STATE_HOW_TO_PLAY;
                }
            }
            if (CheckCollisionPointRec(GetMousePosition(), creditsButton.rect))
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    // Creditos
                    gameState = STATE_CREDITS;
                }
            }
            if (CheckCollisionPointRec(GetMousePosition(), exitButton.rect))
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    // Sai do jogo
                    gameState = STATE_EXIT;
                }
            }
            break;
        case STATE_STORY:
            if (IsKeyPressed(KEY_SPACE))
            {
                gameState = STATE_PLAY;
            }
            break;
        case STATE_PLAY:
            // Temporizador e FPS
            if (temposegundos % 60 == 0 && temposegundos != 0 && confirmador == 0)
            {
                tempominutos++;
                confirmador++;
            }
            if (temposegundos % 60 != 0)
            {
                confirmador = 0;
            }
            temposegundos = GetTime() - tempominutos * 60 - segundospassados;
            break;
        case STATE_HOW_TO_PLAY:
            if (CheckCollisionPointRec(GetMousePosition(), backButton.rect))
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    gameState = STATE_MENU;
                }
            }
            break;
        case STATE_CREDITS:
            if (CheckCollisionPointRec(GetMousePosition(), backButton.rect))
            {
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

        // Desenho
        BeginDrawing();
        DrawBase();

        switch (gameState)
        {
        case STATE_MENU:
            // Nome do jogo
            int textureWidth = texture.width;
            int textureHeight = texture.height;
            int posX = (screenWidth - textureWidth) / 2;
            int posY = (screenHeight - textureHeight) / 8;
            DrawTexture(texture, posX, posY, WHITE);

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
            }
            if (CheckCollisionPointRec(GetMousePosition(), howToPLayButton.rect))
            {
                DrawButton(howToPLayButton, 3, BLUE, 5, BLACK);
            }
            if (CheckCollisionPointRec(GetMousePosition(), creditsButton.rect))
            {
                DrawButton(creditsButton, 3, BLUE, 5, BLACK);
            }
            if (CheckCollisionPointRec(GetMousePosition(), exitButton.rect))
            {
                DrawButton(exitButton, 3, BLUE, 5, BLACK);
            }
            break;
        case STATE_STORY:
            DrawStory(story);
            // Talvez colocar os bonequinhos andando, ou colocar quinhas, varias analauras e os posteres
            break;
        case STATE_PLAY:
            DrawMaze();
            DrawText(TextFormat("%d:%d", tempominutos, temposegundos), screenWidth / 5, screenHeight / 15, 30, WHITE);
            DrawFPS(screenWidth / 10, screenHeight / 15);
            // Botao de voltar temporario
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
        case STATE_HOW_TO_PLAY:
            // Como Jogar
            DrawButton(backButton, 3, SKYBLUE, 5, BLACK);
            if (CheckCollisionPointRec(GetMousePosition(), backButton.rect))
            {
                DrawButton(backButton, 3, BLUE, 5, BLACK);
            }
            break;
        case STATE_CREDITS:
            // Adicionando creditos
            int textureWidthcredits = textureCredits.width;
            int textureHeightcredits = textureCredits.height;
            int posXcredits = (screenWidth - textureWidthcredits) / 2;
            int posYcredits = (screenHeight - textureHeightcredits) / 4;
            DrawTexture(textureCredits, posXcredits, posYcredits, WHITE);
            DrawButton(backButton, 3, SKYBLUE, 5, BLACK);
            if (CheckCollisionPointRec(GetMousePosition(), backButton.rect))
            {

                DrawButton(backButton, 3, BLUE, 5, BLACK);
            }
            break;
        case STATE_EXIT:
            // talvez colocar alguma despedida depois
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