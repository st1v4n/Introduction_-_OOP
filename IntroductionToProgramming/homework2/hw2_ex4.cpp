/**
*
Find largest sorted(Upwards) path in an dynamic matrix - recursive solution
*
*/

#include <iostream>
int count = 1;
int maxCount = -1;
void inputRow(int* matrix,int m) {
    if (!matrix)return;
    for (int i = 1;i <= m;i++) {
        std::cin >> matrix[i];
    }
}
int** generateMatrix(size_t rows) {
    int** matrix = new int* [rows];
    for (int row = 0;row < rows;row++) {
        int m;
        std::cin >> m;
        if (m < 1)return nullptr;
        matrix[row] = new int[m+1];
        matrix[row][0] = m;
        inputRow(matrix[row],m);
        if (!matrix[row])return nullptr;
    }
    return matrix;
}
bool isValidElement(int** matrix, size_t rows, int row, int col) {
    if ((row < 0 || row >= rows)) {
        return false;
    }
    if ((col<=0 || col > matrix[row][0])) {
        return false;
    }
    return true;
}
void findBiggerNeighbour(int** matrix, size_t rows, int row, int col,int moveRow,int moveCol) {
    // we see this as a 9 cell square and we move at each of its cells to check if they are valid and if they are bigger(we start at the central cell)
    if (!isValidElement(matrix,rows,row+moveRow,col+moveCol))return;
    count++;
    if (matrix[row][col] >= matrix[row + moveRow][col + moveCol]) {
        count--;
        return;
    }
    row += moveRow;
    col += moveCol;
    if (count > maxCount) {
        maxCount = count;
    }
    findBiggerNeighbour(matrix, rows, row, col, -1, -1);
    findBiggerNeighbour(matrix, rows, row, col , -1, 0);
    findBiggerNeighbour(matrix, rows, row, col, -1, 1);
    findBiggerNeighbour(matrix, rows, row, col, 0, 1);
    findBiggerNeighbour(matrix, rows, row, col, 1, 1);
    findBiggerNeighbour(matrix, rows, row, col, 1, 0);
    findBiggerNeighbour(matrix, rows, row, col, 1, -1);
    findBiggerNeighbour(matrix, rows, row, col, 0, -1);
    count--;
}
void countOfLargestNeighbourSpree(int** matrix, size_t rows) {
    if (!matrix)return;
    for (int i = 0;i < rows;i++) {
        int getCols = matrix[i][0];
        for (int j = 1;j <= getCols;j++) {
            // we are going to check every neighbour that the current element has, and we have a function that checks if it is a valid element
            findBiggerNeighbour(matrix, rows, i, j, -1, -1);
            findBiggerNeighbour(matrix, rows, i, j, -1, 0);
            findBiggerNeighbour(matrix, rows, i, j, -1, 1);
            findBiggerNeighbour(matrix, rows, i, j, 0, 1);
            findBiggerNeighbour(matrix, rows, i, j, 1, 1);
            findBiggerNeighbour(matrix, rows, i, j, 1, 0);
            findBiggerNeighbour(matrix, rows, i, j, 1, -1);
            findBiggerNeighbour(matrix, rows, i, j, 0, -1);
        }
    }
}
void deleteMatrixMemory(int** matrix, size_t rows) {
    for (int row = 0;row < rows;row++) {
        delete[] matrix[row];
    }
    delete[] matrix;
}
int main()
{
    int n;
    std::cin >> n;
    if (n < 1) {
        std::cout << "Incorrect input";
        return -1;
    }
    int** matrix = generateMatrix(n);
    if (!matrix) {
        std::cout << "Incorrect input";
        return -1;
    }
    countOfLargestNeighbourSpree(matrix, n);
    if (maxCount == -1) {
        std::cout << "Incorrect input";
        return -1;
    }
    else {
        std::cout << maxCount;
    }
    deleteMatrixMemory(matrix, n);
}


