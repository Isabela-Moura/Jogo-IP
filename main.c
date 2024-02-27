#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "maze.h"
#include "menu.h"
#include "raylib.h"

//struct para controlar velocidades
 typedef struct {

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
    Texture2D textureP = LoadTexture("assets/posterIP.png");

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
    Texture2D anaMenu = LoadTexture("assets/analaura.menu.png");
    int textureAx = anaMenu.width;
    int textureAy = anaMenu.height;
    float posXa = (screenWidth - textureAx) * 4 / 5;
    float posYa = (screenHeight - textureAy) * 4 / 5;
    Vector2 positionAnaMenu = {posXa, posYa};
    Rectangle frameRecAnaMenu = {0.0f, 0.0f, (float)anaMenu.width / 4, (float)anaMenu.height};
    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 8;
    // Animacao de Quinhas Menu
    Texture2D quinhasMenu = LoadTexture("assets/quinhas.menu.png");
    int textureQx = quinhasMenu.width;
    int textureQy = quinhasMenu.height;
    float posXq = (screenWidth - textureQx) * 15 / 5;
    float posYq = (screenHeight - textureQy) * 4 / 5;
    Vector2 positionQuinhasMenu = {posXq, posYq};
    Rectangle frameRecQuinhasMenu = {0.0f, 0.0f, (float)quinhasMenu.width / 4, (float)quinhasMenu.height};

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
    Velocidade velocidadequinhas = {2,2,2,2};

    // Coisas do temporizador
    int segundospassados = 0;
    int tempominutos = 0;
    int temposegundos = 0;
    int confirmador = 0;

    // Placar
    int pontuacaoPlacar = 0;
    bool pontuacaoRegistrada[NUM_POSTERS] = {false};

    // Posteres
    Poster poster1 = {150, 750, true};
    Poster poster2 = {350, 900, true};
    Poster poster3 = {800, 750, true};
    Poster poster4 = {1150, 850, true};
    Poster poster5 = {1695, 875, true};
    Poster poster6 = {250, 450, true};
    Poster poster7 = {500, 600, true};
    Poster poster8 = {700, 420, true};
    Poster poster9 = {750, 310, true};
    Poster poster10 = {720, 200, true};
    Poster poster11 = {1500, 200, true};
    Poster poster12 = {1350, 565, true};

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

        // Frames das animacões do Menu
        if (gameState == STATE_MENU)
        {
            framesCounter++;
            if (framesCounter >= (60 / framesSpeed))
            {
                framesCounter = 0;
                currentFrame++;
                if (currentFrame > 3)
                {
                    frameRecAnaMenu.x = (float)currentFrame * (float)anaMenu.width / 4;
                    frameRecQuinhasMenu.x = (float)currentFrame * (float)quinhasMenu.width / 4;
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
                pontuacaoRegistrada[0] = true;
                poster1.isVisible = false;
                drawwallvertical(4, 15, 16); // 1 coluna e 2 linhas
            }

            if (CheckCollisionCircles((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius, (Vector2){350, 900}, 0) && !pontuacaoRegistrada[1])
            {
                pontuacaoPlacar++;
                pontuacaoRegistrada[1] = true;
                poster2.isVisible = false;
                drawwallhorizontal(14, 8, 9); // 1 linhas e 2 coluna
            }

            if (CheckCollisionCircles((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius, (Vector2){800, 750}, 0) && !pontuacaoRegistrada[2])
            {
                pontuacaoPlacar++;
                pontuacaoRegistrada[2] = true;
                poster3.isVisible = false;
            }

            if (CheckCollisionCircles((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius, (Vector2){1150, 850}, 0) && !pontuacaoRegistrada[3])
            {
                pontuacaoPlacar++;
                pontuacaoRegistrada[3] = true;
                poster4.isVisible = false;

                drawwallvertical(37, 1, 2); // 1 coluna e 2 linhas
            }

            if (CheckCollisionCircles((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius, (Vector2){1695, 875}, 0) && !pontuacaoRegistrada[4])
            {
                pontuacaoPlacar++;
                pontuacaoRegistrada[4] = true;
                poster5.isVisible = false;

                drawwallhorizontal(7, 43, 44); // 1 linhas e 2 coluna
            }

            if (CheckCollisionCircles((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius, (Vector2){250, 450}, 0) && !pontuacaoRegistrada[5])
            {
                pontuacaoPlacar++;
                pontuacaoRegistrada[5] = true;
                poster6.isVisible = false;

                drawwallvertical(4, 1, 2); // 1 coluna e 2 linhas
            }

            if (CheckCollisionCircles((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius, (Vector2){500, 600}, 0) && !pontuacaoRegistrada[6])
            {
                pontuacaoPlacar++;
                pontuacaoRegistrada[6] = true;
                poster7.isVisible = false;
                drawwallhorizontal(13, 22, 23); // 1 linhas e 2 coluna
            }

            if (CheckCollisionCircles((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius, (Vector2){700, 420}, 0) && !pontuacaoRegistrada[7])
            {
                pontuacaoPlacar++;
                pontuacaoRegistrada[7] = true;
                poster8.isVisible = false;
                drawwallhorizontal(11, 5, 6); // 1 linhas e 2 coluna
            }

            if (CheckCollisionCircles((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius, (Vector2){750, 310}, 0) && !pontuacaoRegistrada[8])
            {
                pontuacaoPlacar++;
                pontuacaoRegistrada[8] = true;
                poster9.isVisible = false;

                drawwallvertical(21, 1, 2); // 1 coluna e 2 linhas
            }

            if (CheckCollisionCircles((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius, (Vector2){720, 200}, 0) && !pontuacaoRegistrada[9])
            {
                pontuacaoPlacar++;
                pontuacaoRegistrada[9] = true;
                poster10.isVisible = false;
                drawwallvertical(20, 11, 12); // 1 coluna e 2 linhas
            }
            if (CheckCollisionCircles((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius, (Vector2){1500, 200}, 0) && !pontuacaoRegistrada[10])
            {
                pontuacaoPlacar++;
                pontuacaoRegistrada[10] = true;
                poster11.isVisible = false;

                drawwallvertical(20, 11, 12); // 1 coluna e 2 linhas
            }

            if (CheckCollisionCircles((Vector2){quinhasmovimento.x, quinhasmovimento.y}, radius, (Vector2){1350, 565}, 0) && !pontuacaoRegistrada[11])
            {
                pontuacaoPlacar++;
                pontuacaoRegistrada[11] = true;
                poster12.isVisible = false;
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
             //Desenhando todos os retangulos e variaveis dos retangulos na mao para realizar a colisão
             DrawRectangle(77, 136, 35, 850, GREEN);
             Rectangle retangulo1 = {77, 136, 35, 850};
             DrawRectangle(1705, 136, 72, 34, GREEN);
             Rectangle retangulo2 = {1708,136,72,34};
             DrawRectangle(1744, 136, 34, 850, GREEN);
             Rectangle retangulo3 = {1744, 136, 34, 850};
             DrawRectangle(215, 952, 1562, 34, GREEN);
             Rectangle retangulo4 = {215, 952, 1562, 34};
             DrawRectangle(111,952,35,34,GREEN);
             Rectangle retangulo5 = {111,952,35,34};
             DrawRectangle(111,136, 1530, 34, GREEN);
             Rectangle retangulo6 = {111,136, 1526, 34};
             DrawRectangle(110,612, 239, 34, GREEN);
             Rectangle retangulo7C = {110,614, 236, 32};
             Rectangle retangulo7E = {110,614,238,30};
             Rectangle retangulo7B = {110,612,236,32};
             DrawRectangle(214,714,34,238,GREEN);
             Rectangle retangulo8D = {214,716,32,236};
             Rectangle retangulo8C = {216,714,30,1};
             Rectangle retangulo8E = {216,716,32,234};
             DrawRectangle(246,850,274,34,GREEN);
             Rectangle retangulo9B = {246,850,268,32};
             Rectangle retangulo9E = {246,852,270,30};
             Rectangle retangulo9C = {246,852,268,32};
             //retangulos para saber a width e height de quinhas na hora da colisao, um pra cada direcao
             Rectangle retanguloquinhasB = {quinhasmovimento.x, quinhasmovimento.y, (float)quinhasD.width/4, quinhasD.height};
             Rectangle retanguloquinhasC = {quinhasmovimento.x, quinhasmovimento.y, (float)quinhasU.width/4, quinhasU.height};
             Rectangle retanguloquinhasD = {quinhasmovimento.x, quinhasmovimento.y, (float)quinhasR.width/4, quinhasR.height};
             Rectangle retanguloquinhasD2 = {quinhasmovimento.x, quinhasmovimento.y, (float)quinhasR.width/4, quinhasR.height};
             Rectangle retanguloquinhasE = {quinhasmovimento.x, quinhasmovimento.y, (float)quinhasL.width/4, quinhasL.height};
             //colisoes
            if(CheckCollisionRecs(retanguloquinhasD, retangulo3) || CheckCollisionRecs(retanguloquinhasD2,retangulo8D)){velocidadequinhas.direita = 0;}
            else{velocidadequinhas.direita = 2;}
           if(CheckCollisionRecs(retanguloquinhasC, retangulo2) || CheckCollisionRecs(retanguloquinhasC, retangulo6) || CheckCollisionRecs(retanguloquinhasC,retangulo7C)
           || CheckCollisionRecs(retanguloquinhasC,retangulo9C)){velocidadequinhas.cima = 0;}
            else{velocidadequinhas.cima = 2;}
            if(CheckCollisionRecs(retanguloquinhasB, retangulo4) || CheckCollisionRecs(retanguloquinhasB,retangulo5) || CheckCollisionRecs(retanguloquinhasB,retangulo8C) 
            || CheckCollisionRecs(retanguloquinhasB,retangulo9B) || CheckCollisionRecs(retanguloquinhasB, retangulo7B)){velocidadequinhas.baixo = 0;}
            else{velocidadequinhas.baixo = 2;}
            if(CheckCollisionRecs(retanguloquinhasE, retangulo1) || CheckCollisionRecs(retanguloquinhasE, retangulo8E) || CheckCollisionRecs(retanguloquinhasE,retangulo9E)
            || CheckCollisionRecs(retanguloquinhasE, retangulo7E)){velocidadequinhas.esquerda = 0;}
            else{velocidadequinhas.esquerda = 2;}
            // variaveis que estao sendo usados na medida
             int ala = quinhasmovimento.x; 
             int ala2 = quinhasmovimento.y;
            DrawText(TextFormat("Posicao X: %d, Posicao Y: %d", ala, ala2), 900, 100, 32, WHITE);
           //Invoca uma regua vermelha atras de quinhas para melhor medimento
          if(IsKeyDown(KEY_X)){
              int platina = 1;
              if(platina == 1)
           DrawRectangle(quinhasmovimento.x,quinhasmovimento.y,5,1900,RED);
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
        }

        // Desenho
        BeginDrawing();
        DrawBase();

        switch (gameState)
        {
        case STATE_MENU:
            // Menu
            ShowMenu(screenWidth, screenHeight, texture, anaMenu, frameRecAnaMenu, positionAnaMenu, quinhasMenu, frameRecQuinhasMenu, positionQuinhasMenu, startButton, howToPLayButton, creditsButton, exitButton);
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
    UnloadTexture(textureP);
    UnloadTexture(story);
    // Fechando
    CloseWindow();
    return 0;
}