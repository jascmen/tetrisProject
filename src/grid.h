#pragma once //garantiza que este heder file solo se incluya una vez en una compilacion
#include <vector>
#include <raylib.h>

class Grid{
    public: //contstructor
        Grid();
        void Initialize();
        void Print();
        void Draw();
        bool isCellOutside(int row, int column);
        bool isCellEmpty(int row, int column);
        int ClearFullRows();
        int grid[20][10];

private:
    bool IsRowFull(int row); //verifica si la fila esta llena
    void DeleteRow(int row); //elimina la fila
    void MoveRowDown(int row, int numRows); //mover la fila hacia abajo
    int numRows;
    int numCols;
    int cellSize;
    std::vector<Color> colors;
};