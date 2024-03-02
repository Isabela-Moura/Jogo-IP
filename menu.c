#include "menu.h"
#include "raylib.h"

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

void DrawBase()
{
    ClearBackground(BLACK);
    DrawBorders(8, 5, 5, SKYBLUE, BLACK, SKYBLUE);
}

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

/*void ShowWin(int screenWidth, int screenHeight, Texture2D textureWin, Button backButtonWin, Button exitButtonWin)
{
    int textureWidthWin = textureWin.width;
    int textureHeightWin = textureWin.height;
    int posXWin = (screenWidth - textureWidthWin) / 2;
    int posYWin = (screenHeight - textureHeightWin) / 4;
    DrawTexture(textureWin, posXWin, posYWin, WHITE);
    DrawButton(backButtonWin, 3, SKYBLUE, 5, BLACK);
    DrawButton(exitButtonWin, 3, SKYBLUE, 5, BLACK);
    if (CheckCollisionPointRec(GetMousePosition(), backButtonWin.rect))
    {
        DrawButton(backButtonWin, 3, BLUE, 5, BLACK);
    }
    if (CheckCollisionPointRec(GetMousePosition(), exitButtonWin.rect))
    {
        DrawButton(exitButtonWin, 3, BLUE, 5, BLACK);
    }
}

void ShowLose(int screenWidth, int screenHeight, Texture2D textureLose, Button backButtonLose, Button exitButtonLose)
{
    int textureWidthLose = textureLose.width;
    int textureHeightLose = textureLose.height;
    int posXLose = (screenWidth - textureWidthLose) / 2;
    int posYLose = (screenHeight - textureHeightLose) / 4;
    DrawTexture(textureLose, posXLose, posYLose, WHITE);
    DrawButton(backButtonLose, 3, SKYBLUE, 5, BLACK);
    DrawButton(exitButtonLose, 3, SKYBLUE, 5, BLACK);
    if (CheckCollisionPointRec(GetMousePosition(), backButtonLose.rect))
    {
        DrawButton(backButtonLose, 3, BLUE, 5, BLACK);
    }
    if (CheckCollisionPointRec(GetMousePosition(), exitButtonLose.rect))
    {
        DrawButton(exitButtonLose, 3, BLUE, 5, BLACK);
    }
}*/