#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

double lastUpdateTime = 0.0; //ultima vez que se actualizo el juego

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    double timeSinceLastUpdate = currentTime - lastUpdateTime; 
    if(timeSinceLastUpdate >= interval) //si el tiempo transcurrido es mayor o igual al intervalo
    {
        lastUpdateTime = currentTime; //la ultima vez que se actualizo el juego es igual al tiempo actual
        return true;
    }
    return false;
}

void DrawControls(Font font, Texture2D background)
{
    DrawTexture(background, 0, 0, WHITE);

    DrawTextEx(font, "TETRISUTEPINO", { 50, 100 }, 58, 6, WHITE);
    DrawTextEx(font, "Controles:", { 50, 200 }, 38, 2, WHITE);
    DrawTextEx(font, " ←: Mover izquierda", { 50, 250 }, 38, 2, WHITE);
    DrawTextEx(font, " →: Mover derecha", { 50, 300 }, 38, 2, WHITE);
    DrawTextEx(font, " ↓: Mover abajo", { 50, 350 }, 38, 2, WHITE);
    DrawTextEx(font, " ↑: Rotar bloque", { 50, 400 }, 38, 2, WHITE);
    DrawTextEx(font, " P: Pausar juego", { 50, 450 }, 38, 2, WHITE);
    DrawTextEx(font, "Esc: Cerrar juego", { 50, 500 }, 38, 2, WHITE);
}

int main()
{
    const int screenWidth = 580; //500
    const int screenHeight = 620;

    InitWindow(screenWidth, screenHeight, "raylib Tetris");
    SetTargetFPS(60); //establece la velocidad de fotogramas

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Texture2D background = LoadTexture("Images/fondo.png");

    Game game = Game();

    bool gameStarted = false;

    while (!WindowShouldClose()) //comprueba si se ha pulsado la tecla de ESC o el icono cerrar ventana
    {
        UpdateMusicStream(game.music);
        game.HandeleInput();

        if (!gameStarted)
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                gameStarted = true;
            }
        }
        else if (!game.pause)
        {
            if (EventTriggered(0.2)) //si el evento se activa cada 0.2 segundos
            {
                game.MoveBlockDown();
            }
        }

        BeginDrawing(); //crea lienzo en blanco donde podemos dibujar objetos
        ClearBackground(darkBlue);

        if (!gameStarted)
        {
            DrawControls(font, background);
            DrawTextEx(font, "Presiona Enter para jugar", { 50, 550 }, 38, 2, WHITE);
        }
        else
        {
            DrawTextEx(font, "Puntuacion", { 365, 15 }, 38, 2, WHITE);
            DrawTextEx(font, "Siguiente", { 370, 175 }, 38, 2, WHITE);

            if (game.gameOver)
            {
                DrawTextEx(font, "MORISTE PIPIPIPIPI", { 320, 450 }, 38, 2, WHITE);
            }

            DrawRectangleRounded({ 320, 55, 250, 60 }, 0.3, 6, lightBlue);

            if (game.pause)
            {
                DrawTextEx(font, "PAUSA", { 350, 450 }, 38, 2, WHITE);
            }

            char scoreText[10];
            sprintf(scoreText, "%d", game.score);
            Vector2 scoreTextSize = MeasureTextEx(font, scoreText, 38, 2);

            DrawTextEx(font, scoreText, { 320 + (250 - scoreTextSize.x) / 2, 65 }, 38, 2, WHITE);
            DrawRectangleRounded({ 320, 215, 250, 180 }, 0.3, 6, lightBlue);

            game.Draw();
        }

        EndDrawing(); //finaliza el lienzo
    }

    CloseWindow();
}