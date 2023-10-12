#include "grid.h"
#include <iostream>
#include "colors.h"

Grid::Grid()
{
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    Initialize();
    colors = getCellColors();

}

void Grid::Initialize()
{
    //matriz de cuadricula
    for(int row = 0; row < numRows; row++)
    {
        for(int column = 0; column < numCols; column++)
        {
            grid[row][column] = 0;
        }
    }
}

void Grid::Print()
{
    for(int row = 0; row < numRows; row++)
    {
        for(int column = 0; column < numCols; column++)
        {
            std::cout << grid[row][column] << " ";
        }
        std::cout << std::endl;
    }
}


void Grid::Draw()
{
    for(int row = 0; row < numRows; row++)
    {
        for(int column = 0; column < numCols; column++)
        {
            int cellValue = grid[row][column]; //obtiene el valor de la celda
            
                Color cellColor = colors[cellValue];
                int x = column * cellSize + 11; //posicion en x
                int y = row * cellSize + 11; //posicion en y
                DrawRectangle(x, y, cellSize-1, cellSize-1, cellColor); //dibuja el rectangulo
            
        }
    }
}



bool Grid::isCellOutside(int row, int column) //verifica si la celda esta ocupada
{
    if(row>=0 && row<numRows && column>=0 && column<numCols) //si la fila y columna estan dentro de los limites
    {
        return false;
    }
    return true;
}

bool Grid::isCellEmpty(int row, int column)
{
    if(grid[row][column] == 0) //si la celda esta vacia
    {
        return true;
    }
    return false;
}

int Grid::ClearFullRows()
{
    int completedRows = 0;
    for(int row = numRows - 1; row >=0; row--) //recorre las filas de abajo hacia arriba
    {
        if(IsRowFull(row)) //si la fila esta llena
        {
            DeleteRow(row); //elimina la fila
            completedRows++; //aumenta el numero de filas completadas
        }
        else if (completedRows > 0) //si la fila no esta llena y hay filas completadas
        {
            MoveRowDown(row, completedRows); //mueve la fila hacia abajo
        }     
    }
    return completedRows;
}

bool Grid::IsRowFull(int row)
{
    for(int column = 0; column < numCols; column++)
    {
        if(grid[row][column] == 0) //si la celda esta vacia
        {
            return false;
        }
    }
    return true;
}

void Grid::DeleteRow(int row)
{
    for(int column=0; column < numCols; column ++)
    {
        grid[row][column] = 0;
    }
}

void Grid::MoveRowDown(int row, int numRows)
{
    for(int column = 0; column < numCols; column++)
    {
        grid[row+numRows][column] = grid[row][column]; //mueve la fila hacia abajo
        grid[row][column] = 0; //elimina la fila
    }
}
