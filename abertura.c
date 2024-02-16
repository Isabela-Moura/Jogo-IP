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
    Texture2D texture = LoadTexture("assets/nomeJogo.png");
    Texture2D textureHowToPlay = LoadTexture("assets/comojogar.png");
    Texture2D textureCredits = LoadTexture("assets/creditos.png");
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
    Texture2D anaU = LoadTexture("assets/analaura.cima.png");
    Texture2D anaL = LoadTexture("assets/analaura.esquerda.png");
    Texture2D anaD = LoadTexture("assets/analaura.frente.png");
    int textureAx = anaR.width;
    int textureAy = anaR.height;
    float posXa = (screenWidth - textureAx) * 4 / 5;
    float posYa = (screenHeight - textureAy) * 4 / 5;
    Vector2 positionAna = {posXa, posYa};
    Rectangle frameRecAna = {0.0f, 0.0f, (float)anaR.width / 4, (float)anaR.height};
    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 8;
    float tempodeframe = 0;

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

    // Analaura andando(depois trocar para quinhas quando seu movimento for resolvido)
    Vector2 anamovimento = {0, 0};
    int checagem = 0;

    // Status do jogo
    GameState gameState = STATE_MENU;

    SetTargetFPS(60);

    while (!WindowShouldClose() && gameState != STATE_EXIT)
    {
        // Atualizacao
        UpdateMusicStream(music);

        // Identificar quantos segundo se passaram antes do comeco do jogo para o temporizador comecar do 0
        if (gameState != STATE_PLAY)
        {
            segundospassados = (int)GetTime();
        }
        // Posicao original de Ana(depois trocar para quinhas)
        if (gameState != STATE_PLAY)
        {
            checagem = 0;
            anamovimento.x = 0;
            anamovimento.y = 830;
        }
        // Frames das animacões
        if (gameState == STATE_MENU)
        {
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
        }

        switch (gameState)
        {
        case STATE_MENU:
            // Menu
            if (CheckCollisionPointRec(GetMousePosition(), startButton.rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                // Vai para historia
                gameState = STATE_STORY;
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
        case STATE_STORY:
            if (IsKeyPressed(KEY_SPACE))
            {
                gameState = STATE_PLAY;
            }
            break;
        case STATE_PLAY:
            DrawMaze(); // DrawMaze movido para aqui para que analaura(futuramente quinhas) seja desenhada depois do labirinto para melhor visualizacao. Cellsize alterado de 25 para 34
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

            // checar o valor da checagem
            if (IsKeyReleased(KEY_D))
            {
                checagem = 0;
            }
            if (IsKeyReleased(KEY_W))
            {
                checagem = 1;
            }
            if (IsKeyReleased(KEY_A))
            {
                checagem = 2;
            }
            if (IsKeyReleased(KEY_S))
            {
                checagem = 3;
            }
            // caso o boneco pare de se mexer, a checagem e utilizada para checar qual foi o ultimo frame que o boneco estava para parar com a animacao certa
            if (checagem == 0)
            {
                DrawTextureRec(anaR, frameRecAna, anamovimento, WHITE);
                if (IsKeyReleased(KEY_D))
                {
                    frameRecAna.x = 0;
                } // Para deixar o boneco no frame em que esta parado
            }
            if (checagem == 1)
            {
                DrawTextureRec(anaU, frameRecAna, anamovimento, WHITE);
                if (IsKeyReleased(KEY_W))
                {
                    currentFrame = 2;
                    frameRecAna.x = (float)currentFrame * (float)anaR.width / 4;
                }
            }
            if (checagem == 2)
            {
                DrawTextureRec(anaL, frameRecAna, anamovimento, WHITE);
                if (IsKeyReleased(KEY_A))
                {
                    currentFrame = 3;
                    frameRecAna.x = (float)currentFrame * (float)anaR.width / 4;
                }
            }
            if (checagem == 3)
            {
                DrawTextureRec(anaD, frameRecAna, anamovimento, WHITE);
                if (IsKeyReleased(KEY_S))
                {
                    currentFrame = 3;
                    frameRecAna.x = (float)currentFrame * (float)anaR.width / 4;
                }
            }
            // direita ana
            if (IsKeyDown(KEY_D))
            {
                checagem = 0;
                DrawTextureRec(anaR, frameRecAna, anamovimento, WHITE);
                anamovimento.x = anamovimento.x + 2;
                framesCounter++;
                if (framesCounter >= (60 / framesSpeed))
                {
            tempodeframe += GetFrameTime();
            if(tempodeframe >= 0.2){
            tempodeframe = 0;
            currentFrame++;
            }
                    if (currentFrame > 3)
                    {
                        frameRecAna.x = (float)currentFrame * (float)anaR.width / 4;
                        frameRecQuinhas.x = (float)currentFrame * (float)quinhasR.width / 4;
                    }
                }
            }
            // cima ana
            if (IsKeyDown(KEY_W))
            {
                checagem = 1;
                DrawTextureRec(anaU, frameRecAna, anamovimento, WHITE);
                anamovimento.y = anamovimento.y - 2;
                framesCounter++;
                if (framesCounter >= (60 / framesSpeed))
                {
             tempodeframe += GetFrameTime();
            if(tempodeframe >= 0.2){
            tempodeframe = 0;
            currentFrame++;
            }
                    if (currentFrame > 3)
                    {
                        frameRecAna.x = (float)currentFrame * (float)anaU.width / 4;
                        frameRecQuinhas.x = (float)currentFrame * (float)quinhasR.width / 4;
                    }
                }
            }
            // esquerda ana
            if (IsKeyDown(KEY_A))
            {
                checagem = 2;
                DrawTextureRec(anaL, frameRecAna, anamovimento, WHITE);
                anamovimento.x = anamovimento.x - 2;
                framesCounter++;
                if (framesCounter >= (60 / framesSpeed))
                {
            tempodeframe += GetFrameTime();
            if(tempodeframe >= 0.2){
            tempodeframe = 0;
            currentFrame++;
            }
                    if (currentFrame > 3)
                    {
                        frameRecAna.x = (float)currentFrame * (float)anaL.width / 4;
                        frameRecQuinhas.x = (float)currentFrame * (float)quinhasR.width / 4;
                    }
                }
            }
            // baixo ana
            if (IsKeyDown(KEY_S))
            {
                checagem = 3;
                DrawTextureRec(anaD, frameRecAna, anamovimento, WHITE);
                anamovimento.y = anamovimento.y + 2;
                framesCounter++;
                if (framesCounter >= (60 / framesSpeed))
                {
            tempodeframe += GetFrameTime();
            if(tempodeframe >= 0.2){
            tempodeframe = 0;
            currentFrame++;
            }
                    if (currentFrame > 3)
                    {
                        frameRecAna.x = (float)currentFrame * (float)anaD.width / 4;
                        frameRecQuinhas.x = (float)currentFrame * (float)quinhasR.width / 4;
                    }
                }
            }

            break;
        case STATE_HOW_TO_PLAY:
            if (CheckCollisionPointRec(GetMousePosition(), backButton.rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                gameState = STATE_MENU;
            }
            break;
        case STATE_CREDITS:
            if (CheckCollisionPointRec(GetMousePosition(), backButton.rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                gameState = STATE_MENU;
            }
            break;
        case STATE_EXIT:
            // Sai do jogo
            break;
        }

        // Desenho
        BeginDrawing();
        DrawBase();

        switch (gameState)
        {
        case STATE_MENU:
            // Menu
            ShowMenu(screenWidth, screenHeight, texture, anaR, frameRecAna, positionAna, quinhasR, frameRecQuinhas, positionQuinhas, startButton, howToPLayButton, creditsButton, exitButton);
            break;
        case STATE_STORY:
            ShowStory(story);
            // Talvez colocar os bonequinhos andando, ou colocar quinhas, varias analauras e os posteres
            break;
        case STATE_PLAY:
            // Jogo
            ShowPlay(screenWidth, screenHeight, tempominutos, temposegundos);
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
            ShowHowToPlay(screenWidth, screenHeight, textureHowToPlay, backButton);
            break;
        case STATE_CREDITS:
            // Adicionando creditos
            ShowCredits(screenWidth, screenHeight, textureCredits, backButton);
            break;
        case STATE_EXIT:
            // Sai do jogo
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
    UnloadTexture(anaU);
    UnloadTexture(anaL);
    UnloadTexture(anaD);
    // Descarregamento das texturas
    UnloadTexture(texture);
    UnloadTexture(textureHowToPlay);
    UnloadTexture(textureCredits);
    UnloadTexture(story);
    // Fechando
    CloseWindow();
    return 0;
}