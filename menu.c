#include "menu.h"
#include "raylib.h"

void DrawButton(Button button, int borderWidth1, Color borderColor1, int borderWidth2, Color borderColor2)
{
    Color buttonColor = button.color;

    if (CheckCollisionPointRec(GetMousePosition(), button.rect))
    {
        buttonColor = button.hoverColor;
    }

    // Desenha retangulo
    DrawRectangleRec(button.rect, buttonColor);

    // Bordas duplas
    DrawRectangleLinesEx(button.rect, borderWidth1, borderColor1);
    DrawRectangleLinesEx((Rectangle){button.rect.x + borderWidth1, button.rect.y + borderWidth1, button.rect.width - 2 * borderWidth1, button.rect.height - 2 * borderWidth1}, borderWidth2, borderColor2);

    float textX = button.rect.x + (button.rect.width - MeasureText(button.text, 26)) / 2;
    float textY = button.rect.y + (button.rect.height - 26) / 2;
    // Texto
    DrawText(button.text, textX, textY, 26, BLACK);
}

void ShowMenu(int screenWidth, int screenHeight, Texture2D texture, Texture2D anaMenu, Rectangle frameRecAna, Vector2 positionAna, Texture2D quinhasMenu, Rectangle frameRecQuinhas, Vector2 positionQuinhas, Button startButton, Button howToPLayButton, Button creditsButton, Button exitButton)
{
    // Nome do jogo
    int textureWidth = texture.width;
    int textureHeight = texture.height;
    int posX = (screenWidth - textureWidth) / 2;
    int posY = (screenHeight - textureHeight) / 8;
    DrawTexture(texture, posX, posY, WHITE);
    // Ana Laura e Quinhas na entrada
    DrawTextureRec(anaMenu, frameRecAna, positionAna, WHITE);
    DrawTextureRec(quinhasMenu, frameRecQuinhas, positionQuinhas, WHITE);
    // Desenha botoes
    DrawButton(startButton, 3, SKYBLUE, 5, BLACK);
    DrawButton(howToPLayButton, 3, SKYBLUE, 5, BLACK);
    DrawButton(creditsButton, 3, SKYBLUE, 5, BLACK);
    DrawButton(exitButton, 3, SKYBLUE, 5, BLACK);
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
}

void ShowStory(Texture2D texture)
{
    static float alpha = 0.0f;
    alpha += GetFrameTime() * 0.5f;
    if (alpha > 1.0f)
    {
        alpha = 1.0f;
    }
    DrawTexturePro(texture, (Rectangle){0, 0, texture.width, texture.height}, (Rectangle){20, 20, GetScreenWidth() - 40, GetScreenHeight() - 40}, (Vector2){0, 0}, 0.0f, Fade(WHITE, alpha));
}

void ShowHowToPlay(int screenWidth, int screenHeight, Texture2D textureHowToPlay, Button backButton)
{
    int textureWidthHowToPlay = textureHowToPlay.width;
    int textureHeightHowToPlay = textureHowToPlay.height;
    int posXHowToPlay = (screenWidth - textureWidthHowToPlay) / 2;
    int posYHowToPlay = (screenHeight - textureHeightHowToPlay) / 4;
    DrawTexture(textureHowToPlay, posXHowToPlay, posYHowToPlay, WHITE);
    DrawButton(backButton, 3, SKYBLUE, 5, BLACK);
    if (CheckCollisionPointRec(GetMousePosition(), backButton.rect))
    {

        DrawButton(backButton, 3, BLUE, 5, BLACK);
    }
}

void ShowCredits(int screenWidth, int screenHeight, Texture2D textureCredits, Button backButton)
{
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
}
