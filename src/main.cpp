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
int main()
{
    
    const int screenWidth = 580; //500
    const int screenHeight = 620;

    InitWindow(screenWidth, screenHeight, "raylib Tetris");
    SetTargetFPS(60); //establece la velocidad de fotogramas

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    Game game = Game();

   

    while (!WindowShouldClose()) //comprueba si se ha pulsado la tecla de ESC o el icono cerrar ventana
    {
        UpdateMusicStream(game.music);
        game.HandeleInput();
        if(EventTriggered(0.2)) //si el evento se activa cada 0.2 segundos
        {
            game.MoveBlockDown();
        }
        
        BeginDrawing(); //crea lienzo en blanco donde podemos dibujar objetos
        ClearBackground(darkBlue);
        DrawTextEx(font,"Puntuacion", {365,15},38,2,WHITE);
        DrawTextEx(font,"Siguiente", {370,175},38,2,WHITE);
        if(game.gameOver)
        {
            DrawTextEx(font,"KGASTE PAPU", {320,450},38,2,WHITE);
        }
        DrawRectangleRounded({320, 55, 250, 60}, 0.3, 6, lightBlue);

        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 scoreTextSize = MeasureTextEx(font, scoreText, 38, 2);


        DrawTextEx(font,scoreText, {320+(250-scoreTextSize.x)/2,65},38,2,WHITE);
        DrawRectangleRounded({320, 215, 250, 180}, 0.3, 6, lightBlue);

        game.Draw();
        EndDrawing(); //finaliza el lienzo
    }

    CloseWindow();

}