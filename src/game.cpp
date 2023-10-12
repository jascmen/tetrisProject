#include "game.h"
#include <random>

#include <raylib.h>

Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks(); //vector de bloques
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    InitAudioDevice();//inicializa el audio
    music = LoadMusicStream("Sounds/music.mp3");//carga la musica
    death = LoadSound("Sounds/mataron.mp3");//carga la musica
    PlayMusicStream(music);//reproduce la musica
    rotateSound = LoadSound("Sounds/rotate.mp3");
    clearSound = LoadSound("Sounds/clear.mp3");
}

Game::~Game()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);//descarga la musica
    CloseAudioDevice();//cierra el audio
}

Block Game::GetRandomBlock() //devuelve un bloque aleatorio
{
    if(blocks.empty()){
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size(); //genera un numero aleatorio entre 0 y el tamaño del vector de bloques
    Block block = blocks[randomIndex]; //obtiene el bloque aleatorio
    blocks.erase(blocks.begin() + randomIndex); //elimina el bloque del vector
    return block;
}

std::vector<Block> Game :: GetAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw(11,11);
    switch(nextBlock.id){
        case 3:
            nextBlock.Draw(290, 310);
            break;
        case 4:
            nextBlock.Draw(290, 270);
            break;
        default:
            nextBlock.Draw(310, 280);
            break;
    }
   
}

// void Game::HandeleInput()
// {
//     int keyPressed = GetKeyPressed(); //obtiene la tecla presionada
//     if(gameOver && keyPressed != 0){
//         gameOver = false;
//         Reset();      
//     }
//     switch (keyPressed)
//     {
//         case KEY_LEFT:
//             MoveBlockLeft();
//             break;
//         case KEY_RIGHT:
//             MoveBlockRight();
//             break;
//         case KEY_DOWN:
//             MoveBlockDown();
//             UpdateScore(0, 1);
//             break;
//         case KEY_UP:
//             RotateBlock();
//             break;
//     }
// }

void Game::HandeleInput()
{
    int keyPressed = GetKeyPressed(); // Obtiene la tecla presionada

    if (gameOver && keyPressed != 0)
    {
        gameOver = false;
        Reset();
    }

    static bool prevGamepadLeftState = false;
    static bool prevGamepadRightState = false;
    static bool prevGamepadDownState = false;
    static bool prevGamepadUpState = false;

    // Check for keyboard input
    switch (keyPressed)
    {
        case KEY_LEFT:
            MoveBlockLeft();
            break;
        case KEY_RIGHT:
            MoveBlockRight();
            break;
        case KEY_DOWN:
            MoveBlockDown();
            UpdateScore(0, 1);
            break;
        case KEY_UP:
            RotateBlock();
            break;
    }
    // Check for gamepad input
    if (IsGamepadAvailable(0))
    {
        bool currentGamepadLeftState = IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT);
        bool currentGamepadRightState = IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
        bool currentGamepadDownState = IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
        bool currentGamepadUpState = IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP);

        if (currentGamepadLeftState && !prevGamepadLeftState)
        {
            MoveBlockLeft();
        }
        else if (!currentGamepadLeftState && prevGamepadLeftState)
        {
            // Botón izquierdo del gamepad liberado
        }

        if (currentGamepadRightState && !prevGamepadRightState)
        {
            MoveBlockRight();
        }
        else if (!currentGamepadRightState && prevGamepadRightState)
        {
            // Botón derecho del gamepad liberado
        }

        if (currentGamepadDownState && !prevGamepadDownState)
        {
            MoveBlockDown();
            UpdateScore(0, 1);
        }
        else if (!currentGamepadDownState && prevGamepadDownState)
        {
            // Botón abajo del gamepad liberado
        }

        if (currentGamepadUpState && !prevGamepadUpState)
        {
            RotateBlock();
        }
        else if (!currentGamepadUpState && prevGamepadUpState)
        {
            // Botón arriba del gamepad liberado
        }

        // Actualiza el estado anterior del gamepad
        prevGamepadLeftState = currentGamepadLeftState;
        prevGamepadRightState = currentGamepadRightState;
        prevGamepadDownState = currentGamepadDownState;
        prevGamepadUpState = currentGamepadUpState;
    }
}



void Game::MoveBlockLeft() //mueve el bloque a la izquierda
{
    if(!gameOver){
        currentBlock.Move(0, -1);
        if(IsBlockOutside() || !BlockFits()){
            currentBlock.Move(0, 1); //si el bloque esta fuera de la cuadricula lo mueve a la derecha
        }
    }
}

void Game::MoveBlockRight() //mueve el bloque a la derecha
{
    if(!gameOver){
        currentBlock.Move(0, 1);
        if(IsBlockOutside() || !BlockFits()){
            currentBlock.Move(0, -1); //si el bloque esta fuera de la cuadricula lo mueve a la izquierda
        }
    }
}

void Game::MoveBlockDown() //mueve el bloque hacia abajo
{
    if(!gameOver){
        currentBlock.Move(1, 0);
        if(IsBlockOutside() || !BlockFits()){
            currentBlock.Move(-1, 0); //si el bloque esta fuera de la cuadricula lo mueve hacia arriba
            LockBlodk(); //bloquea el bloque
        }
    }
}

bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition(); //obtiene la posicion de la celda
    for(Position item : tiles){
        if(grid.isCellOutside(item.row, item.column)){ //verifica si la celda esta ocupada
            return true;
        }
    }
    return false;
}

void Game::RotateBlock()
{
    if(!gameOver){
        currentBlock.Rotate();
        if(IsBlockOutside() || !BlockFits()){
            currentBlock.UndoRotation(); //si el bloque esta fuera de la cuadricula deshace la rotacion
        }
        else{
            PlaySound(rotateSound);
        }
    }
    
}

void Game::LockBlodk()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition(); //obtiene la posicion de la celda
    for(Position item : tiles){
        grid.grid[item.row][item.column] = currentBlock.id; //bloquea el bloque
    }
    currentBlock = nextBlock; //el bloque actual es igual al siguiente bloque
    if(!BlockFits()){ //si el bloque no cabe en la cuadricula
        gameOver = true; //el juego termina
        PlaySound(death);//reproduce la musica 
    }
    nextBlock = GetRandomBlock(); //el siguiente bloque es igual a un bloque aleatorio
    int rowsCleared= grid.ClearFullRows(); //limpia las filas completas
    if(rowsCleared > 0){
        PlaySound(clearSound);//reproduce el sonido
        UpdateScore(rowsCleared, 0); //actualiza la puntuacion
    }
}

bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition(); //obtiene la posicion de la celda
    for(Position item : tiles){
        
        if(!grid.isCellEmpty(item.row, item.column)){ //verifica si la celda esta vacia
            return false;
        }
    }
    return true;
}

void Game::Reset()
{
    grid.Initialize();
    blocks = GetAllBlocks(); //vector de bloques
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

void Game::UpdateScore(int rowsCleared, int movedDownPoints)
{
    switch (rowsCleared)
    {
        case 1:
            score += 100;
            break;
        case 2:
            score += 300;
            break;
        case 3:
            score += 500;
            break;
        default:
        break;  
    }
    score += movedDownPoints;
}
