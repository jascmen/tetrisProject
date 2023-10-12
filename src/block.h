#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

class Block
{

public: //constructor
    Block();
    void Draw(int offsetX, int offsetY);
    void Move(int rows, int columns);
    std::vector<Position> GetCellPosition();
    void Rotate();
    void UndoRotation();
    int id;
    std::map<int, std::vector<Position>> cells; //mapa de vectores de posiciones
private:
    int cellSize;
    int rotationState;
    std::vector<Color> colors;
    int rowOffset; //desplazamiento de fila -- abajo
    int columnOffset; //desplazamiento de columna-- izquierda y derecha
};
 
