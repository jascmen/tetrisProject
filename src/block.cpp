#include "block.h"

Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    colors = getCellColors();
    rowOffset = 0;
    columnOffset = 0;
} 

void Block::Draw(int offsetX, int offsetY)
{
     std::vector<Position> tiles = GetCellPosition(); //obtiene la posicion de la celda
     for(Position item : tiles){
            int x = item.column * cellSize + offsetX; //posicion en x
            int y = item.row * cellSize + offsetY;  //posicion en y
            DrawRectangle(x, y, cellSize-1, cellSize-1, colors[id]); //dibuja el rectangulo
     }
}

void Block::Move(int rows, int columns)
{
    rowOffset += rows;
    columnOffset += columns;
}

std::vector<Position> Block::GetCellPosition() //obtiene la posicion de la celda
{
    std::vector<Position> tiles = cells[rotationState]; //obtiene el vector de posiciones de la rotacion actual
    std::vector<Position> movedTiles; //vector de posiciones movidas
    for(Position item : tiles){
        Position newPosition = Position(item.row + rowOffset, item.column + columnOffset); //nueva posicion
        movedTiles.push_back(newPosition);//agrega la nueva posicion al vector de posiciones movidas
    }
    return movedTiles;
}

void Block::Rotate()
{
    rotationState ++; //aumenta el estado de rotacion
    if(rotationState == (int) cells.size()){ //si el estado de rotacion es igual al tamaño del mapa de vectores de posiciones
        rotationState = 0; //el estado de rotacion es igual a 0
    }
}

void Block::UndoRotation()
{
    rotationState --; //disminuye el estado de rotacion
    if(rotationState < 0){ //si el estado de rotacion es menor a 0
        rotationState = cells.size() - 1; //el estado de rotacion es igual al tamaño del mapa de vectores de posiciones - 1
    }
}
