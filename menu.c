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

    float textX = button.rect.x + (button.rect.width - MeasureText(button.text, 52)) / 2;
    float textY = button.rect.y + (button.rect.height - 52) / 2;
    // Texto
    DrawText(button.text, textX, textY, 52, BLACK);
}

void ShowMenu(Texture2D background, Button startButton, Button howToPLayButton, Button creditsButton, Button exitButton)
{
    static float alpha = 1.0f;
    DrawTexturePro(background, (Rectangle){0, 0, background.width, background.height}, (Rectangle){20, 20, GetScreenWidth() - 40, GetScreenHeight() - 40}, (Vector2){0, 0}, 0.0f, Fade(WHITE, alpha));
    // Desenha botoes
    DrawButton(startButton, 6, RED, 10, BLACK);
    DrawButton(howToPLayButton, 6, RED, 10, BLACK);
    DrawButton(creditsButton, 6, RED, 10, BLACK);
    DrawButton(exitButton, 6, RED, 10, BLACK);
    if (CheckCollisionPointRec(GetMousePosition(), startButton.rect))
    {
        DrawButton(startButton, 6, MAROON, 10, BLACK);
    }
    if (CheckCollisionPointRec(GetMousePosition(), howToPLayButton.rect))
    {
        DrawButton(howToPLayButton, 6, MAROON, 10, BLACK);
    }
    if (CheckCollisionPointRec(GetMousePosition(), creditsButton.rect))
    {
        DrawButton(creditsButton, 6, MAROON, 10, BLACK);
    }
    if (CheckCollisionPointRec(GetMousePosition(), exitButton.rect))
    {
        DrawButton(exitButton, 6, MAROON, 10, BLACK);
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
    static float alpha = 1.0f;
    DrawTexturePro(textureHowToPlay, (Rectangle){0, 0, textureHowToPlay.width, textureHowToPlay.height}, (Rectangle){20, 20, GetScreenWidth() - 40, GetScreenHeight() - 40}, (Vector2){0, 0}, 0.0f, Fade(WHITE, alpha));
    DrawButton(backButton, 6, RED, 10, BLACK);
    if (CheckCollisionPointRec(GetMousePosition(), backButton.rect))
    {

        DrawButton(backButton, 6, MAROON, 10, BLACK);
    }
}

void ShowCredits(int screenWidth, int screenHeight, Texture2D textureCredits, Button backButton)
{
    static float alpha = 1.0f;
    DrawTexturePro(textureCredits, (Rectangle){0, 0, textureCredits.width, textureCredits.height}, (Rectangle){20, 20, GetScreenWidth() - 40, GetScreenHeight() - 40}, (Vector2){0, 0}, 0.0f, Fade(WHITE, alpha));
    DrawButton(backButton, 6, RED, 10, BLACK);
    if (CheckCollisionPointRec(GetMousePosition(), backButton.rect))
    {

        DrawButton(backButton, 6, MAROON, 10, BLACK);
    }
}

/*void ShowWin(int screenWidth, int screenHeight, Texture2D textureWin, Button backButtonWin, Button exitButtonWin)
{
    static float alpha = 0.0f;
    alpha += GetFrameTime() * 0.5f;
    if (alpha > 1.0f)
    {
        alpha = 1.0f;
    }
    DrawTexturePro(texture, (Rectangle){0, 0, texture.width, texture.height}, (Rectangle){20, 20, GetScreenWidth() - 40, GetScreenHeight() - 40}, (Vector2){0, 0}, 0.0f, Fade(WHITE, alpha));

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
    static float alpha = 0.0f;
    alpha += GetFrameTime() * 0.5f;
    if (alpha > 1.0f)
    {
        alpha = 1.0f;
    }
    DrawTexturePro(texture, (Rectangle){0, 0, texture.width, texture.height}, (Rectangle){20, 20, GetScreenWidth() - 40, GetScreenHeight() - 40}, (Vector2){0, 0}, 0.0f, Fade(WHITE, alpha));
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