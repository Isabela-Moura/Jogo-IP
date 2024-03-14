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
    music.looping = true;
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
    int posXbutton = (screenWidth - 300) * 2 / 5;
    int posYbuttonS = (screenHeight - 300) * 1 / 5;
    int posYbuttonH = posYbuttonS + 125;
    int posYbuttonC = posYbuttonH + 125;
    int posYbuttonE = posYbuttonC + 125;
    int posXbuttonB = (screenWidth - 300) / 2;
    int posYbuttonB = (screenHeight - 50) * 9 / 10;
    int posYbuttonWB = (screenHeight - 50) * 4 / 6;
    int posYbuttonWE = posYbuttonWB;
    int posXbuttonWB = (screenWidth - 460) * 1 / 10;
    int posXbuttonWE = (screenWidth - 460) * 9 / 10;
    Color colorButton = RED;
    Button startButton = {(Rectangle){posXbutton, posYbuttonS, 300, 75}, colorButton, MAROON, "COMEÇAR"};
    Button howToPLayButton = {(Rectangle){posXbutton, posYbuttonH, 300, 75}, colorButton, MAROON, "COMO JOGAR"};
    Button creditsButton = {(Rectangle){posXbutton, posYbuttonC, 300, 75}, colorButton, MAROON, "CRÉDITOS"};
    Button exitButton = {(Rectangle){posXbutton, posYbuttonE, 300, 75}, colorButton, MAROON, "SAIR"};
    Button backButton = {(Rectangle){posXbuttonB, posYbuttonB, 300, 75}, colorButton, MAROON, "VOLTAR"};
    Button backButtonWin = {(Rectangle){posXbuttonWB, posYbuttonWB, 460, 75}, colorButton, MAROON, "GANHAR DE NOVO"};
    Button exitButtonWin = {(Rectangle){posXbuttonWE, posYbuttonWE, 460, 75}, colorButton, MAROON, "SAIR DO JOGO"};
    Button backButtonLose = {(Rectangle){posXbuttonWB, posYbuttonWB, 460, 75}, colorButton, MAROON, "TENTAR DE NOVO"};
    Button exitButtonLose = {(Rectangle){posXbuttonWE, posYbuttonWE, 460, 75}, colorButton, MAROON, "SAIR DO JOGO"};

    // movimentacao quinhas
    Texture2D quinhasR = LoadTexture("assets/quinhas.direita.png");
    Texture2D quinhasU = LoadTexture("assets/quinhas.cima.png");
    Texture2D quinhasL = LoadTexture("assets/quinhas.esquerda.png");
    Texture2D quinhasD = LoadTexture("assets/quinhas.frente.png");

    // variavel para que quinhas pare de uma forma correta
    int checagemQuinhas = -1; // Valor inicial para indicar que nenhum botão foi pressionado
    Vector2 quinhasmovimento = {0.0f, 0.0f};

    // animacoes de quinhas parado e variaveis relacionado a sua movimentacao
    Texture2D quinhasParadoD = LoadTexture("assets/quinhas.parado.png");
    Texture2D quinhasParadoC = LoadTexture("assets/quinhas.cima.parado.png");
    Texture2D quinhasParadoB = LoadTexture("assets/quinhas.frente.parado.png");
    Texture2D quinhasParadoE = LoadTexture("assets/quinhas.esquerda.parado.png");
    Rectangle frameRecQuinhas = {0.0f, 0.0f, (float)quinhasD.width / 4, (float)quinhasD.height};
    int currentFrameQuinhas = 0;
    int framesCounterQuinhas = 0;
    int framesSpeedQuinhas = 8;
    float tempodeframeQuinhas = 0;
    Velocidade velocidadequinhas = {3, 3, 3, 3};

    // movimentacao nalauritas
    Texture2D nalaurita1D = LoadTexture("assets/analaura.direita.png");
    Texture2D nalaurita1E = LoadTexture("assets/analaura.esquerda.png");
    Texture2D nalaurita2C = LoadTexture("assets/analaura.cima.png");
    Texture2D nalaurita2B = LoadTexture("assets/analaura.frente.png");
    Texture2D nalaurita3B = LoadTexture("assets/analaura.frente.png");
    Texture2D nalaurita3C = LoadTexture("assets/analaura.cima.png");
    Texture2D nalaurita4D = LoadTexture("assets/analaura.direita.png");
    Texture2D nalaurita4E = LoadTexture("assets/analaura.esquerda.png");
    Texture2D nalaurita5E = LoadTexture("assets/analaura.esquerda.png");
    Texture2D nalaurita5D = LoadTexture("assets/analaura.direita.png");
    Texture2D nalaurita6E = LoadTexture("assets/analaura.esquerda.png");
    Texture2D nalaurita6D = LoadTexture("assets/analaura.direita.png");
    Texture2D nalaurita7E = LoadTexture("assets/analaura.esquerda.png");
    Texture2D nalaurita7D = LoadTexture("assets/analaura.direita.png");
    int currentFrameAna = 0, currentFramenalaurita2 = 0, currentFramenalaurita3 = 0, currentFramenalaurita4 = 0, currentFramenalaurita5 = 0, currentFramenalaurita6 = 0, currentFramenalaurita7 = 0;
    int framesCounterAna = 0, framescounternalaurita2 = 0, framescounternalaurita3 = 0, framescounternalaurita4 = 0, framescounternalaurita5 = 0, framescounternalaurita6 = 0, framescounternalaurita7 = 0;
    int framesSpeedAna = 8;
    float tempodeframenalaurita1 = 0, tempodeframenalaurita2 = 0, tempodeframenalaurita3 = 0, tempodeframenalaurita4 = 0, tempodeframenalaurita5 = 0, tempodeframenalaurita6 = 0, tempodeframenalaurita7 = 0;
    int nalaurita1modo = 0;
    Velocidade nalaurita1velocidade = {1, 1, 1, 1};
    Vector2 nalaurita1movimento = {0, 0};
    Rectangle frameRecnalaurita1 = {0.0f, 0.0f, (float)nalaurita1D.width / 4, (float)nalaurita1D.height};
    int nalaurita2modo = 0;
    Velocidade nalaurita2velocidade = {2, 2, 2, 2};
    Vector2 nalaurita2movimento = {0, 0};
    Rectangle frameRecnalaurita2 = {0.0f, 0.0f, (float)nalaurita2C.width / 4, (float)nalaurita2C.height};
    int nalaurita3modo = 0;
    Velocidade nalaurita3velocidade = {2, 2, 2, 2};
    Vector2 nalaurita3movimento = {0, 0};
    Rectangle frameRecnalaurita3 = {0.0f, 0.0f, (float)nalaurita3B.width / 4, (float)nalaurita3B.height};
    int nalaurita4modo = 0;
    Velocidade nalaurita4velocidade = {2, 2, 2, 2};
    Vector2 nalaurita4movimento = {0, 0};
    Rectangle frameRecnalaurita4 = {0.0f, 0.0f, (float)nalaurita4D.width / 4, (float)nalaurita4D.height};
    int nalaurita5modo = 0;
    Velocidade nalaurita5velocidade = {2, 2, 2, 2};
    Vector2 nalaurita5movimento = {0, 0};
    Rectangle frameRecnalaurita5 = {0.0f, 0.0f, (float)nalaurita5D.width / 4, (float)nalaurita5D.height};
    int nalaurita6modo = 0;
    Velocidade nalaurita6velocidade = {2, 2, 2, 2};
    Vector2 nalaurita6movimento = {0, 0};
    Rectangle frameRecnalaurita6 = {0.0f, 0.0f, (float)nalaurita6D.width / 4, (float)nalaurita6D.height};
    int nalaurita7modo = 0;
    Velocidade nalaurita7velocidade = {2, 2, 2, 2};
    Vector2 nalaurita7movimento = {0, 0};
    Rectangle frameRecnalaurita7 = {0.0f, 0.0f, (float)nalaurita7D.width / 4, (float)nalaurita7D.height};

    // Temporizador
    int segundospassados = 0;
    int tempominutos = 0;
    int temposegundos = 0;
    int confirmador = 0;
    int parado = 0;
    int tempominutosvitoria = 0, temposegundosvitoria = 0;

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

        // Identificar quantos segundo se passaram antes do comeco do jogo para o temporizador comecar do 0 e variaveis para estabilizar a posicao original de Quinhas e Nalauritas
        if (gameState != STATE_PLAY)
        {
            segundospassados = (int)GetTime();
            checagemQuinhas = 0;
            quinhasmovimento.x = 144;
            quinhasmovimento.y = 872;
            nalaurita1movimento.x = 250;
            nalaurita1movimento.y = 784;
            nalaurita1modo = 1;
            nalaurita2modo = 1;
            nalaurita3modo = 1;
            nalaurita4modo = 1;
            nalaurita5modo = 1;
            nalaurita6modo = 1;
            nalaurita7modo = 1;
            nalaurita2movimento.x = 112;
            nalaurita2movimento.y = 175;
            nalaurita3movimento.x = 833;
            nalaurita3movimento.y = 188;
            nalaurita4movimento.x = 846;
            nalaurita4movimento.y = 176;
            nalaurita5movimento.x = 1245;
            nalaurita5movimento.y = 416;
            nalaurita6movimento.x = 1233;
            nalaurita6movimento.y = 620;
            nalaurita7movimento.x = 696;
            nalaurita7movimento.y = 891;
        }

        switch (gameState)
        {
        case STATE_MENU:
            // Menu
            if (CheckCollisionPointRec(GetMousePosition(), startButton.rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                // Vai para historia
                gameState = STATE_STORY;
                // funcao resposavel por fechar as paredes caso o jogo recomece
                recomeco();
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

            if (IsKeyDown(KEY_D) && IsKeyDown(KEY_W))
            {
                checagemQuinhas = 0;
                quinhasmovimento.x += velocidadequinhas.direita;
                quinhasmovimento.y -= velocidadequinhas.cima;
                parado = 2;
            }
            else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_A))
            {
                checagemQuinhas = 1;
                quinhasmovimento.x -= velocidadequinhas.esquerda; // Ajuste na ordem das operações
                quinhasmovimento.y -= velocidadequinhas.cima;
                parado = 2;
            }
            else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_D))
            {
                checagemQuinhas = 3;
                quinhasmovimento.x += velocidadequinhas.direita;
                quinhasmovimento.y += velocidadequinhas.baixo;
                parado = 4;
            }
            else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_A))
            {
                checagemQuinhas = 3;
                quinhasmovimento.x -= velocidadequinhas.esquerda;
                quinhasmovimento.y += velocidadequinhas.baixo;
                parado = 4;
            }
            else if (IsKeyDown(KEY_D))
            {
                checagemQuinhas = 0;
                quinhasmovimento.x += velocidadequinhas.direita;
                parado = 1;
            }
            else if (IsKeyDown(KEY_W))
            {
                checagemQuinhas = 1;
                quinhasmovimento.y -= velocidadequinhas.cima;
                parado = 2;
            }
            else if (IsKeyDown(KEY_A))
            {
                checagemQuinhas = 2;
                quinhasmovimento.x -= velocidadequinhas.esquerda;
                parado = 3;
            }
            else if (IsKeyDown(KEY_S))
            {
                checagemQuinhas = 3;
                quinhasmovimento.y += velocidadequinhas.baixo;
                parado = 4;
            }

            else
            {
                checagemQuinhas = -1; // Nenhuma tecla está sendo pressionada
            }

            // Atualiza a animação apenas se uma tecla estiver sendo pressionada
            if (checagemQuinhas != -1)
            {
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
                        frameRecQuinhas.x = (float)currentFrameQuinhas * (float)quinhasR.width / 4;
                    }
                }
            }

            // Desenha o boneco com base na última tecla pressionada
            if (!IsKeyDown(KEY_D) && !IsKeyDown(KEY_W) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_S))
            {
                if (parado == 1)
                {
                    DrawTexture(quinhasParadoD, quinhasmovimento.x, quinhasmovimento.y, WHITE);
                }

                if (parado == 2)
                {
                    DrawTexture(quinhasParadoC, quinhasmovimento.x, quinhasmovimento.y, WHITE);
                }

                if (parado == 3)
                {
                    DrawTexture(quinhasParadoE, quinhasmovimento.x, quinhasmovimento.y, WHITE);
                }

                if (parado == 4 || parado == 0)
                {
                    DrawTexture(quinhasParadoB, quinhasmovimento.x, quinhasmovimento.y, WHITE);
                }
            }

            else
            {

                if (checagemQuinhas == 0)
                    DrawTextureRec(quinhasR, frameRecQuinhas, quinhasmovimento, WHITE);
                else if (checagemQuinhas == 1)
                    DrawTextureRec(quinhasU, frameRecQuinhas, quinhasmovimento, WHITE);
                else if (checagemQuinhas == 2)
                    DrawTextureRec(quinhasL, frameRecQuinhas, quinhasmovimento, WHITE);
                else if (checagemQuinhas == 3)
                    DrawTextureRec(quinhasD, frameRecQuinhas, quinhasmovimento, WHITE);
            }

            // movimentacao de nalauritas
            if (nalaurita1modo == 1)
            {
                DrawTextureRec(nalaurita1D, frameRecnalaurita1, nalaurita1movimento, WHITE);
                nalaurita1movimento.x = nalaurita1movimento.x + nalaurita1velocidade.direita;
                framesCounterAna++;
                if (framesCounterAna >= (60 / framesSpeedAna))
                {
                    tempodeframenalaurita1 += GetFrameTime();
                    if (tempodeframenalaurita1 >= 0.2)
                    {
                        tempodeframenalaurita1 = 0;
                        currentFrameAna++;
                    }
                    if (currentFrameAna > 3)
                    {
                        frameRecnalaurita1.x = (float)currentFrameAna * (float)nalaurita1D.width / 4;
                    }
                }
            }
            if (nalaurita1modo == 2)
            {
                DrawTextureRec(nalaurita1E, frameRecnalaurita1, nalaurita1movimento, WHITE);
                nalaurita1movimento.x = nalaurita1movimento.x - nalaurita1velocidade.esquerda;
                framesCounterAna++;
                if (framesCounterAna >= (60 / framesSpeedAna))
                {
                    tempodeframenalaurita1 += GetFrameTime();
                    if (tempodeframenalaurita1 >= 0.2)
                    {
                        tempodeframenalaurita1 = 0;
                        currentFrameAna++;
                    }
                    if (currentFrameAna > 3)
                    {
                        frameRecnalaurita1.x = (float)currentFrameAna * (float)nalaurita1E.width / 4;
                    }
                }
            }
            if (nalaurita2modo == 1)
            {
                DrawTextureRec(nalaurita2B, frameRecnalaurita2, nalaurita2movimento, WHITE);
                nalaurita2movimento.y = nalaurita2movimento.y + nalaurita2velocidade.baixo;
                framescounternalaurita2++;
                if (framescounternalaurita2 >= (60 / framesSpeedAna))
                {
                    tempodeframenalaurita2 += GetFrameTime();
                    if (tempodeframenalaurita2 >= 0.2)
                    {
                        tempodeframenalaurita2 = 0;
                        currentFramenalaurita2++;
                    }
                    if (currentFramenalaurita2 > 3)
                    {
                        frameRecnalaurita2.x = (float)currentFramenalaurita2 * (float)nalaurita2B.width / 4;
                    }
                }
            }
            if (nalaurita2modo == 2)
            {
                DrawTextureRec(nalaurita2C, frameRecnalaurita2, nalaurita2movimento, WHITE);
                nalaurita2movimento.y = nalaurita2movimento.y - nalaurita2velocidade.cima;
                framescounternalaurita2++;
                if (framescounternalaurita2 >= (60 / framesSpeedAna))
                {
                    tempodeframenalaurita2 += GetFrameTime();
                    if (tempodeframenalaurita2 >= 0.2)
                    {
                        tempodeframenalaurita2 = 0;
                        currentFramenalaurita2++;
                    }
                    if (currentFramenalaurita2 > 3)
                    {
                        frameRecnalaurita2.x = (float)currentFramenalaurita2 * (float)nalaurita2C.width / 4;
                    }
                }
            }
            if (nalaurita3modo == 1)
            {
                DrawTextureRec(nalaurita3B, frameRecnalaurita3, nalaurita3movimento, WHITE);
                nalaurita3movimento.y = nalaurita3movimento.y + nalaurita3velocidade.baixo;
                framescounternalaurita3++;
                if (framescounternalaurita3 >= (60 / framesSpeedAna))
                {
                    tempodeframenalaurita3 += GetFrameTime();
                    if (tempodeframenalaurita3 >= 0.2)
                    {
                        tempodeframenalaurita3 = 0;
                        currentFramenalaurita3++;
                    }
                    if (currentFramenalaurita3 > 3)
                    {
                        frameRecnalaurita3.x = (float)currentFramenalaurita3 * (float)nalaurita3B.width / 4;
                    }
                }
            }
            if (nalaurita3modo == 2)
            {
                DrawTextureRec(nalaurita3C, frameRecnalaurita3, nalaurita3movimento, WHITE);
                nalaurita3movimento.y = nalaurita3movimento.y - nalaurita3velocidade.cima;
                framescounternalaurita3++;
                if (framescounternalaurita3 >= (60 / framesSpeedAna))
                {
                    tempodeframenalaurita3 += GetFrameTime();
                    if (tempodeframenalaurita3 >= 0.2)
                    {
                        tempodeframenalaurita3 = 0;
                        currentFramenalaurita3++;
                    }
                    if (currentFramenalaurita3 > 3)
                    {
                        frameRecnalaurita3.x = (float)currentFramenalaurita3 * (float)nalaurita3C.width / 4;
                    }
                }
            }
            if (nalaurita4modo == 1)
            {
                DrawTextureRec(nalaurita4D, frameRecnalaurita4, nalaurita4movimento, WHITE);
                nalaurita4movimento.x = nalaurita4movimento.x + nalaurita4velocidade.direita;
                framescounternalaurita4++;
                if (framescounternalaurita4 >= (60 / framesSpeedAna))
                {
                    tempodeframenalaurita4 += GetFrameTime();
                    if (tempodeframenalaurita4 >= 0.2)
                    {
                        tempodeframenalaurita4 = 0;
                        currentFramenalaurita4++;
                    }
                    if (currentFramenalaurita4 > 3)
                    {
                        frameRecnalaurita4.x = (float)currentFramenalaurita4 * (float)nalaurita4D.width / 4;
                    }
                }
            }
            if (nalaurita4modo == 2)
            {
                DrawTextureRec(nalaurita4E, frameRecnalaurita4, nalaurita4movimento, WHITE);
                nalaurita4movimento.x = nalaurita4movimento.x - nalaurita4velocidade.direita;
                framescounternalaurita4++;
                if (framescounternalaurita4 >= (60 / framesSpeedAna))
                {
                    tempodeframenalaurita4 += GetFrameTime();
                    if (tempodeframenalaurita4 >= 0.2)
                    {
                        tempodeframenalaurita4 = 0;
                        currentFramenalaurita4++;
                    }
                    if (currentFramenalaurita4 > 3)
                    {
                        frameRecnalaurita4.x = (float)currentFramenalaurita4 * (float)nalaurita4E.width / 4;
                    }
                }
            }
            if (nalaurita5modo == 1)
            {
                DrawTextureRec(nalaurita5D, frameRecnalaurita5, nalaurita5movimento, WHITE);
                nalaurita5movimento.x = nalaurita5movimento.x + nalaurita5velocidade.direita;
                framescounternalaurita5++;
                if (framescounternalaurita5 >= (60 / framesSpeedAna))
                {
                    tempodeframenalaurita5 += GetFrameTime();
                    if (tempodeframenalaurita5 >= 0.2)
                    {
                        tempodeframenalaurita5 = 0;
                        currentFramenalaurita5++;
                    }
                    if (currentFramenalaurita5 > 3)
                    {
                        frameRecnalaurita5.x = (float)currentFramenalaurita5 * (float)nalaurita5D.width / 4;
                    }
                }
            }
            if (nalaurita5modo == 2)
            {
                DrawTextureRec(nalaurita5E, frameRecnalaurita5, nalaurita5movimento, WHITE);
                nalaurita5movimento.x = nalaurita5movimento.x - nalaurita5velocidade.direita;
                framescounternalaurita5++;
                if (framescounternalaurita5 >= (60 / framesSpeedAna))
                {
                    tempodeframenalaurita5 += GetFrameTime();
                    if (tempodeframenalaurita5 >= 0.2)
                    {
                        tempodeframenalaurita5 = 0;
                        currentFramenalaurita5++;
                    }
                    if (currentFramenalaurita5 > 3)
                    {
                        frameRecnalaurita5.x = (float)currentFramenalaurita5 * (float)nalaurita5E.width / 4;
                    }
                }
            }
            if (nalaurita6modo == 1)
            {
                DrawTextureRec(nalaurita6D, frameRecnalaurita6, nalaurita6movimento, WHITE);
                nalaurita6movimento.x = nalaurita6movimento.x + nalaurita6velocidade.direita;
                framescounternalaurita6++;
                if (framescounternalaurita6 >= (60 / framesSpeedAna))
                {
                    tempodeframenalaurita6 += GetFrameTime();
                    if (tempodeframenalaurita6 >= 0.2)
                    {
                        tempodeframenalaurita6 = 0;
                        currentFramenalaurita6++;
                    }
                    if (currentFramenalaurita6 > 3)
                    {
                        frameRecnalaurita6.x = (float)currentFramenalaurita6 * (float)nalaurita6D.width / 4;
                    }
                }
            }
            if (nalaurita6modo == 2)
            {
                DrawTextureRec(nalaurita6E, frameRecnalaurita6, nalaurita6movimento, WHITE);
                nalaurita6movimento.x = nalaurita6movimento.x - nalaurita6velocidade.direita;
                framescounternalaurita6++;
                if (framescounternalaurita6 >= (60 / framesSpeedAna))
                {
                    tempodeframenalaurita6 += GetFrameTime();
                    if (tempodeframenalaurita6 >= 0.2)
                    {
                        tempodeframenalaurita6 = 0;
                        currentFramenalaurita6++;
                    }
                    if (currentFramenalaurita6 > 3)
                    {
                        frameRecnalaurita6.x = (float)currentFramenalaurita6 * (float)nalaurita6E.width / 4;
                    }
                }
            }
            if (nalaurita7modo == 1)
            {
                DrawTextureRec(nalaurita7D, frameRecnalaurita7, nalaurita7movimento, WHITE);
                nalaurita7movimento.x = nalaurita7movimento.x + nalaurita7velocidade.direita;
                framescounternalaurita7++;
                if (framescounternalaurita7 >= (60 / framesSpeedAna))
                {
                    tempodeframenalaurita7 += GetFrameTime();
                    if (tempodeframenalaurita7 >= 0.2)
                    {
                        tempodeframenalaurita7 = 0;
                        currentFramenalaurita7++;
                    }
                    if (currentFramenalaurita7 > 3)
                    {
                        frameRecnalaurita7.x = (float)currentFramenalaurita7 * (float)nalaurita7D.width / 4;
                    }
                }
            }
            if (nalaurita7modo == 2)
            {
                DrawTextureRec(nalaurita7E, frameRecnalaurita7, nalaurita7movimento, WHITE);
                nalaurita7movimento.x = nalaurita7movimento.x - nalaurita7velocidade.direita;
                framescounternalaurita7++;
                if (framescounternalaurita7 >= (60 / framesSpeedAna))
                {
                    tempodeframenalaurita7 += GetFrameTime();
                    if (tempodeframenalaurita7 >= 0.2)
                    {
                        tempodeframenalaurita7 = 0;
                        currentFramenalaurita7++;
                    }
                    if (currentFramenalaurita7 > 3)
                    {
                        frameRecnalaurita7.x = (float)currentFramenalaurita7 * (float)nalaurita7E.width / 4;
                    }
                }
            }
            // Desenhando todos os retangulos e variaveis dos retangulos na mao para realizar a colisão
            Rectangle retangulo1 = {77, 136, 35, 850};
            Rectangle retangulo2 = {1708, 136, 72, 34};
            Rectangle retangulo2D = {1705, 139, 1, 28};
            Rectangle retangulo3 = {1744, 136, 34, 850};
            Rectangle retangulo4 = {215, 952, 1562, 34};
            Rectangle retangulo5 = {111, 952, 35, 34};
            Rectangle retangulo6 = {111, 136, 1526, 34};
            Rectangle retangulo6E = {114, 139, 1527, 28};
            Rectangle retangulo7C = {110, 614, 236, 32};
            Rectangle retangulo7E = {110, 614, 238, 28};
            Rectangle retangulo7B = {110, 612, 236, 1};
            Rectangle retangulo8D = {214, 716, 32, 236};
            Rectangle retangulo8C = {216, 714, 30, 1};
            Rectangle retangulo8E = {216, 716, 32, 234};
            Rectangle retangulo9B = {246, 850, 266, 1};
            Rectangle retangulo9E = {246, 854, 270, 26};
            Rectangle retangulo9C = {246, 854, 266, 28};
            Rectangle retangulo10C = {318, 716, 98, 32};
            Rectangle retangulo10B = {318, 714, 98, 32};
            Rectangle retangulo10D = {316, 716, 2, 30};
            DrawRectangle(418, 414, 34, 364, RED);
            Rectangle retangulo11D = {418, 416, 30, 364};
            Rectangle retangulo11C = {420, 418, 28, 362};
            Rectangle retangulo11B = {420, 414, 28, 1};
            Rectangle retangulo11E = {422, 416, 30, 362};
            Rectangle retangulo12B = {452, 476, 300, 32};
            Rectangle retangulo12C = {452, 478, 300, 32};
            Rectangle retangulo13E = {318, 376, 32, 234};
            Rectangle retangulo13D = {316, 376, 32, 234};
            Rectangle retangulo13B = {318, 374, 30, 1};
            Rectangle retangulo14B = {182, 374, 132, 1};
            Rectangle retangulo14C = {182, 376, 132, 32};
            Rectangle retangulo14D = {180, 376, 132, 30};
            Rectangle retangulo15D = {180, 408, 32, 131};
            Rectangle retangulo15E = {182, 408, 32, 131};
            Rectangle retangulo15C = {182, 408, 30, 134};
            Rectangle retangulo16C = {214, 512, 27, 32};
            Rectangle retangulo16E = {214, 512, 32, 29};
            Rectangle retangulo16B = {214, 510, 30, 1};
            Rectangle retangulo17C = {216, 242, 232, 30};
            Rectangle retangulo17E = {216, 242, 235, 26};
            Rectangle retangulo17D = {213, 241, 1, 26};
            Rectangle retangulo17B = {216, 238, 232, 1};
            Rectangle retangulo18C = {421, 275, 129, 31};
            Rectangle retangulo18D = {418, 275, 1, 28};
            Rectangle retangulo18B = {421, 272, 129, 1};
            Rectangle retangulo18E = {421, 275, 132, 28};
            Rectangle retangulo19D = {520, 308, 1, 96};
            Rectangle retangulo19C = {523, 308, 28, 99};
            Rectangle retangulo19E = {523, 308, 31, 96};
            Rectangle retangulo19B = {523, 305, 28, 1};
            Rectangle retangulo20D = {555, 377, 1, 28};
            Rectangle retangulo20E = {558, 377, 233, 28};
            Rectangle retangulo20C = {558, 377, 230, 31};
            Rectangle retangulo20B = {558, 374, 230, 1};
            Rectangle retangulo21D = {621, 173, 1, 130};
            Rectangle retangulo21E = {624, 173, 31, 130};
            Rectangle retangulo21C = {624, 173, 28, 133};
            Rectangle retangulo21B = {624, 170, 28, 1};
            Rectangle retangulo22D = {656, 275, 1, 28};
            Rectangle retangulo22E = {659, 275, 166, 28};
            Rectangle retangulo22C = {659, 275, 163, 31};
            Rectangle retangulo22B = {659, 272, 163, 1};
            Rectangle retangulo23D = {792, 239, 1, 30};
            Rectangle retangulo23E = {795, 239, 31, 30};
            Rectangle retangulo23B = {795, 236, 28, 1};
            Rectangle retangulo24D = {757, 411, 1, 94};
            Rectangle retangulo24E = {760, 411, 31, 94};
            Rectangle retangulo24C = {760, 411, 28, 97};
            Rectangle retangulo25B = {453, 680, 130, 1};
            Rectangle retangulo25C = {453, 684, 130, 30};
            Rectangle retangulo26B = {591, 578, 28, 1};
            Rectangle retangulo26D = {588, 581, 1, 367};
            Rectangle retangulo26E = {591, 581, 31, 367};
            Rectangle retangulo27C = {624, 581, 198, 31};
            Rectangle retangulo27E = {624, 581, 201, 28};
            Rectangle retangulo27B = {624, 578, 198, 1};
            Rectangle retangulo28E = {1203, 170, 31, 99};
            Rectangle retangulo28D = {1200, 170, 1, 99};
            Rectangle retangulo28C = {1203, 170, 28, 102};
            Rectangle retangulo29C = {1032, 241, 164, 31};
            Rectangle retangulo29D = {1029, 241, 1, 28};
            Rectangle retangulo29B = {1032, 238, 164, 1};
            Rectangle retangulo30E = {1032, 275, 31, 60};
            Rectangle retangulo30C = {1032, 275, 28, 63};
            Rectangle retangulo31D = {894, 308, 1, 28};
            Rectangle retangulo31B = {897, 305, 129, 1};
            Rectangle retangulo31C = {897, 308, 129, 31};
            Rectangle retangulo32D = {894, 342, 1, 369};
            Rectangle retangulo32E = {897, 342, 31, 369};
            Rectangle retangulo32C = {897, 342, 28, 372};
            Rectangle retangulo33D = {690, 683, 1, 28};
            Rectangle retangulo33B = {693, 680, 198, 1};
            Rectangle retangulo33C = {693, 683, 198, 31};
            Rectangle retangulo34D = {690, 717, 1, 164};
            Rectangle retangulo34E = {693, 717, 31, 164};
            Rectangle retangulo34C = {693, 717, 28, 167};
            Rectangle retangulo35B = {727, 850, 231, 1};
            Rectangle retangulo35C = {727, 853, 231, 31};
            Rectangle retangulo35E = {727, 853, 234, 28};
            Rectangle retangulo36E = {930, 784, 31, 65};
            Rectangle retangulo36D = {927, 784, 1, 65};
            Rectangle retangulo37E = {930, 784, 406, 28};
            Rectangle retangulo37C = {930, 784, 400, 31};
            Rectangle retangulo37B = {930, 781, 400, 1};
            Rectangle retangulo38D = {1301, 818, 1, 63};
            Rectangle retangulo38E = {1304, 818, 31, 63};
            Rectangle retangulo38C = {1304, 818, 28, 66};
            Rectangle retangulo39D = {996, 479, 1, 299};
            Rectangle retangulo39E = {999, 479, 31, 299};
            Rectangle retangulo40C = {999, 479, 130, 31};
            Rectangle retangulo40B = {999, 476, 130, 1};
            Rectangle retangulo41E = {1134, 344, 31, 162};
            Rectangle retangulo41D = {1131, 344, 1, 162};
            Rectangle retangulo41C = {1134, 344, 28, 165};
            Rectangle retangulo41B = {1134, 341, 28, 1};
            Rectangle retangulo42B = {1168, 340, 199, 1};
            Rectangle retangulo42C = {1168, 343, 199, 31};
            Rectangle retangulo42E = {1168, 343, 202, 28};
            Rectangle retangulo43D = {1336, 242, 1, 96};
            Rectangle retangulo43E = {1339, 242, 31, 96};
            Rectangle retangulo43B = {1339, 239, 28, 1};
            Rectangle retangulo43C = {1339, 242, 28, 99};
            Rectangle retangulo44B = {1407, 680, 28, 1};
            Rectangle retangulo44D = {1404, 683, 1, 266};
            Rectangle retangulo44E = {1407, 683, 31, 266};
            Rectangle retangulo45B = {1134, 680, 267, 1};
            Rectangle retangulo45C = {1134, 683, 267, 31};
            Rectangle retangulo46D = {1098, 581, 1, 130};
            Rectangle retangulo46E = {1101, 581, 31, 130};
            Rectangle retangulo46C = {1101, 581, 28, 133};
            Rectangle retangulo46B = {1101, 578, 28, 1};
            Rectangle retangulo47E = {1134, 581, 132, 28};
            Rectangle retangulo47B = {1134, 578, 129, 1};
            Rectangle retangulo47C = {1134, 581, 129, 31};
            Rectangle retangulo48D = {1233, 479, 1, 96};
            Rectangle retangulo48E = {1236, 479, 31, 96};
            Rectangle retangulo48B = {1236, 476, 28, 1};
            Rectangle retangulo49B = {1270, 476, 266, 1};
            Rectangle retangulo49C = {1270, 479, 266, 31};
            Rectangle retangulo50D = {1505, 479, 1, 402};
            Rectangle retangulo50E = {1508, 479, 31, 402};
            Rectangle retangulo50B = {1508, 476, 28, 1};
            Rectangle retangulo50C = {1508, 479, 28, 405};
            Rectangle retangulo51B = {1542, 850, 28, 1};
            Rectangle retangulo51C = {1542, 853, 28, 31};
            Rectangle retangulo51E = {1542, 853, 31, 28};
            Rectangle retangulo52D = {1641, 513, 1, 437};
            Rectangle retangulo52E = {1644, 513, 31, 437};
            Rectangle retangulo52B = {1644, 510, 28, 1};
            Rectangle retangulo53D = {1438, 172, 1, 232};
            Rectangle retangulo53E = {1441, 172, 31, 232};
            Rectangle retangulo53C = {1441, 172, 28, 235};
            Rectangle retangulo54E = {1475, 377, 66, 28};
            Rectangle retangulo54B = {1475, 374, 63, 1};
            Rectangle retangulo54C = {1475, 377, 63, 31};
            Rectangle retangulo55B = {1611, 238, 28, 1};
            Rectangle retangulo55D = {1608, 241, 1, 165};
            Rectangle retangulo55E = {1611, 241, 31, 165};
            Rectangle retangulo55C = {1611, 241, 28, 168};
            Rectangle retangulo56B = {1645, 238, 96, 1};
            Rectangle retangulo56C = {1645, 241, 96, 31};
            // retangulo identificado para saber se o jogador conquistou a vitoria e retangulo para impedir a passagem por baixo
            Rectangle retangulovitoria = {1647, 146, 45, 1};
            Rectangle retangulofinal = {148, 952, 65, 1};
            // retangulos dos posteres
            Rectangle retangulop1 = {213, 644, 1, 69};
            Rectangle retangulop2 = {350, 646, 20, 1};
            Rectangle retangulop4 = {1369, 170, 1, 69};
            Rectangle retangulop5 = {1541, 407, 67, 1};
            Rectangle retangulop6 = {213, 170, 1, 68};
            Rectangle retangulop7 = {825, 578, 69, 1};
            Rectangle retangulop8 = {266, 543, 50, 1};
            Rectangle retangulop9 = {825, 171, 1, 64};
            Rectangle retangulop10 = {790, 508, 1, 70};
            Rectangle retangulop12 = {1637, 169, 68, 1};
            // retangulos para saber a width e height de quinhas na hora da colisao, um pra cada direcao
            Rectangle retanguloquinhasB = {quinhasmovimento.x, quinhasmovimento.y, (float)quinhasD.width / 4, quinhasD.height};
            Rectangle retanguloquinhasC = {quinhasmovimento.x, quinhasmovimento.y, (float)quinhasU.width / 4, quinhasU.height};
            Rectangle retanguloquinhasD = {quinhasmovimento.x, quinhasmovimento.y, (float)quinhasR.width / 4, quinhasR.height};
            Rectangle retanguloquinhasD2 = {quinhasmovimento.x, quinhasmovimento.y, (float)quinhasR.width / 4, quinhasR.height};
            Rectangle retanguloquinhasE = {quinhasmovimento.x, quinhasmovimento.y, (float)quinhasL.width / 4, quinhasL.height};
            // retangulos para saber a width e height de cada nalaurita na hora da colisao
            Rectangle retangulonalaurita1D = {nalaurita1movimento.x, nalaurita1movimento.y, (float)nalaurita1D.width / 4, nalaurita1D.height};
            Rectangle retangulonalaurita1E = {nalaurita1movimento.x, nalaurita1movimento.y, (float)nalaurita1E.width / 4, nalaurita1E.height};
            Rectangle retangulonalaurita2C = {nalaurita2movimento.x, nalaurita2movimento.y, (float)nalaurita2C.width / 4, nalaurita2C.height};
            Rectangle retangulonalaurita2B = {nalaurita2movimento.x, nalaurita2movimento.y, (float)nalaurita2B.width / 4, nalaurita2B.height};
            Rectangle retangulonalaurita3C = {nalaurita3movimento.x, nalaurita3movimento.y, (float)nalaurita3C.width / 4, nalaurita3C.height};
            Rectangle retangulonalaurita3B = {nalaurita3movimento.x, nalaurita3movimento.y, (float)nalaurita3B.width / 4, nalaurita3B.height};
            Rectangle retangulonalaurita4D = {nalaurita4movimento.x, nalaurita4movimento.y, (float)nalaurita4D.width / 4, nalaurita4D.height};
            Rectangle retangulonalaurita4E = {nalaurita4movimento.x, nalaurita4movimento.y, (float)nalaurita4E.width / 4, nalaurita4E.height};
            Rectangle retangulonalaurita5D = {nalaurita5movimento.x, nalaurita5movimento.y, (float)nalaurita5D.width / 4, nalaurita5D.height};
            Rectangle retangulonalaurita5E = {nalaurita5movimento.x, nalaurita5movimento.y, (float)nalaurita5E.width / 4, nalaurita5E.height};
            Rectangle retangulonalaurita6D = {nalaurita6movimento.x, nalaurita6movimento.y, (float)nalaurita6D.width / 4, nalaurita6D.height};
            Rectangle retangulonalaurita6E = {nalaurita6movimento.x, nalaurita6movimento.y, (float)nalaurita6E.width / 4, nalaurita6E.height};
            Rectangle retangulonalaurita7D = {nalaurita7movimento.x, nalaurita7movimento.y, (float)nalaurita7D.width / 4, nalaurita7D.height};
            Rectangle retangulonalaurita7E = {nalaurita7movimento.x, nalaurita7movimento.y, (float)nalaurita7E.width / 4, nalaurita7E.height};
            // colisoes
            if (CheckCollisionRecs(retanguloquinhasD, retangulo2D) || CheckCollisionRecs(retanguloquinhasD, retangulo3) || (poster6.isVisible == 1 && CheckCollisionRecs(retanguloquinhasD, retangulop6)) || (poster1.isVisible == 1 && CheckCollisionRecs(retanguloquinhasD, retangulop1)) || CheckCollisionRecs(retanguloquinhasD2, retangulo8D) || CheckCollisionRecs(retanguloquinhasD, retangulo10D) || CheckCollisionRecs(retanguloquinhasD, retangulo11D) || CheckCollisionRecs(retanguloquinhasD, retangulo13D) || CheckCollisionRecs(retanguloquinhasD, retangulo14D) || CheckCollisionRecs(retanguloquinhasD, retangulo15D) || CheckCollisionRecs(retanguloquinhasD, retangulo17D) || CheckCollisionRecs(retanguloquinhasD, retangulo18D) || CheckCollisionRecs(retanguloquinhasD, retangulo19D) || CheckCollisionRecs(retanguloquinhasD, retangulo20D) || CheckCollisionRecs(retanguloquinhasD, retangulo21D) || CheckCollisionRecs(retanguloquinhasD, retangulo22D) || CheckCollisionRecs(retanguloquinhasD, retangulo23D) || CheckCollisionRecs(retanguloquinhasD, retangulo24D) || CheckCollisionRecs(retanguloquinhasD, retangulo26D) || CheckCollisionRecs(retanguloquinhasD, retangulo28D) || CheckCollisionRecs(retanguloquinhasD, retangulo29D) || CheckCollisionRecs(retanguloquinhasD, retangulo31D) || CheckCollisionRecs(retanguloquinhasD, retangulo32D) || CheckCollisionRecs(retanguloquinhasD, retangulo33D) || CheckCollisionRecs(retanguloquinhasD, retangulo34D) || CheckCollisionRecs(retanguloquinhasD, retangulo36D) || CheckCollisionRecs(retanguloquinhasD, retangulo38D) || CheckCollisionRecs(retanguloquinhasD, retangulo39D) || CheckCollisionRecs(retanguloquinhasD, retangulo41D) || CheckCollisionRecs(retanguloquinhasD, retangulo43D) || CheckCollisionRecs(retanguloquinhasD, retangulo44D) || CheckCollisionRecs(retanguloquinhasD, retangulo46D) || CheckCollisionRecs(retanguloquinhasD, retangulo48D) || CheckCollisionRecs(retanguloquinhasD, retangulo50D) || CheckCollisionRecs(retanguloquinhasD, retangulo52D) || CheckCollisionRecs(retanguloquinhasD, retangulo53D) || CheckCollisionRecs(retanguloquinhasD, retangulo55D))
            {
                velocidadequinhas.direita = 0;
            }
            else
            {
                velocidadequinhas.direita = 3;
            }
            if (CheckCollisionRecs(retanguloquinhasC, retangulo2) || (poster12.isVisible == 1 && CheckCollisionRecs(retanguloquinhasC, retangulop12)) || (poster8.isVisible == 1 && CheckCollisionRecs(retanguloquinhasC, retangulop8)) || (poster5.isVisible == 1 && CheckCollisionRecs(retanguloquinhasC, retangulop5)) || (poster2.isVisible == 1 && CheckCollisionRecs(retanguloquinhasC, retangulop2)) || CheckCollisionRecs(retanguloquinhasC, retangulo6) || CheckCollisionRecs(retanguloquinhasC, retangulo7C) || CheckCollisionRecs(retanguloquinhasC, retangulo9C) || CheckCollisionRecs(retanguloquinhasC, retangulo10C) || CheckCollisionRecs(retanguloquinhasC, retangulo11C) || CheckCollisionRecs(retanguloquinhasC, retangulo12C) || CheckCollisionRecs(retanguloquinhasC, retangulo14C) || CheckCollisionRecs(retanguloquinhasC, retangulo15C) || CheckCollisionRecs(retanguloquinhasC, retangulo16C) || CheckCollisionRecs(retanguloquinhasC, retangulo17C) || CheckCollisionRecs(retanguloquinhasC, retangulo18C) || CheckCollisionRecs(retanguloquinhasC, retangulo19C) || CheckCollisionRecs(retanguloquinhasC, retangulo20C) || CheckCollisionRecs(retanguloquinhasC, retangulo21C) || CheckCollisionRecs(retanguloquinhasC, retangulo22C) || CheckCollisionRecs(retanguloquinhasC, retangulo24C) || CheckCollisionRecs(retanguloquinhasC, retangulo25C) || CheckCollisionRecs(retanguloquinhasC, retangulo27C) || CheckCollisionRecs(retanguloquinhasC, retangulo28C) || CheckCollisionRecs(retanguloquinhasC, retangulo29C) || CheckCollisionRecs(retanguloquinhasC, retangulo30C) || CheckCollisionRecs(retanguloquinhasC, retangulo31C) || CheckCollisionRecs(retanguloquinhasC, retangulo32C) || CheckCollisionRecs(retanguloquinhasC, retangulo33C) || CheckCollisionRecs(retanguloquinhasC, retangulo34C) || CheckCollisionRecs(retanguloquinhasC, retangulo35C) || CheckCollisionRecs(retanguloquinhasC, retangulo37C) || CheckCollisionRecs(retanguloquinhasC, retangulo38C) || CheckCollisionRecs(retanguloquinhasC, retangulo40C) || CheckCollisionRecs(retanguloquinhasC, retangulo41C) || CheckCollisionRecs(retanguloquinhasC, retangulo42C) || CheckCollisionRecs(retanguloquinhasC, retangulo43C) || CheckCollisionRecs(retanguloquinhasC, retangulo45C) || CheckCollisionRecs(retanguloquinhasC, retangulo46C) || CheckCollisionRecs(retanguloquinhasC, retangulo47C) || CheckCollisionRecs(retanguloquinhasC, retangulo49C) || CheckCollisionRecs(retanguloquinhasC, retangulo50C) || CheckCollisionRecs(retanguloquinhasC, retangulo51C) || CheckCollisionRecs(retanguloquinhasC, retangulo53C) || CheckCollisionRecs(retanguloquinhasC, retangulo54C) || CheckCollisionRecs(retanguloquinhasC, retangulo55C) || CheckCollisionRecs(retanguloquinhasC, retangulo56C))
            {
                velocidadequinhas.cima = 0;
            }
            else
            {
                velocidadequinhas.cima = 3;
            }
            if (CheckCollisionRecs(retanguloquinhasB, retangulo4) || (poster7.isVisible == 1 && CheckCollisionRecs(retanguloquinhasB, retangulop7)) || CheckCollisionRecs(retanguloquinhasB, retangulo5) || CheckCollisionRecs(retanguloquinhasB, retangulo8C) || CheckCollisionRecs(retanguloquinhasB, retangulo9B) || CheckCollisionRecs(retanguloquinhasB, retangulo7B) || CheckCollisionRecs(retanguloquinhasB, retangulo10B) || CheckCollisionRecs(retanguloquinhasB, retangulo11B) || CheckCollisionRecs(retanguloquinhasB, retangulo12B) || CheckCollisionRecs(retanguloquinhasB, retangulo13B) || CheckCollisionRecs(retanguloquinhasB, retangulo14B) || CheckCollisionRecs(retanguloquinhasB, retangulo16B) || CheckCollisionRecs(retanguloquinhasB, retangulo17B) || CheckCollisionRecs(retanguloquinhasB, retangulo18B) || CheckCollisionRecs(retanguloquinhasB, retangulo19B) || CheckCollisionRecs(retanguloquinhasB, retangulo20B) || CheckCollisionRecs(retanguloquinhasB, retangulo21B) || CheckCollisionRecs(retanguloquinhasB, retangulo22B) || CheckCollisionRecs(retanguloquinhasB, retangulo23B) || CheckCollisionRecs(retanguloquinhasB, retangulo25B) || CheckCollisionRecs(retanguloquinhasB, retangulo26B) || CheckCollisionRecs(retanguloquinhasB, retangulo27B) || CheckCollisionRecs(retanguloquinhasB, retangulo29B) || CheckCollisionRecs(retanguloquinhasB, retangulo31B) || CheckCollisionRecs(retanguloquinhasB, retangulo33B) || CheckCollisionRecs(retanguloquinhasB, retangulo35B) || CheckCollisionRecs(retanguloquinhasB, retangulo37B) || CheckCollisionRecs(retanguloquinhasB, retangulo40B) || CheckCollisionRecs(retanguloquinhasB, retangulo41B) || CheckCollisionRecs(retanguloquinhasB, retangulo42B) || CheckCollisionRecs(retanguloquinhasB, retangulo43B) || CheckCollisionRecs(retanguloquinhasB, retangulo44B) || CheckCollisionRecs(retanguloquinhasB, retangulo45B) || CheckCollisionRecs(retanguloquinhasB, retangulo46B) || CheckCollisionRecs(retanguloquinhasB, retangulo47B) || CheckCollisionRecs(retanguloquinhasB, retangulo48B) || CheckCollisionRecs(retanguloquinhasB, retangulo49B) || CheckCollisionRecs(retanguloquinhasB, retangulo50B) || CheckCollisionRecs(retanguloquinhasB, retangulo51B) || CheckCollisionRecs(retanguloquinhasB, retangulo52B) || CheckCollisionRecs(retanguloquinhasB, retangulo54B) || CheckCollisionRecs(retanguloquinhasB, retangulo55B) || CheckCollisionRecs(retanguloquinhasB, retangulo56B) || CheckCollisionRecs(retanguloquinhasB, retangulofinal))
            {
                velocidadequinhas.baixo = 0;
            }
            else
            {
                velocidadequinhas.baixo = 3;
            }
            if (CheckCollisionRecs(retanguloquinhasE, retangulo6E) || CheckCollisionRecs(retanguloquinhasE, retangulo1) || (poster10.isVisible == 1 && CheckCollisionRecs(retanguloquinhasE, retangulop10)) || (poster4.isVisible == 1 && CheckCollisionRecs(retanguloquinhasE, retangulop4)) || CheckCollisionRecs(retanguloquinhasE, retangulo8E) || CheckCollisionRecs(retanguloquinhasE, retangulo9E) || CheckCollisionRecs(retanguloquinhasE, retangulo7E) || CheckCollisionRecs(retanguloquinhasE, retangulo11E) || CheckCollisionRecs(retanguloquinhasE, retangulo13E) || CheckCollisionRecs(retanguloquinhasE, retangulo15E) || CheckCollisionRecs(retanguloquinhasE, retangulo16E) || CheckCollisionRecs(retanguloquinhasE, retangulo17E) || CheckCollisionRecs(retanguloquinhasE, retangulo18E) || CheckCollisionRecs(retanguloquinhasE, retangulo19E) || CheckCollisionRecs(retanguloquinhasE, retangulo20E) || CheckCollisionRecs(retanguloquinhasE, retangulo21E) || CheckCollisionRecs(retanguloquinhasE, retangulo22E) || CheckCollisionRecs(retanguloquinhasE, retangulo23E) || CheckCollisionRecs(retanguloquinhasE, retangulo24E) || CheckCollisionRecs(retanguloquinhasE, retangulo26E) || CheckCollisionRecs(retanguloquinhasE, retangulo27E) || CheckCollisionRecs(retanguloquinhasE, retangulo28E) || CheckCollisionRecs(retanguloquinhasE, retangulo30E) || CheckCollisionRecs(retanguloquinhasE, retangulo32E) || CheckCollisionRecs(retanguloquinhasE, retangulo34E) || CheckCollisionRecs(retanguloquinhasE, retangulo35E) || CheckCollisionRecs(retanguloquinhasE, retangulo36E) || CheckCollisionRecs(retanguloquinhasE, retangulo37E) || CheckCollisionRecs(retanguloquinhasE, retangulo38E) || CheckCollisionRecs(retanguloquinhasE, retangulo39E) || CheckCollisionRecs(retanguloquinhasE, retangulo41E) || CheckCollisionRecs(retanguloquinhasE, retangulo42E) || CheckCollisionRecs(retanguloquinhasE, retangulo43E) || CheckCollisionRecs(retanguloquinhasE, retangulo44E) || CheckCollisionRecs(retanguloquinhasE, retangulo46E) || CheckCollisionRecs(retanguloquinhasE, retangulo47E) || CheckCollisionRecs(retanguloquinhasE, retangulo48E) || CheckCollisionRecs(retanguloquinhasE, retangulo50E) || CheckCollisionRecs(retanguloquinhasE, retangulo51E) || CheckCollisionRecs(retanguloquinhasE, retangulo52E) || CheckCollisionRecs(retanguloquinhasE, retangulo53E) || CheckCollisionRecs(retanguloquinhasE, retangulo54E) || CheckCollisionRecs(retanguloquinhasE, retangulo55E))
            {
                velocidadequinhas.esquerda = 0;
            }
            else
            {
                velocidadequinhas.esquerda = 3;
            }
            // Colisoes de nalauritas
            if (CheckCollisionRecs(retangulonalaurita1D, retangulo26E))
            {
                nalaurita1modo = 2;
            }
            if (CheckCollisionRecs(retangulonalaurita1E, retangulo8E))
            {
                nalaurita1modo = 1;
            }
            if (CheckCollisionRecs(retangulonalaurita2B, retangulo7C))
            {
                nalaurita2modo = 2;
            }
            if (CheckCollisionRecs(retangulonalaurita2C, retangulo6))
            {
                nalaurita2modo = 1;
            }
            if (CheckCollisionRecs(retangulonalaurita3C, retangulo6))
            {
                nalaurita3modo = 1;
            }
            if (CheckCollisionRecs(retangulonalaurita3B, retangulo33B) || (poster7.isVisible == 1 && CheckCollisionRecs(retangulonalaurita3B, retangulop7)))
            {
                nalaurita3modo = 2;
            }
            if (CheckCollisionRecs(retangulonalaurita4D, retangulo28D))
            {
                nalaurita4modo = 2;
            }
            if (CheckCollisionRecs(retangulonalaurita4E, retangulo21E) || (poster9.isVisible && CheckCollisionRecs(retangulonalaurita4E, retangulop9)))
            {
                nalaurita4modo = 1;
            }
            if (CheckCollisionRecs(retangulonalaurita5D, retangulo3))
            {
                nalaurita5modo = 2;
            }
            if (CheckCollisionRecs(retangulonalaurita5E, retangulo41E))
            {
                nalaurita5modo = 1;
            }
            if (CheckCollisionRecs(retangulonalaurita6D, retangulo50D))
            {
                nalaurita6modo = 2;
            }
            if (CheckCollisionRecs(retangulonalaurita6E, retangulo46E))
            {
                nalaurita6modo = 1;
            }
            if (CheckCollisionRecs(retangulonalaurita7D, retangulo44D))
            {
                nalaurita7modo = 2;
            }
            if (CheckCollisionRecs(retangulonalaurita7E, retangulo26E))
            {
                nalaurita7modo = 1;
            }
            // condicao de vitoria
            if (CheckCollisionRecs(retanguloquinhasC, retangulovitoria))
            {
                tempominutosvitoria = tempominutos;
                temposegundosvitoria = temposegundos;
                gameState = STATE_WIN;
            }
            // colisao entre quinhas e analaura
            int toqueinimigo = 5;
            if (derrota(quinhasmovimento, toqueinimigo,
                        retangulonalaurita1D,
                        retangulonalaurita1E,
                        retangulonalaurita2B,
                        retangulonalaurita2C,
                        retangulonalaurita3C,
                        retangulonalaurita3B,
                        retangulonalaurita4D,
                        retangulonalaurita4E,
                        retangulonalaurita5D,
                        retangulonalaurita5E,
                        retangulonalaurita6D,
                        retangulonalaurita7D,
                        retangulonalaurita7E))
            {
                gameState = STATE_LOSE;
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
                recomeco();
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
                recomeco();
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
            recomeco();
            ShowStory(story);
            break;
        case STATE_PLAY:
            // Jogo
            ShowPlay(screenWidth, screenHeight, pontuacaoPlacar);
            DrawText(TextFormat("%d:%d", tempominutos, temposegundos), screenWidth / 5, screenHeight / 15, 30, WHITE);
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
            ShowWin(screenWidth, screenHeight, textureWin, backButtonWin, exitButtonWin, tempominutosvitoria, temposegundosvitoria);
            drawwallverticalbloqueio(4, 15, 16);    // 1 coluna e 2 linhas
            drawwallhorizontalbloqueio(14, 8, 9);   // 1 linhas e 2 coluna
            drawwallverticalbloqueio(37, 1, 2);     // 1 coluna e 2 linhas
            drawwallhorizontalbloqueio(7, 43, 44);  // 1 linhas e 2 coluna
            drawwallverticalbloqueio(4, 1, 2);      // 1 coluna e 2 linhas
            drawwallhorizontalbloqueio(13, 22, 23); // 1 linhas e 2 coluna
            drawwallhorizontalbloqueio(11, 5, 6);   // 1 linhas e 2 coluna
            drawwallverticalbloqueio(21, 1, 2);     // 1 coluna e 2 linhas
            drawwallverticalbloqueio(20, 11, 12);   // 1 coluna e 2 linhas
            drawwallhorizontalbloqueio(0, 46, 47);  // 1 linhas e 2 coluna

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

            tempominutos=0;
            
            break;
        case STATE_LOSE:
            // Derrota
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

            tempominutos=0;

            ShowLose(screenWidth, screenHeight, textureLose, backButtonLose, exitButtonLose);
            
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
    UnloadTexture(quinhasR);
    UnloadTexture(quinhasD);
    UnloadTexture(quinhasL);
    UnloadTexture(quinhasU);
    UnloadTexture(nalaurita1D);
    UnloadTexture(nalaurita1E);
    UnloadTexture(nalaurita2C);
    UnloadTexture(nalaurita2B);
    UnloadTexture(nalaurita3B);
    UnloadTexture(nalaurita3C);
    UnloadTexture(nalaurita4D);
    UnloadTexture(nalaurita4E);
    UnloadTexture(nalaurita5D);
    UnloadTexture(nalaurita5E);
    UnloadTexture(nalaurita6D);
    UnloadTexture(nalaurita6E);
    UnloadTexture(nalaurita7D);
    UnloadTexture(nalaurita7E);
    UnloadTexture(quinhasParadoB);
    UnloadTexture(quinhasParadoC);
    UnloadTexture(quinhasParadoD);
    UnloadTexture(quinhasParadoE);
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
