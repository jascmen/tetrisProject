#pragma once
#include "grid.h"
#include "blockes.cpp"

class Game
{
    public:
        Game ();
        ~Game();
        void Draw();
        void HandeleInput();
         void MoveBlockDown();
         bool gameOver;
        int score;
        Music music;
        
        

     private:
         void MoveBlockLeft();
         void MoveBlockRight();
        Block GetRandomBlock();
        std::vector<Block> GetAllBlocks();
        bool IsBlockOutside();
        void RotateBlock();
        void LockBlodk(); //bloquea el bloque
        bool BlockFits(); //verifica si el bloque cabe
        void Reset();
        void UpdateScore(int rowsCleared, int movedDownPoints);
         Grid grid;
        std::vector<Block> blocks; // vector de bloques
        Block currentBlock;
        Block nextBlock;
        Sound rotateSound;
        Sound clearSound;
        Sound death;
};