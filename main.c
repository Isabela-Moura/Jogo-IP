#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "maze.h"
#include "menu.h"
#include "raylib.h"

// struct para controlar velocidades
typedef struct
{

    int direita;
    int esquerda;
    int baixo;
    int cima;

} Velocidade;

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
    Music music = LoadMusicStream("assets/music.mp3");
    music.looping = false;
    PlayMusicStream(music);

    // Fonte
    Font font = LoadFont("resources/fonts/pixantiqua.png");

    // Imagem
    Texture2D background = LoadTexture("assets/fundo-menu.png");
    Texture2D textureHowToPlay = LoadTexture("assets/comojogar.png");
    Texture2D textureCredits = LoadTexture("assets/creditos.png");
    Texture2D story = LoadTexture("assets/historia.png");
    Texture2D textureP = LoadTexture("assets/posterIP.png");
    Texture2D textureWin = LoadTexture("assets/win.png");
    Texture2D textureLose = LoadTexture("assets/gameover.png");

    // Botoes do menu
    int screenHeight = GetScreenHeight();
    int screenWidth = GetScreenWidth();
    int posXbutton = (screenWidth - 400) * 2 / 5;
    int posYbuttonS = (screenHeight - 400) * 1 / 5;
    int posYbuttonH = posYbuttonS + 150;
    int posYbuttonC = posYbuttonH + 150;
    int posYbuttonE = posYbuttonC + 150;
    int posXbuttonB = (screenWidth - 400) / 2;
    int posYbuttonB = posYbuttonC + 150;
    Color colorButton = RED;
    Button startButton = {(Rectangle){posXbutton, posYbuttonS, 400, 100}, colorButton, MAROON, "COMEÇAR"};
    Button howToPLayButton = {(Rectangle){posXbutton, posYbuttonH, 400, 100}, colorButton, MAROON, "COMO JOGAR"};
    Button creditsButton = {(Rectangle){posXbutton, posYbuttonC, 400, 100}, colorButton, MAROON, "CRÉDITOS"};
    Button exitButton = {(Rectangle){posXbutton, posYbuttonE, 400, 100}, colorButton, MAROON, "SAIR"};
    Button backButton = {(Rectangle){posXbuttonB, posYbuttonB, 400, 100}, colorButton, MAROON, "VOLTAR"};
    Button backButtonWin = {(Rectangle){posXbutton, posYbuttonB, 400, 100}, colorButton, MAROON, "GANHAR DE NOVO"};
    Button exitButtonWin = {(Rectangle){posXbutton, posYbuttonE, 400, 100}, colorButton, MAROON, "SAIR DO JOGO"};
    Button backButtonLose = {(Rectangle){posXbutton, posYbuttonB, 400, 100}, colorButton, MAROON, "TENTAR DE NOVO"};
    Button exitButtonLose = {(Rectangle){posXbutton, posYbuttonE, 400, 100}, colorButton, MAROON, "SAIR DO JOGO"};

    // movimentacao ana
    Texture2D anaR = LoadTexture("assets/analaura.direita.png");
    Texture2D anaU = LoadTexture("assets/analaura.cima.png");
    Texture2D anaL = LoadTexture("assets/analaura.esquerda.png");
    Texture2D anaD = LoadTexture("assets/analaura.frente.png");
    Rectangle frameRecAna = {0.0f, 0.0f, (float)anaD.width / 4, (float)anaD.height};
    Vector2 anamovimento = {0, 0};
    int checagemAna = 0;
    int currentFrameAna = 0;
    int framesCounterAna = 0;
    int framesSpeedAna = 8;
    float tempodeframeAna = 0;

    // movimentacao quinhas
    Texture2D quinhasR = LoadTexture("assets/quinhas.direita.png");
    Texture2D quinhasU = LoadTexture("assets/quinhas.cima.png");
    Texture2D quinhasL = LoadTexture("assets/quinhas.esquerda.png");
    Texture2D quinhasD = LoadTexture("assets/quinhas.frente.png");
    Vector2 quinhasmovimento = {300, 1100};
    int checagemQuinhas = 0;
    Rectangle frameRecQuinhas = {0.0f, 0.0f, (float)quinhasD.width / 4, (float)quinhasD.height};
    int currentFrameQuinhas = 0;
    int framesCounterQuinhas = 0;
    int framesSpeedQuinhas = 8;
    float tempodeframeQuinhas = 0;
    Velocidade velocidadequinhas = {3, 3, 3, 3};

    // Coisas do temporizador
    int segundospassados = 0;
    int tempominutos = 0;
    int temposegundos = 0;
    int confirmador = 0;

    // Placar
    int pontuacaoPlacar = 0;
    int pontuacaoRegistrada[NUM_POSTERS] = {0};

    // Posteres
    Poster poster1 = {150, 750, 1};
    Poster poster2 = {350, 900, 1};
    Poster poster3 = {800, 750, 1};
    Poster poster4 = {1150, 850, 1};
    Poster poster5 = {1695, 875, 1};
    Poster poster6 = {250, 450, 1};
    Poster poster7 = {500, 600, 1};
    Poster poster8 = {700, 420, 1};
    Poster poster9 = {750, 310, 1};
    Poster poster10 = {720, 200, 1};
    Poster poster11 = {1500, 200, 1};
    Poster poster12 = {1350, 565, 1};

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
            checagemAna = 0;
            anamovimento.x = 0;
            anamovimento.y = 830;
            checagemQuinhas = 0;
            quinhasmovimento.x = 144;
            quinhasmovimento.y = 872;
        }
        // Frames das animacões
        if (gameState == STATE_PLAY)
        {
            framesCounterAna++;
            if (framesCounterAna >= (60 / framesSpeedAna))
            {
                framesCounterAna = 0;
                currentFrameAna++;
                if (currentFrameAna > 3)
                {
                    frameRecAna.x = (float)currentFrameAna * (float)anaR.width / 4;
                    frameRecQuinhas.x = (float)currentFrameAna * (float)quinhasR.width / 4;
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
                // Vai para como jogar
                gameState = STATE_HOW_TO_PLAY;
            }
            if (CheckCollisionPointRec(GetMousePosition(), creditsButton.rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                // Vai para os creditos
                gameState = STATE_CREDITS;
            }
            if (CheckCollisionPointRec(GetMousePosition(), exitButton.rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                // Sai do jogo
                gameState = STATE_EXIT;
            }
            break;
        case STATE_STORY:
            // Para começar o jogo
            if (IsKeyPressed(KEY_ENTER))
            {
                gameState = STATE_PLAY;
            }
            break;
        case STATE_PLAY:
            DrawMaze();
            // DrawMaze movido para aqui para que analaura(futuramente quinhas) seja desenhada depois do labirinto para melhor visualizacao. Cellsize alterado de 25 para 34
            DrawPoster(textureP, poster1, 0.1f);
            DrawPoster(textureP, poster2, 0.1f);
            DrawPoster(textureP, poster3, 0.1f);
            DrawPoster(textureP, poster4, 0.1f);
            DrawPoster(textureP, poster5, 0.1f);
            DrawPoster(textureP, poster6, 0.1f);
            DrawPoster(textureP, poster7, 0.1f);
            DrawPoster(textureP, poster8, 0.1f);
            DrawPoster(textureP, poster9, 0.1f);
            DrawPoster(textureP, poster10, 0.1f);
            DrawPoster(textureP, poster11, 0.1f);
            DrawPoster(textureP, poster12, 0.1f);

            int radius = 30;

            if (CheckCollisionCircles((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius, (Vector2){150, 750}, 0) && !pontuacaoRegistrada[0])
            {

                pontuacaoPlacar++;
                pontuacaoRegistrada[0] = 1;
                poster1.isVisible = 0;
                drawwallvertical(4, 15, 16); // 1 coluna e 2 linhas
            }

            if (CheckCollisionCircles((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius, (Vector2){350, 900}, 0) && !pontuacaoRegistrada[1])
            {
                pontuacaoPlacar++;
                pontuacaoRegistrada[1] = 1;
                poster2.isVisible = 0;
                drawwallhorizontal(14, 8, 9); // 1 linhas e 2 coluna
            }

            if (CheckCollisionCircles((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius, (Vector2){800, 750}, 0) && !pontuacaoRegistrada[2])
            {
                pontuacaoPlacar++;
                pontuacaoRegistrada[2] = 1;
                poster3.isVisible = 0;
            }

            if (CheckCollisionCircles((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius, (Vector2){1150, 850}, 0) && !pontuacaoRegistrada[3])
            {
                pontuacaoPlacar++;
                pontuacaoRegistrada[3] = 1;
                poster4.isVisible = 0;

                drawwallvertical(37, 1, 2); // 1 coluna e 2 linhas
            }

            if (CheckCollisionCircles((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius, (Vector2){1695, 875}, 0) && !pontuacaoRegistrada[4])
            {
                pontuacaoPlacar++;
                pontuacaoRegistrada[4] = 1;
                poster5.isVisible = 0;

                drawwallhorizontal(7, 43, 44); // 1 linhas e 2 coluna
            }

            if (CheckCollisionCircles((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius, (Vector2){250, 450}, 0) && !pontuacaoRegistrada[5])
            {
                pontuacaoPlacar++;
                pontuacaoRegistrada[5] = 1;
                poster6.isVisible = 0;

                drawwallvertical(4, 1, 2); // 1 coluna e 2 linhas
            }

            if (CheckCollisionCircles((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius, (Vector2){500, 600}, 0) && !pontuacaoRegistrada[6])
            {
                pontuacaoPlacar++;
                pontuacaoRegistrada[6] = 1;
                poster7.isVisible = 0;
                drawwallhorizontal(13, 22, 23); // 1 linhas e 2 coluna
            }

            if (CheckCollisionCircles((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius, (Vector2){700, 420}, 0) && !pontuacaoRegistrada[7])
            {
                pontuacaoPlacar++;
                pontuacaoRegistrada[7] = 1;
                poster8.isVisible = 0;
                drawwallhorizontal(11, 5, 6); // 1 linhas e 2 coluna
            }

            if (CheckCollisionCircles((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius, (Vector2){750, 310}, 0) && !pontuacaoRegistrada[8])
            {
                pontuacaoPlacar++;
                pontuacaoRegistrada[8] = 1;
                poster9.isVisible = 0;

                drawwallvertical(21, 1, 2); // 1 coluna e 2 linhas
            }

            if (CheckCollisionCircles((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius, (Vector2){720, 200}, 0) && !pontuacaoRegistrada[9])
            {
                pontuacaoPlacar++;
                pontuacaoRegistrada[9] = 1;
                poster10.isVisible = 0;
                drawwallvertical(20, 11, 12); // 1 coluna e 2 linhas
            }
            if (CheckCollisionCircles((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius, (Vector2){1500, 200}, 0) && !pontuacaoRegistrada[10])
            {
                pontuacaoPlacar++;
                pontuacaoRegistrada[10] = 1;
                poster11.isVisible = 0;

                drawwallvertical(20, 11, 12); // 1 coluna e 2 linhas
            }

            if (CheckCollisionCircles((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius, (Vector2){1350, 565}, 0) && !pontuacaoRegistrada[11])
            {
                pontuacaoPlacar++;
                pontuacaoRegistrada[11] = 1;
                poster12.isVisible = 0;
                drawwallhorizontal(0, 46, 47); // 1 linhas e 2 coluna
            }

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

            // checar o valor da checagemAna
            if (IsKeyReleased(KEY_D))
            {
                //  checagemAna = 0;
                checagemQuinhas = 0;
            }
            if (IsKeyReleased(KEY_W))
            {
                // checagemAna = 1;
                checagemQuinhas = 1;
            }
            if (IsKeyReleased(KEY_A))
            {
                // checagemAna = 2;
                checagemQuinhas = 2;
            }
            if (IsKeyReleased(KEY_S))
            {
                //  checagemAna = 3;
                checagemQuinhas = 3;
            }
            // caso o boneco pare de se mexer, a checagemAna e utilizada para checar qual foi o ultimo frame que o boneco estava para parar com a animacao certa
            /*    if (checagemAna == 0)
                {
                    DrawTextureRec(anaR, frameRecAna, anamovimento, WHITE);
                    if (IsKeyReleased(KEY_D))
                    {
                        frameRecAna.x = 0;
                    } // Para deixar o boneco no frame em que esta parado

                } */
            if (checagemQuinhas == 0)
            {
                DrawTextureRec(quinhasR, frameRecQuinhas, quinhasmovimento, WHITE);
                if (IsKeyReleased(KEY_D))
                {
                    frameRecQuinhas.x = 0;
                } // Para deixar o boneco no frame em que esta parado
            }
            /* if (checagemAna == 1)
             {
                 DrawTextureRec(anaU, frameRecAna, anamovimento, WHITE);
                 if (IsKeyReleased(KEY_W))
                 {
                     currentFrameAna = 2;
                     frameRecAna.x = (float)currentFrameAna * (float)anaR.width / 4;
                 }
             } */
            if (checagemQuinhas == 1)
            {
                DrawTextureRec(quinhasU, frameRecQuinhas, quinhasmovimento, WHITE);
                if (IsKeyReleased(KEY_D))
                {
                    currentFrameQuinhas = 2;
                    frameRecQuinhas.x = (float)currentFrameAna * (float)quinhasR.width / 4;
                } // Para deixar o boneco no frame em que esta parado
            }
            /*   if (checagemAna == 2)
               {
                   DrawTextureRec(anaL, frameRecAna, anamovimento, WHITE);
                   if (IsKeyReleased(KEY_A))
                   {
                       currentFrameAna = 3;
                       frameRecAna.x = (float)currentFrameAna * (float)anaR.width / 4;
                   }
               } */
            if (checagemQuinhas == 2)
            {
                DrawTextureRec(quinhasL, frameRecQuinhas, quinhasmovimento, WHITE);
                if (IsKeyReleased(KEY_D))
                {
                    currentFrameQuinhas = 3;
                    frameRecQuinhas.x = (float)currentFrameAna * (float)quinhasR.width / 4;
                } // Para deixar o boneco no frame em que esta parado
            }
            /*   if (checagemAna == 3)
               {
                   DrawTextureRec(anaD, frameRecAna, anamovimento, WHITE);
                   if (IsKeyReleased(KEY_S))
                   {
                       currentFrameAna = 3;
                       frameRecAna.x = (float)currentFrameAna * (float)anaR.width / 4;
                   }
               } */
            if (checagemQuinhas == 3)
            {
                DrawTextureRec(quinhasD, frameRecQuinhas, quinhasmovimento, WHITE);
                if (IsKeyReleased(KEY_D))
                {
                    currentFrameQuinhas = 3;
                    frameRecQuinhas.x = (float)currentFrameAna * (float)quinhasR.width / 4;
                } // Para deixar o boneco no frame em que esta parado
            }

            if (IsKeyDown(KEY_D)) // direita ana e quinhas
            {
                /* direita ana
                checagemAna = 0;
                DrawTextureRec(anaR, frameRecAna, anamovimento, WHITE);
                anamovimento.x = anamovimento.x + 2;
                framesCounterAna++;
                if (framesCounterAna >= (60 / framesSpeedAna))
                {
                    tempodeframeAna += GetFrameTime();
                    if (tempodeframeAna >= 0.2)
                    {
                        tempodeframeAna = 0;
                        currentFrameAna++;
                    }
                    if (currentFrameAna > 3)
                    {
                        frameRecAna.x = (float)currentFrameAna * (float)anaR.width / 4;
                        frameRecQuinhas.x = (float)currentFrameAna * (float)quinhasR.width / 4;
                    }
                } */
                // direita quinhas
                checagemQuinhas = 0;
                DrawTextureRec(quinhasR, frameRecQuinhas, quinhasmovimento, WHITE);
                quinhasmovimento.x = quinhasmovimento.x + velocidadequinhas.direita;
                framesCounterQuinhas++;
                if (framesCounterQuinhas >= (60 / framesSpeedQuinhas))
                {
                    tempodeframeQuinhas += GetFrameTime();
                    if (tempodeframeQuinhas >= 0.2)
                    {
                        tempodeframeQuinhas = 0;
                        currentFrameQuinhas++;
                    }
                    if (currentFrameQuinhas > 3)
                    {
                        frameRecAna.x = (float)currentFrameQuinhas * (float)anaR.width / 4;
                        frameRecQuinhas.x = (float)currentFrameQuinhas * (float)quinhasR.width / 4;
                    }
                }
            }
            // cima ana e quinhas
            if (IsKeyDown(KEY_W))
            {
                /* cima ana
                checagemAna = 1;
                DrawTextureRec(anaU, frameRecAna, anamovimento, WHITE);
                anamovimento.y = anamovimento.y - 2;
                framesCounterAna++;
                if (framesCounterAna >= (60 / framesSpeedAna))
                {
                    tempodeframeAna += GetFrameTime();
                    if (tempodeframeAna >= 0.2)
                    {
                        tempodeframeAna = 0;
                        currentFrameAna++;
                    }
                    if (currentFrameAna > 3)
                    {
                        frameRecAna.x = (float)currentFrameAna * (float)anaU.width / 4;
                        frameRecQuinhas.x = (float)currentFrameAna * (float)quinhasR.width / 4;
                    }
                } */
                // cima quinhas
                checagemQuinhas = 1;
                DrawTextureRec(quinhasU, frameRecQuinhas, quinhasmovimento, WHITE);
                quinhasmovimento.y = quinhasmovimento.y - velocidadequinhas.cima;
                framesCounterQuinhas++;
                if (framesCounterQuinhas >= (60 / framesSpeedQuinhas))
                {
                    tempodeframeQuinhas += GetFrameTime();
                    if (tempodeframeQuinhas >= 0.2)
                    {
                        tempodeframeQuinhas = 0;
                        currentFrameQuinhas++;
                    }
                    if (currentFrameQuinhas > 3)
                    {
                        frameRecAna.x = (float)currentFrameQuinhas * (float)anaR.width / 4;
                        frameRecQuinhas.x = (float)currentFrameQuinhas * (float)quinhasR.width / 4;
                    }
                }
            }

            // esquerda ana e quinhas
            if (IsKeyDown(KEY_A))
            {
                /* esquerda ana
                checagemAna = 2;
                DrawTextureRec(anaL, frameRecAna, anamovimento, WHITE);
                anamovimento.x = anamovimento.x - 2;
                framesCounterAna++;
                if (framesCounterAna >= (60 / framesSpeedAna))
                {
                    tempodeframeAna += GetFrameTime();
                    if (tempodeframeAna >= 0.2)
                    {
                        tempodeframeAna = 0;
                        currentFrameAna++;
                    }
                    if (currentFrameAna > 3)
                    {
                        frameRecAna.x = (float)currentFrameAna * (float)anaL.width / 4;
                        frameRecQuinhas.x = (float)currentFrameAna * (float)quinhasR.width / 4;
                    }
                } */
                // esquerda quinhas
                checagemQuinhas = 2;
                DrawTextureRec(quinhasL, frameRecQuinhas, quinhasmovimento, WHITE);
                quinhasmovimento.x = quinhasmovimento.x - velocidadequinhas.esquerda;
                framesCounterQuinhas++;
                if (framesCounterQuinhas >= (60 / framesSpeedQuinhas))
                {
                    tempodeframeQuinhas += GetFrameTime();
                    if (tempodeframeQuinhas >= 0.2)
                    {
                        tempodeframeQuinhas = 0;
                        currentFrameQuinhas++;
                    }
                    if (currentFrameQuinhas > 3)
                    {
                        frameRecAna.x = (float)currentFrameQuinhas * (float)anaR.width / 4;
                        frameRecQuinhas.x = (float)currentFrameQuinhas * (float)quinhasR.width / 4;
                    }
                }
            }
            // baixo ana e quinhas
            if (IsKeyDown(KEY_S))
            {
                /* baixo ana
                checagemAna = 3;
                DrawTextureRec(anaD, frameRecAna, anamovimento, WHITE);
                anamovimento.y = anamovimento.y + 2;
                framesCounterAna++;
                if (framesCounterAna >= (60 / framesSpeedAna))
                {
                    tempodeframeAna += GetFrameTime();
                    if (tempodeframeAna >= 0.2)
                    {
                        tempodeframeAna = 0;
                        currentFrameAna++;
                    }
                    if (currentFrameAna > 3)
                    {
                        frameRecAna.x = (float)currentFrameAna * (float)anaD.width / 4;
                        frameRecQuinhas.x = (float)currentFrameAna * (float)quinhasR.width / 4;
                    }
                } */
                // baixo quinhas
                checagemQuinhas = 3;
                DrawTextureRec(quinhasD, frameRecQuinhas, quinhasmovimento, WHITE);
                quinhasmovimento.y = quinhasmovimento.y + velocidadequinhas.baixo;
                framesCounterQuinhas++;
                if (framesCounterQuinhas >= (60 / framesSpeedQuinhas))
                {
                    tempodeframeQuinhas += GetFrameTime();
                    if (tempodeframeQuinhas >= 0.2)
                    {
                        tempodeframeQuinhas = 0;
                        currentFrameQuinhas++;
                    }
                    if (currentFrameQuinhas > 3)
                    {
                        frameRecAna.x = (float)currentFrameQuinhas * (float)anaR.width / 4;
                        frameRecQuinhas.x = (float)currentFrameQuinhas * (float)quinhasR.width / 4;
                    }
                }
            }
            // Desenhando todos os retangulos e variaveis dos retangulos na mao para realizar a colisão
            DrawRectangle(77, 136, 35, 850, GREEN);
            Rectangle retangulo1 = {77, 136, 35, 850};
            DrawRectangle(1705, 136, 72, 34, GREEN);
            Rectangle retangulo2 = {1708, 136, 72, 34};
            DrawRectangle(1744, 136, 34, 850, GREEN);
            Rectangle retangulo3 = {1744, 136, 34, 850};
            DrawRectangle(215, 952, 1562, 34, GREEN);
            Rectangle retangulo4 = {215, 952, 1562, 34};
            DrawRectangle(111, 952, 35, 34, GREEN);
            Rectangle retangulo5 = {111, 952, 35, 34};
            DrawRectangle(111, 136, 1530, 34, GREEN);
            Rectangle retangulo6 = {111, 136, 1526, 34};
            DrawRectangle(110, 612, 239, 34, GREEN);
            Rectangle retangulo7C = {110, 614, 236, 32};
            Rectangle retangulo7E = {110, 614, 238, 28};
            Rectangle retangulo7B = {110, 612, 236, 1};
            DrawRectangle(214, 714, 34, 238, GREEN);
            Rectangle retangulo8D = {214, 716, 32, 236};
            Rectangle retangulo8C = {216, 714, 30, 1};
            Rectangle retangulo8E = {216, 716, 32, 234};
            DrawRectangle(246, 850, 274, 34, GREEN);
            Rectangle retangulo9B = {246, 850, 266, 1};
            Rectangle retangulo9E = {246, 854, 270, 26};
            Rectangle retangulo9C = {246, 854, 266, 28};
            DrawRectangle(316, 714, 103, 34, GREEN);
            Rectangle retangulo10C = {318, 716, 98, 32};
            Rectangle retangulo10B = {318, 714, 98, 32};
            Rectangle retangulo10D = {316, 716, 2, 30};
            DrawRectangle(418, 414, 34, 366, GREEN);
            Rectangle retangulo11D = {418, 416, 30, 364};
            Rectangle retangulo11C = {420, 418, 28, 362};
            Rectangle retangulo11B = {420, 414, 28, 1};
            Rectangle retangulo11E = {422, 416, 30, 362};
            DrawRectangle(450, 476, 306, 34, GREEN);
            Rectangle retangulo12B = {452, 476, 300, 32};
            Rectangle retangulo12C = {452, 478, 300, 32};
            DrawRectangle(316, 374, 34, 238, GREEN);
            Rectangle retangulo13E = {318, 376, 32, 234};
            Rectangle retangulo13D = {316, 376, 32, 234};
            Rectangle retangulo13B = {318, 374, 30, 1};
            DrawRectangle(180, 374, 136, 34, GREEN);
            Rectangle retangulo14B = {182, 374, 132, 1};
            Rectangle retangulo14C = {182, 376, 132, 32};
            Rectangle retangulo14D = {180, 376, 132, 30};
            DrawRectangle(180, 406, 34, 137, GREEN);
            Rectangle retangulo15D = {180, 408, 32, 131};
            Rectangle retangulo15E = {182, 408, 32, 131};
            Rectangle retangulo15C = {182, 408, 30, 134};
            DrawRectangle(212, 510, 34, 34, GREEN);
            Rectangle retangulo16C = {214, 512, 27, 32};
            Rectangle retangulo16E = {214, 512, 32, 29};
            Rectangle retangulo16B = {214, 510, 30, 1};
            DrawRectangle(213, 238, 238, 34, GREEN);
            Rectangle retangulo17C = {216, 242, 232, 30};
            Rectangle retangulo17E = {216, 242, 235, 26};
            Rectangle retangulo17D = {213, 241, 1, 26};
            Rectangle retangulo17B = {216, 238, 232, 1};
            DrawRectangle(418, 272, 135, 34, GREEN);
            Rectangle retangulo18C = {421, 275, 129, 31};
            Rectangle retangulo18D = {418, 275, 1, 28};
            Rectangle retangulo18B = {421, 272, 129, 1};
            Rectangle retangulo18E = {421, 275, 132, 28};
            DrawRectangle(520, 305, 34, 102, GREEN);
            Rectangle retangulo19D = {520, 308, 1, 96};
            Rectangle retangulo19C = {523, 308, 28, 99};
            Rectangle retangulo19E = {523, 308, 31, 96};
            Rectangle retangulo19B = {523, 305, 28, 1};
            DrawRectangle(555, 374, 236, 34, GREEN);
            Rectangle retangulo20D = {555, 377, 1, 28};
            Rectangle retangulo20E = {558, 377, 233, 28};
            Rectangle retangulo20C = {558, 377, 230, 31};
            Rectangle retangulo20B = {558, 374, 230, 1};
            DrawRectangle(621, 170, 34, 136, GREEN);
            Rectangle retangulo21D = {621, 173, 1, 130};
            Rectangle retangulo21E = {624, 173, 31, 130};
            Rectangle retangulo21C = {624, 173, 28, 133};
            Rectangle retangulo21B = {624, 170, 28, 1};
            DrawRectangle(656, 272, 169, 34, GREEN);
            Rectangle retangulo22D = {656, 275, 1, 28};
            Rectangle retangulo22E = {659, 275, 166, 28};
            Rectangle retangulo22C = {659, 275, 163, 31};
            Rectangle retangulo22B = {659, 272, 163, 1};
            DrawRectangle(792, 236, 34, 36, GREEN);
            Rectangle retangulo23D = {792, 239, 1, 30};
            Rectangle retangulo23E = {795, 239, 31, 30};
            Rectangle retangulo23B = {795, 236, 28, 1};
            DrawRectangle(757, 408, 34, 100, GREEN);
            Rectangle retangulo24D = {757, 411, 1, 94};
            Rectangle retangulo24E = {760, 411, 31, 94};
            Rectangle retangulo24C = {760, 411, 28, 97};
            DrawRectangle(450, 680, 136, 34, GREEN);
            Rectangle retangulo25B = {453, 680, 130, 1};
            Rectangle retangulo25C = {453, 684, 130, 30};
            DrawRectangle(588, 578, 34, 373, GREEN);
            Rectangle retangulo26B = {591, 578, 28, 1};
            Rectangle retangulo26D = {588, 581, 1, 367};
            Rectangle retangulo26E = {591, 581, 31, 367};
            DrawRectangle(621, 578, 204, 34, GREEN);
            Rectangle retangulo27C = {624, 581, 198, 31};
            Rectangle retangulo27E = {624, 581, 201, 28};
            Rectangle retangulo27B = {624, 578, 198, 1};
            DrawRectangle(1200, 167, 34, 105, GREEN);
            Rectangle retangulo28E = {1203, 170, 31, 99};
            Rectangle retangulo28D = {1200, 170, 1, 99};
            Rectangle retangulo28C = {1203, 170, 28, 102};
            DrawRectangle(1029, 238, 170, 34, GREEN);
            Rectangle retangulo29C = {1032, 241, 164, 31};
            Rectangle retangulo29D = {1029, 241, 1, 28};
            Rectangle retangulo29B = {1032, 238, 164, 1};
            DrawRectangle(1029, 272, 34, 66, GREEN);
            Rectangle retangulo30E = {1032, 275, 31, 60};
            Rectangle retangulo30C = {1032, 275, 28, 63};
            DrawRectangle(894, 305, 135, 34, GREEN);
            Rectangle retangulo31D = {894, 308, 1, 28};
            Rectangle retangulo31B = {897, 305, 129, 1};
            Rectangle retangulo31C = {897, 308, 129, 31};
            DrawRectangle(894, 339, 34, 375, GREEN);
            Rectangle retangulo32D = {894, 342, 1, 369};
            Rectangle retangulo32E = {897, 342, 31, 369};
            Rectangle retangulo32C = {897, 342, 28, 372};
            DrawRectangle(690, 680, 204, 34, GREEN);
            Rectangle retangulo33D = {690, 683, 1, 28};
            Rectangle retangulo33B = {693, 680, 198, 1};
            Rectangle retangulo33C = {693, 683, 198, 31};
            DrawRectangle(690, 714, 34, 170, GREEN);
            Rectangle retangulo34D = {690, 717, 1, 164};
            Rectangle retangulo34E = {693, 717, 31, 164};
            Rectangle retangulo34C = {693, 717, 28, 167};
            DrawRectangle(724, 850, 237, 34, GREEN);
            Rectangle retangulo35B = {727, 850, 231, 1};
            Rectangle retangulo35C = {727, 853, 231, 31};
            Rectangle retangulo35E = {727, 853, 234, 28};
            DrawRectangle(927, 781, 34, 71, GREEN);
            Rectangle retangulo36E = {930, 784, 31, 65};
            Rectangle retangulo36D = {927, 784, 1, 65};
            DrawRectangle(927, 781, 409, 34, GREEN);
            Rectangle retangulo37E = {930, 784, 406, 28};
            Rectangle retangulo37C = {930, 784, 400, 31};
            Rectangle retangulo37B = {930, 781, 400, 1};
            DrawRectangle(1301, 815, 34, 69, GREEN);
            Rectangle retangulo38D = {1301, 818, 1, 63};
            Rectangle retangulo38E = {1304, 818, 31, 63};
            Rectangle retangulo38C = {1304, 818, 28, 66};
            DrawRectangle(996, 476, 34, 305, GREEN);
            Rectangle retangulo39D = {996, 479, 1, 299};
            Rectangle retangulo39E = {999, 479, 31, 299};
            DrawRectangle(996, 476, 136, 34, GREEN);
            Rectangle retangulo40C = {999, 479, 130, 31};
            Rectangle retangulo40B = {999, 476, 130, 1};
            DrawRectangle(1131, 341, 34, 168, GREEN);
            Rectangle retangulo41E = {1134, 344, 31, 162};
            Rectangle retangulo41D = {1131, 344, 1, 162};
            Rectangle retangulo41C = {1134, 344, 28, 165};
            Rectangle retangulo41B = {1134, 341, 28, 1};
            DrawRectangle(1165, 340, 205, 34, GREEN);
            Rectangle retangulo42B = {1168, 340, 199, 1};
            Rectangle retangulo42C = {1168, 343, 199, 31};
            Rectangle retangulo42E = {1168, 343, 202, 28};
            DrawRectangle(1336, 239, 34, 102, GREEN);
            Rectangle retangulo43D = {1336, 242, 1, 96};
            Rectangle retangulo43E = {1339, 242, 31, 96};
            Rectangle retangulo43B = {1339, 239, 28, 1};
            Rectangle retangulo43C = {1339, 242, 28, 99};
            DrawRectangle(1404, 680, 34, 272, GREEN);
            Rectangle retangulo44B = {1407, 680, 28, 1};
            Rectangle retangulo44D = {1404, 683, 1, 266};
            Rectangle retangulo44E = {1407, 683, 31, 266};
            DrawRectangle(1131, 680, 273, 34, GREEN);
            Rectangle retangulo45B = {1134, 680, 267, 1};
            Rectangle retangulo45C = {1134, 683, 267, 31};
            DrawRectangle(1098, 578, 34, 136, GREEN);
            Rectangle retangulo46D = {1098, 581, 1, 130};
            Rectangle retangulo46E = {1101, 581, 31, 130};
            Rectangle retangulo46C = {1101, 581, 28, 133};
            Rectangle retangulo46B = {1101, 578, 28, 1};
            DrawRectangle(1131, 578, 135, 34, GREEN);
            Rectangle retangulo47E = {1134, 581, 132, 28};
            Rectangle retangulo47B = {1134, 578, 129, 1};
            Rectangle retangulo47C = {1134, 581, 129, 31};
            DrawRectangle(1233, 476, 34, 102, GREEN);
            Rectangle retangulo48D = {1233, 479, 1, 96};
            Rectangle retangulo48E = {1236, 479, 31, 96};
            Rectangle retangulo48B = {1236, 476, 28, 1};
            DrawRectangle(1267, 476, 272, 34, GREEN);
            Rectangle retangulo49B = {1270, 476, 266, 1};
            Rectangle retangulo49C = {1270, 479, 266, 31};
            DrawRectangle(1505, 476, 34, 408, GREEN);
            Rectangle retangulo50D = {1505, 479, 1, 402};
            Rectangle retangulo50E = {1508, 479, 31, 402};
            Rectangle retangulo50B = {1508, 476, 28, 1};
            Rectangle retangulo50C = {1508, 479, 28, 405};
            DrawRectangle(1539, 850, 34, 34, GREEN);
            Rectangle retangulo51B = {1542, 850, 28, 1};
            Rectangle retangulo51C = {1542, 853, 28, 31};
            Rectangle retangulo51E = {1542, 853, 31, 28};
            DrawRectangle(1641,510,34,443,GREEN);
            Rectangle retangulo52D = {1641,513,1,437};
            Rectangle retangulo52E = {1644,513,31,437};
            Rectangle retangulo52B = {1644,510,28,1};
            DrawRectangle(1438,169,34,238,GREEN);
            Rectangle retangulo53D = {1438,172,1,232};
            Rectangle retangulo53E = {1441,172,31,232};
            Rectangle retangulo53C = {1441,172,28,235};
            DrawRectangle(1472,374,69,34,GREEN);
            Rectangle retangulo54E = {1475,377,66,28};
            Rectangle retangulo54B = {1475,374,63,1};
            Rectangle retangulo54C = {1475,377,63,31};
            DrawRectangle(1608,238,34,171,GREEN);
            Rectangle retangulo55B = {1611,238,28,1};
            Rectangle retangulo55D = {1608,241,1,165};
            Rectangle retangulo55E = {1611,241,31,165};
            Rectangle retangulo55C = {1611,241,28,168};
            DrawRectangle(1642,238,102,34,GREEN);
            Rectangle retangulo56B = {1645,238,96,1};
            Rectangle retangulo56C = {1645,241,96,31};
            //retangulos dos posteres
            Rectangle retangulop1 = {213,644,1,69};
            Rectangle retangulop2 = {350,646,20,1};
            Rectangle retangulop4 = {1369,170,1,69};
            Rectangle retangulop5 = {1541,407,67,1};
            Rectangle retangulop6 = {213,170,1,68};
            Rectangle retangulop7 = {825,578,69,1};
            Rectangle retangulop8 = {266,543,50,1};
            Rectangle retangulop10 = {790,508,1,70};
            Rectangle retangulop12 = {1637,169,68,1};
            // retangulos para saber a width e height de quinhas na hora da colisao, um pra cada direcao
            Rectangle retanguloquinhasB = {quinhasmovimento.x, quinhasmovimento.y, (float)quinhasD.width / 4, quinhasD.height};
            Rectangle retanguloquinhasC = {quinhasmovimento.x, quinhasmovimento.y, (float)quinhasU.width / 4, quinhasU.height};
            Rectangle retanguloquinhasD = {quinhasmovimento.x, quinhasmovimento.y, (float)quinhasR.width / 4, quinhasR.height};
            Rectangle retanguloquinhasD2 = {quinhasmovimento.x, quinhasmovimento.y, (float)quinhasR.width / 4, quinhasR.height};
            Rectangle retanguloquinhasE = {quinhasmovimento.x, quinhasmovimento.y, (float)quinhasL.width / 4, quinhasL.height};
            // colisoes
            if (CheckCollisionRecs(retanguloquinhasD, retangulo3) || (poster6.isVisible == 1 && CheckCollisionRecs(retanguloquinhasD,retangulop6)) ||(poster1.isVisible == 1 && CheckCollisionRecs(retanguloquinhasD,retangulop1))|| CheckCollisionRecs(retanguloquinhasD2, retangulo8D) || CheckCollisionRecs(retanguloquinhasD, retangulo10D) || CheckCollisionRecs(retanguloquinhasD, retangulo11D) || CheckCollisionRecs(retanguloquinhasD, retangulo13D) || CheckCollisionRecs(retanguloquinhasD, retangulo14D) || CheckCollisionRecs(retanguloquinhasD, retangulo15D) || CheckCollisionRecs(retanguloquinhasD, retangulo17D) || CheckCollisionRecs(retanguloquinhasD, retangulo18D) || CheckCollisionRecs(retanguloquinhasD, retangulo19D) || CheckCollisionRecs(retanguloquinhasD, retangulo20D) || CheckCollisionRecs(retanguloquinhasD, retangulo21D) || CheckCollisionRecs(retanguloquinhasD, retangulo22D) || CheckCollisionRecs(retanguloquinhasD, retangulo23D) || CheckCollisionRecs(retanguloquinhasD, retangulo24D) || CheckCollisionRecs(retanguloquinhasD, retangulo26D) || CheckCollisionRecs(retanguloquinhasD, retangulo28D) || CheckCollisionRecs(retanguloquinhasD, retangulo29D) || CheckCollisionRecs(retanguloquinhasD, retangulo31D) || CheckCollisionRecs(retanguloquinhasD, retangulo32D) || CheckCollisionRecs(retanguloquinhasD, retangulo33D) || CheckCollisionRecs(retanguloquinhasD, retangulo34D) || CheckCollisionRecs(retanguloquinhasD, retangulo36D) || CheckCollisionRecs(retanguloquinhasD, retangulo38D) || CheckCollisionRecs(retanguloquinhasD, retangulo39D) || CheckCollisionRecs(retanguloquinhasD, retangulo41D) || CheckCollisionRecs(retanguloquinhasD, retangulo43D) || CheckCollisionRecs(retanguloquinhasD, retangulo44D) || CheckCollisionRecs(retanguloquinhasD, retangulo46D) || CheckCollisionRecs(retanguloquinhasD, retangulo48D) || CheckCollisionRecs(retanguloquinhasD, retangulo50D) || CheckCollisionRecs(retanguloquinhasD, retangulo52D) || CheckCollisionRecs(retanguloquinhasD, retangulo53D) || CheckCollisionRecs(retanguloquinhasD, retangulo55D))
            {
                velocidadequinhas.direita = 0;
            }
            else
            {
                velocidadequinhas.direita = 3;
            }
            if (CheckCollisionRecs(retanguloquinhasC, retangulo2) || (poster12.isVisible == 1 && CheckCollisionRecs(retanguloquinhasC,retangulop12)) || (poster8.isVisible == 1 && CheckCollisionRecs(retanguloquinhasC,retangulop8)) || (poster5.isVisible == 1 && CheckCollisionRecs(retanguloquinhasC,retangulop5)) ||(poster2.isVisible == 1 && CheckCollisionRecs(retanguloquinhasC,retangulop2)) || CheckCollisionRecs(retanguloquinhasC, retangulo6) || CheckCollisionRecs(retanguloquinhasC, retangulo7C) || CheckCollisionRecs(retanguloquinhasC, retangulo9C) || CheckCollisionRecs(retanguloquinhasC, retangulo10C) || CheckCollisionRecs(retanguloquinhasC, retangulo11C) || CheckCollisionRecs(retanguloquinhasC, retangulo12C) || CheckCollisionRecs(retanguloquinhasC, retangulo14C) || CheckCollisionRecs(retanguloquinhasC, retangulo15C) || CheckCollisionRecs(retanguloquinhasC, retangulo16C) || CheckCollisionRecs(retanguloquinhasC, retangulo17C) || CheckCollisionRecs(retanguloquinhasC, retangulo18C) || CheckCollisionRecs(retanguloquinhasC, retangulo19C) || CheckCollisionRecs(retanguloquinhasC, retangulo20C) || CheckCollisionRecs(retanguloquinhasC, retangulo21C) || CheckCollisionRecs(retanguloquinhasC, retangulo22C) || CheckCollisionRecs(retanguloquinhasC, retangulo24C) || CheckCollisionRecs(retanguloquinhasC, retangulo25C) || CheckCollisionRecs(retanguloquinhasC, retangulo27C) || CheckCollisionRecs(retanguloquinhasC, retangulo28C) || CheckCollisionRecs(retanguloquinhasC, retangulo29C) || CheckCollisionRecs(retanguloquinhasC, retangulo30C) || CheckCollisionRecs(retanguloquinhasC, retangulo31C) || CheckCollisionRecs(retanguloquinhasC, retangulo32C) || CheckCollisionRecs(retanguloquinhasC, retangulo33C) || CheckCollisionRecs(retanguloquinhasC, retangulo34C) || CheckCollisionRecs(retanguloquinhasC, retangulo35C) || CheckCollisionRecs(retanguloquinhasC, retangulo37C) || CheckCollisionRecs(retanguloquinhasC, retangulo38C) || CheckCollisionRecs(retanguloquinhasC, retangulo40C) || CheckCollisionRecs(retanguloquinhasC, retangulo41C) || CheckCollisionRecs(retanguloquinhasC, retangulo42C) || CheckCollisionRecs(retanguloquinhasC, retangulo43C) || CheckCollisionRecs(retanguloquinhasC, retangulo45C) || CheckCollisionRecs(retanguloquinhasC, retangulo46C) || CheckCollisionRecs(retanguloquinhasC, retangulo47C) || CheckCollisionRecs(retanguloquinhasC, retangulo49C) || CheckCollisionRecs(retanguloquinhasC, retangulo50C) || CheckCollisionRecs(retanguloquinhasC, retangulo51C) || CheckCollisionRecs(retanguloquinhasC, retangulo53C) || CheckCollisionRecs(retanguloquinhasC, retangulo54C) || CheckCollisionRecs(retanguloquinhasC, retangulo55C) || CheckCollisionRecs(retanguloquinhasC, retangulo56C)) 
            {
                velocidadequinhas.cima = 0;
            }
            else
            {
                velocidadequinhas.cima = 3;
            }
            if (CheckCollisionRecs(retanguloquinhasB, retangulo4) || (poster7.isVisible == 1 && CheckCollisionRecs(retanguloquinhasB,retangulop7)) ||CheckCollisionRecs(retanguloquinhasB, retangulo5) || CheckCollisionRecs(retanguloquinhasB, retangulo8C) || CheckCollisionRecs(retanguloquinhasB, retangulo9B) || CheckCollisionRecs(retanguloquinhasB, retangulo7B) || CheckCollisionRecs(retanguloquinhasB, retangulo10B) || CheckCollisionRecs(retanguloquinhasB, retangulo11B) || CheckCollisionRecs(retanguloquinhasB, retangulo12B) || CheckCollisionRecs(retanguloquinhasB, retangulo13B) || CheckCollisionRecs(retanguloquinhasB, retangulo14B) || CheckCollisionRecs(retanguloquinhasB, retangulo16B) || CheckCollisionRecs(retanguloquinhasB, retangulo17B) || CheckCollisionRecs(retanguloquinhasB, retangulo18B) || CheckCollisionRecs(retanguloquinhasB, retangulo19B) || CheckCollisionRecs(retanguloquinhasB, retangulo20B) || CheckCollisionRecs(retanguloquinhasB, retangulo21B) || CheckCollisionRecs(retanguloquinhasB, retangulo22B) || CheckCollisionRecs(retanguloquinhasB, retangulo23B) || CheckCollisionRecs(retanguloquinhasB, retangulo25B) || CheckCollisionRecs(retanguloquinhasB, retangulo26B) || CheckCollisionRecs(retanguloquinhasB, retangulo27B) || CheckCollisionRecs(retanguloquinhasB, retangulo29B) || CheckCollisionRecs(retanguloquinhasB, retangulo31B) || CheckCollisionRecs(retanguloquinhasB, retangulo33B) || CheckCollisionRecs(retanguloquinhasB, retangulo35B) || CheckCollisionRecs(retanguloquinhasB, retangulo37B) || CheckCollisionRecs(retanguloquinhasB, retangulo40B) || CheckCollisionRecs(retanguloquinhasB, retangulo41B) || CheckCollisionRecs(retanguloquinhasB, retangulo42B) || CheckCollisionRecs(retanguloquinhasB, retangulo43B) || CheckCollisionRecs(retanguloquinhasB, retangulo44B) || CheckCollisionRecs(retanguloquinhasB, retangulo45B) || CheckCollisionRecs(retanguloquinhasB, retangulo46B) || CheckCollisionRecs(retanguloquinhasB, retangulo47B) || CheckCollisionRecs(retanguloquinhasB, retangulo48B) || CheckCollisionRecs(retanguloquinhasB, retangulo49B) || CheckCollisionRecs(retanguloquinhasB, retangulo50B) || CheckCollisionRecs(retanguloquinhasB, retangulo51B) || CheckCollisionRecs(retanguloquinhasB, retangulo52B) || CheckCollisionRecs(retanguloquinhasB, retangulo54B) || CheckCollisionRecs(retanguloquinhasB, retangulo55B) || CheckCollisionRecs(retanguloquinhasB, retangulo56B))
            {
                velocidadequinhas.baixo = 0;
            }
            else
            {
                velocidadequinhas.baixo = 3;
            }
            if (CheckCollisionRecs(retanguloquinhasE, retangulo1) || (poster10.isVisible == 1 && CheckCollisionRecs(retanguloquinhasE,retangulop10)) || (poster4.isVisible == 1 && CheckCollisionRecs(retanguloquinhasE,retangulop4)) ||CheckCollisionRecs(retanguloquinhasE, retangulo8E) || CheckCollisionRecs(retanguloquinhasE, retangulo9E) || CheckCollisionRecs(retanguloquinhasE, retangulo7E) || CheckCollisionRecs(retanguloquinhasE, retangulo11E) || CheckCollisionRecs(retanguloquinhasE, retangulo13E) || CheckCollisionRecs(retanguloquinhasE, retangulo15E) || CheckCollisionRecs(retanguloquinhasE, retangulo16E) || CheckCollisionRecs(retanguloquinhasE, retangulo17E) || CheckCollisionRecs(retanguloquinhasE, retangulo18E) || CheckCollisionRecs(retanguloquinhasE, retangulo19E) || CheckCollisionRecs(retanguloquinhasE, retangulo20E) || CheckCollisionRecs(retanguloquinhasE, retangulo21E) || CheckCollisionRecs(retanguloquinhasE, retangulo22E) || CheckCollisionRecs(retanguloquinhasE, retangulo23E) || CheckCollisionRecs(retanguloquinhasE, retangulo24E) || CheckCollisionRecs(retanguloquinhasE, retangulo26E) || CheckCollisionRecs(retanguloquinhasE, retangulo27E) || CheckCollisionRecs(retanguloquinhasE, retangulo28E) || CheckCollisionRecs(retanguloquinhasE, retangulo30E) || CheckCollisionRecs(retanguloquinhasE, retangulo32E) || CheckCollisionRecs(retanguloquinhasE, retangulo34E) || CheckCollisionRecs(retanguloquinhasE, retangulo35E) || CheckCollisionRecs(retanguloquinhasE, retangulo36E) || CheckCollisionRecs(retanguloquinhasE, retangulo37E) || CheckCollisionRecs(retanguloquinhasE, retangulo38E) || CheckCollisionRecs(retanguloquinhasE, retangulo39E) || CheckCollisionRecs(retanguloquinhasE, retangulo41E) || CheckCollisionRecs(retanguloquinhasE, retangulo42E) || CheckCollisionRecs(retanguloquinhasE, retangulo43E) || CheckCollisionRecs(retanguloquinhasE, retangulo44E) || CheckCollisionRecs(retanguloquinhasE, retangulo46E) || CheckCollisionRecs(retanguloquinhasE, retangulo47E) || CheckCollisionRecs(retanguloquinhasE, retangulo48E) || CheckCollisionRecs(retanguloquinhasE, retangulo50E) || CheckCollisionRecs(retanguloquinhasE, retangulo51E) || CheckCollisionRecs(retanguloquinhasE, retangulo52E) || CheckCollisionRecs(retanguloquinhasE, retangulo53E) || CheckCollisionRecs(retanguloquinhasE, retangulo54E) || CheckCollisionRecs(retanguloquinhasE, retangulo55E))
            {
                velocidadequinhas.esquerda = 0;
            }
            else
            {
                velocidadequinhas.esquerda = 3;
            }
            // variaveis que estao sendo usados na medida
            int ala = quinhasmovimento.x;
            int ala2 = quinhasmovimento.y;
            DrawText(TextFormat("Posicao X: %d, Posicao Y: %d", ala, ala2), 900, 100, 32, WHITE);
            // Invoca uma regua vermelha atras de quinhas para melhor medimento
            if (IsKeyDown(KEY_X))
            {
                int platina = 1;
                if (platina == 1)
                    DrawRectangle(quinhasmovimento.x, quinhasmovimento.y, 5, 1900, RED);
            }

            break;
        case STATE_HOW_TO_PLAY:
            // Para voltar para o menu
            if (CheckCollisionPointRec(GetMousePosition(), backButton.rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                gameState = STATE_MENU;
            }
            break;
        case STATE_CREDITS:
            // Para voltar para o menu
            if (CheckCollisionPointRec(GetMousePosition(), backButton.rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                gameState = STATE_MENU;
            }
            break;
        case STATE_EXIT:
            // Sai do jogo
            break;
        case STATE_WIN:
            // Vitoria
            // Para voltar para o menu
            if (CheckCollisionPointRec(GetMousePosition(), backButtonWin.rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                gameState = STATE_MENU;
            }
            // Para sair do jogo
            if (CheckCollisionPointRec(GetMousePosition(), exitButtonWin.rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                // Sai do jogo
                gameState = STATE_EXIT;
            }
            break;
        case STATE_LOSE:
            // Derrota
            // Para voltar para o menu
            if (CheckCollisionPointRec(GetMousePosition(), backButtonLose.rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                gameState = STATE_MENU;
            }
            // Para sair do jogo
            if (CheckCollisionPointRec(GetMousePosition(), exitButtonLose.rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                // Sai do jogo
                gameState = STATE_EXIT;
            }
            break;
        }

        // Desenho
        BeginDrawing();
        DrawBase();
        switch (gameState)
        {
        case STATE_MENU:
            // Menu
            ShowMenu(background, startButton, howToPLayButton, creditsButton, exitButton);
            break;
        case STATE_STORY:
            // Historia inicial
            ShowStory(story);
            break;
        case STATE_PLAY:
            // Jogo
            ShowPlay(screenWidth, screenHeight, tempominutos, temposegundos, pontuacaoPlacar);
            // Botao de voltar temporario
            DrawButton(backButton, 3, SKYBLUE, 5, BLACK);
            if (CheckCollisionPointRec(GetMousePosition(), backButton.rect))
            {
                DrawButton(backButton, 3, BLUE, 5, BLACK);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    pontuacaoPlacar = 0; // Reiniciar o placar
                    // Resetar a pontuação de cada poster e a visibilidade de cada um
                    pontuacaoRegistrada[0] = 0;
                    poster1.isVisible = 1;
                    pontuacaoRegistrada[1] = 0;
                    poster2.isVisible = 1;
                    pontuacaoRegistrada[2] = 0;
                    poster3.isVisible = 1;
                    pontuacaoRegistrada[3] = 0;
                    poster4.isVisible = 1;
                    pontuacaoRegistrada[4] = 0;
                    poster5.isVisible = 1;
                    pontuacaoRegistrada[5] = 0;
                    poster6.isVisible = 1;
                    pontuacaoRegistrada[6] = 0;
                    poster7.isVisible = 1;
                    pontuacaoRegistrada[7] = 0;
                    poster8.isVisible = 1;
                    pontuacaoRegistrada[8] = 0;
                    poster9.isVisible = 1;
                    pontuacaoRegistrada[9] = 0;
                    poster10.isVisible = 1;
                    pontuacaoRegistrada[10] = 0;
                    poster11.isVisible = 1;
                    pontuacaoRegistrada[11] = 0;
                    poster12.isVisible = 1;

                    gameState = STATE_MENU;
                }
            }
            break;
        case STATE_HOW_TO_PLAY:
            // Como Jogar
            ShowHowToPlay(screenWidth, screenHeight, textureHowToPlay, backButton);
            break;
        case STATE_CREDITS:
            // Creditos
            ShowCredits(screenWidth, screenHeight, textureCredits, backButton);
            break;
        case STATE_EXIT:
            // Sai do jogo
            break;
        case STATE_WIN:
            // Vitoria
            /*ShowWin(screenWidth, screenHeight, texture, exitButtonWin);*/
            break;
        case STATE_LOSE:
            // Derrota
            /*ShowLose(screenWidth, screenHeight, texture, backButtonLose, exitButtonLose);*/
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
    UnloadTexture(textureHowToPlay);
    UnloadTexture(textureCredits);
    UnloadTexture(textureP);
    UnloadTexture(story);
    UnloadTexture(background);

    // Fechando
    CloseWindow();
    return 0;
}