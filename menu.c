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
    DrawBorders(16, 10, 10, RED, BLACK, RED);
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

    float textX = button.rect.x + (button.rect.width - MeasureText(button.text, 40)) / 2;
    float textY = button.rect.y + (button.rect.height - 40) / 2;
    // Texto
    DrawText(button.text, textX, textY, 40, BLACK);
}

void ShowMenu(Texture2D background, Button startButton, Button howToPLayButton, Button creditsButton, Button exitButton)
{
    static float alpha = 1.0f;
    DrawTexturePro(background, (Rectangle){0, 0, background.width, background.height}, (Rectangle){40, 40, GetScreenWidth() - 80, GetScreenHeight() - 80}, (Vector2){0, 0}, 0.0f, Fade(WHITE, alpha));
    // Desenha botoes
    DrawButton(startButton, 5, RED, 8, BLACK);
    DrawButton(howToPLayButton, 5, RED, 8, BLACK);
    DrawButton(creditsButton, 5, RED, 8, BLACK);
    DrawButton(exitButton, 5, RED, 8, BLACK);
    if (CheckCollisionPointRec(GetMousePosition(), startButton.rect))
    {
        DrawButton(startButton, 5, MAROON, 8, BLACK);
    }
    if (CheckCollisionPointRec(GetMousePosition(), howToPLayButton.rect))
    {
        DrawButton(howToPLayButton, 5, MAROON, 8, BLACK);
    }
    if (CheckCollisionPointRec(GetMousePosition(), creditsButton.rect))
    {
        DrawButton(creditsButton, 5, MAROON, 8, BLACK);
    }
    if (CheckCollisionPointRec(GetMousePosition(), exitButton.rect))
    {
        DrawButton(exitButton, 5, MAROON, 8, BLACK);
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
    DrawTexturePro(texture, (Rectangle){0, 0, texture.width, texture.height}, (Rectangle){40, 40, GetScreenWidth() - 80, GetScreenHeight() - 80}, (Vector2){0, 0}, 0.0f, Fade(WHITE, alpha));
}

void ShowHowToPlay(int screenWidth, int screenHeight, Texture2D textureHowToPlay, Button backButton)
{
    static float alpha = 1.0f;
    DrawTexturePro(textureHowToPlay, (Rectangle){0, 0, textureHowToPlay.width, textureHowToPlay.height}, (Rectangle){40, 40, GetScreenWidth() - 80, GetScreenHeight() - 80}, (Vector2){0, 0}, 0.0f, Fade(WHITE, alpha));
    DrawButton(backButton, 5, RED, 8, BLACK);
    if (CheckCollisionPointRec(GetMousePosition(), backButton.rect))
    {

        DrawButton(backButton, 5, MAROON, 8, BLACK);
    }
}

void ShowCredits(int screenWidth, int screenHeight, Texture2D textureCredits, Button backButton)
{
    static float alpha = 1.0f;
    DrawTexturePro(textureCredits, (Rectangle){0, 0, textureCredits.width, textureCredits.height}, (Rectangle){40, 40, GetScreenWidth() - 80, GetScreenHeight() - 80}, (Vector2){0, 0}, 0.0f, Fade(WHITE, alpha));
    DrawButton(backButton, 5, RED, 8, BLACK);
    if (CheckCollisionPointRec(GetMousePosition(), backButton.rect))
    {

        DrawButton(backButton, 5, MAROON, 8, BLACK);
    }
}

void ShowWin(int screenWidth, int screenHeight, Texture2D textureWin, Button backButtonWin, Button exitButtonWin, int tempominutosvitoria, int temposegundosvitoria)
{
    static float alpha = 0.0f;
    alpha += GetFrameTime() * 0.5f;
    if (alpha > 1.0f)
    {
        alpha = 1.0f;
    }
    DrawTexturePro(textureWin, (Rectangle){0, 0, textureWin.width, textureWin.height}, (Rectangle){40, 40, GetScreenWidth() - 80, GetScreenHeight() - 80}, (Vector2){0, 0}, 0.0f, Fade(WHITE, alpha));
    DrawText(TextFormat("E o seu tempo foi de: %d:%d", tempominutosvitoria, temposegundosvitoria), screenWidth/2-160, screenHeight/1.1,30,RED);
    DrawButton(backButtonWin, 5, RED, 8, BLACK);
    DrawButton(exitButtonWin, 5, RED, 8, BLACK);
    if (CheckCollisionPointRec(GetMousePosition(), backButtonWin.rect))
    {
        DrawButton(backButtonWin, 5, MAROON, 8, BLACK);
    }
    if (CheckCollisionPointRec(GetMousePosition(), exitButtonWin.rect))
    {
        DrawButton(exitButtonWin, 5, MAROON, 8, BLACK);
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
    DrawTexturePro(textureLose, (Rectangle){0, 0, textureLose.width, textureLose.height}, (Rectangle){40, 40, GetScreenWidth() - 80, GetScreenHeight() - 80}, (Vector2){0, 0}, 0.0f, Fade(WHITE, alpha));
    DrawButton(backButtonLose, 5, RED, 8, BLACK);
    DrawButton(exitButtonLose, 5, RED, 8, BLACK);
    if (CheckCollisionPointRec(GetMousePosition(), backButtonLose.rect))
    {
        DrawButton(backButtonLose, 5, MAROON, 8, BLACK);
    }
    if (CheckCollisionPointRec(GetMousePosition(), exitButtonLose.rect))
    {
        DrawButton(exitButtonLose, 5, MAROON, 8, BLACK);
    }
}
