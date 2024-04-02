/**
*
* Solution to course project # 3
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Stivan Nikolaev Aleksandrov
* @idnumber 3MI0600301
* @compiler VC
*
* realisation of the game ,,Bricks Drop''
*
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
//that symbol will be to visualize the game field (it will form the border)
const char BorderSymbol = '@';
//the field x will be 10 + 2 at start, because we will include the border, that consists of 1 symbol on the left and 1 symbol on the right + '\0' at the end of every row
constexpr int FieldX = 12 + 3;
// the same reason for field y, but now 1 symbol on top and 1 symbol down
constexpr int FieldY = 12 + 2;
constexpr size_t MAX_STRING_SIZE = 128;
constexpr int minimumSymbols = 5;
char username[MAX_STRING_SIZE];
char password[MAX_STRING_SIZE];
int score = 0;
int maxScore = 0;
const char firstColorSymbol = 'A';
const char lastColorSymbol = 'Z';
char color = firstColorSymbol;
const int maxBlocksGeneratedInRow = FieldX / 2;
const int minBloCksGeneratedInRow = 2;
const int maxBlocksLength = 5;
const int minBlocksLength = 1;
const int maximumSpaceBetweenBlocks = 4;
const int minimumSpaceBetweenBlocks = 0;
const int pointsGain = 10;
int getRandomNumber(int intervalLen, int startPoint) {
    int randomNumber = rand() % intervalLen + startPoint;
    return randomNumber;
}
int convertCharToInt(char symbol) {
    return symbol - '0';
}
void generateGameField(char field[][FieldX], char emptySymbol) {
    for (int i = 0;i <= FieldX-2;i++) {
        field[0][i] = BorderSymbol;
    }
    for (int y = 1;y <= FieldY-2;y++) {
        for (int x = 0;x <= FieldX-2;x++) {
            if (x == 0 || x == FieldX - 2) {
                field[y][x] = BorderSymbol;
            }
            else {
                field[y][x] = emptySymbol;
            }
        }
    }
    for (int i = 0;i <= FieldX-2;i++) {
        field[FieldY-1][i] = BorderSymbol;
    }
    for (int j = 0;j < FieldY;j++) {
        field[j][FieldX - 1] = '\0';
    }
}
void printField(const char field[][FieldX]) {
    for (int y = 0;y < FieldY;y++) {
        for (int x = 0;x < FieldX-1;x++) {
            std::cout << field[y][x];
        }
        std::cout << std::endl;
    }
}
int StringLengthFunc(const char* str) {
    if (!str)return -1;
    int len = 0;
    while (*str) {
        str++;
        len++;
    }
    return len;
}
int convertToInt(const char* str) {
    if (!str)return -1;
    int result = 0;
    while (*str) {
        (result *= 10) += convertCharToInt(*str);
        str++;
    }
    return result;
}
void writeDataToFile(const char* username,const char* password, int score) {
    if (!username || !password) return;
    std::ofstream ofs("data.txt");
    if (!ofs.is_open()) {
        std::cout << "File could not be loaded!" << std::endl;
        std::cout << "You will play as guest (your score will not be counted towards any max scores)!";
        return;
    }
    ofs << score << "\n";
    ofs << username << "\n";
    ofs << password << "\n";
    ofs.clear();
    ofs.close();
}
bool compareStrings(const char* str1, const char* str2) {
    if (!str1 || !str2)return false;
    while (*str1 && *str2) {
        if ((*str1) != (*str2))return false;
        str1++;
        str2++;
    }
    return (*str1) == (*str2);
}
// no need to type username and password as parameters of the function because they are globally declared
void loginToAccount() {
    if (!username || !password) return;
    std::ifstream ifs("data.txt");
    if (!ifs.is_open()) {
        std::cout << "Unexpected Error! You will play as guest!";
    }
    char previousMaxScore[MAX_STRING_SIZE];
    char previousUsername[MAX_STRING_SIZE];
    char previousPassword[MAX_STRING_SIZE];
    ifs.getline(previousMaxScore, MAX_STRING_SIZE);
    ifs.getline(previousUsername, MAX_STRING_SIZE);
    ifs.getline(previousPassword, MAX_STRING_SIZE);
    maxScore = convertToInt(previousMaxScore);
    while (!compareStrings(username, previousUsername) || !compareStrings(password, previousPassword)) {
        std::cout << "Username or Password is invalid! Enter new ones: \n";
        std::cout << "Username: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;
    }
    ifs.clear();
    ifs.close();
}
// no need to type username and password as parameters of the function because they are globally declared
void enterAccountInfo() {
    if (!username || !password)return;
    std::cout << "Enter Username: ";
    std::cin >> username;
    while (StringLengthFunc(username) < minimumSymbols) {
        std::cout << "Your username is too short, enter new one: ";
        std::cin >> username;
    }
    std::cout << "Enter Password: ";
    std::cin >> password;
    while (StringLengthFunc(password) < minimumSymbols) {
        std::cout << "Your password is too short, enter new one: ";
        std::cin >> password;
    }
}
void changeColor() {
    color++;
    if (color > lastColorSymbol) {
        color = firstColorSymbol;      
    }
}
bool isValidCordinate(int row, int col) {
    return (row >= 1 && row < FieldY - 1) && (col >= 1 && col < FieldX - 2);
}
int getSpace(char field[][FieldX], int row, int col,char currentColor) {
    int count = 0;
    while (field[row][col] == ' ' && field[row-1][col]==currentColor) {
        count++;
        col++;
    }
    return count;
}
int getBlockLength(char field[][FieldX], int row, int col, char color) {
    if (color == ' ')return -1;
    int count = 0;
    for (int i = col;field[row][i]==color;i++) {
        count++;    
    }
    return count;
}
void swap(char& s1, char& s2) {
    char temp = s1;
    s1 = s2;
    s2 = temp;
}
bool isRowFull(char field[][FieldX], int row) {
    for (int i = 1;i <= FieldX - 3;i++) {
        if (field[row][i] == ' ')return false;
    }
    return true;
}
void putInSpace(char field[][FieldX],int blockLength,int row,int col) {
    for (int i = 1;i <= blockLength;i++) {
        swap(field[row][col + i - 1], field[row + 1][col + i - 1]);
    }
}
bool canBePutInSpace(char field[][FieldX],int blockLength, int row,int col) {
    return blockLength == getSpace(field, row, col,field[row-1][col]);
}
void dropBlockDown(char field[][FieldX],int blockLength, int row, int col) {
    if (isValidCordinate(row + 1, col) && (field[row + 1][col] == ' ') && canBePutInSpace(field, blockLength, row+1, col)) {
        putInSpace(field, blockLength, row, col);
        dropBlockDown(field, blockLength, row + 1, col);
    }
}
void checkFieldForDrops(char field[][FieldX],int currentTopRow) {
    for (int y = FieldY - 3;y >= currentTopRow - 1;y--) {
        for (int x = 1;x <= FieldX - 3;x++) {
            int blockLength = getBlockLength(field, y, x, field[y][x]);
            if (blockLength == -1)continue;
            dropBlockDown(field, blockLength, y, x);
            x += blockLength - 1;
        }
    }
}
void generateBlockAndSpace(char field[][FieldX], int row, int& startPointX) {
    changeColor();
    int blockLength = getRandomNumber(maxBlocksLength - minBlocksLength, minBlocksLength);
    int space = getRandomNumber(maximumSpaceBetweenBlocks - minimumSpaceBetweenBlocks, minimumSpaceBetweenBlocks);
    int limitBlock = startPointX + blockLength - 1;
    for (int i = startPointX, countNewLength = 1;i <= limitBlock;i++, startPointX++, countNewLength++) {
        if (i >= FieldX - 3) {
            blockLength = countNewLength-1;
            dropBlockDown(field, blockLength, row, startPointX - blockLength);
            return;
        }
        field[row][i] = color;
    }
    dropBlockDown(field, blockLength, row, startPointX - blockLength);
        int limitSpace = startPointX + space;
        for (int i = startPointX;i <= limitSpace;i++, startPointX++) {
            if (i >= FieldX - 3) {
                return;
            }
            field[row][i] = ' ';
        }
        //because we added 2 more position to startPointX 
        startPointX--;
        if (space > 0)startPointX--;
}
void generateSpaceAtRowStart(char field[][FieldX],int row, int& startPointX) {
    int spaceLength = getRandomNumber(maximumSpaceBetweenBlocks - minimumSpaceBetweenBlocks, minimumSpaceBetweenBlocks);
    int end = spaceLength + startPointX - 1;
    for (int i = startPointX;i <= end;i++, startPointX++) {
        field[row][i] = ' ';
    }
    if (spaceLength > 0)startPointX--;
}
void fillRowWithEmptySpace(char field[][FieldX], int row) {
    for (int x = 1;x < FieldX - 2;x++) {
        field[row][x] = ' ';
    }
}
void generateRow(char field[][FieldX], int row) {
    //lets say that the max blocks that can be generated will be maxBlocksGeneratedInRow
    int numberOfBlocks = getRandomNumber(maxBlocksGeneratedInRow - minBloCksGeneratedInRow, minBloCksGeneratedInRow);
    int count = 0;
    for (int x = 1;x < FieldX - 3;x++) {
        generateSpaceAtRowStart(field,row,x);
        //lets say that the max block length that can be generated will be maxBlocksLength
        generateBlockAndSpace(field, row, x);
        if (x >= FieldX - 3)return;
        count++;
        if (count >= numberOfBlocks)return;
    }
    if (isRowFull(field, row)) {
        score += pointsGain;
        fillRowWithEmptySpace(field,row);
        checkFieldForDrops(field, 1);
    }
}
void generateRandomBlocks(char field[][FieldX]) {
    // game starts with 1/3 of the field's rows covered with blocks
    int rows = FieldY / 3;
    int end = FieldY - 2 - rows + 1;
    for (int i = FieldY - 2;i >= end;i--) {
        generateRow(field, i);
    }
}
bool isGameOver(char field[][FieldX]) {
    for (int i = 1;i < FieldX - 2;i++) {
        if (field[1][i] != ' ')return true;
    }
    return false;
}
void moveBlockByOne(char field[][FieldX], int blockLength, int row, int col,int directionMove) {
    for (int i = 1;i <= blockLength;i++) {
        swap(field[row][col], field[row][col + directionMove]);
        col -= directionMove;
    }
}
void makeAMove(char field[][FieldX], int row, int col, char direction, int moves) {
    int directionMove=0;
    int blockLength = getBlockLength(field, row, col, field[row][col]);
    int countMoves = 0;
    switch (direction) {
    case 'r':
        directionMove = 1;
        col += blockLength - 1;
        break;
    case 'l':
        directionMove = -1;
        break;
    }
    while (field[row][col + directionMove] == ' ' && countMoves<moves) {
        moveBlockByOne(field, blockLength, row, col, directionMove);
        col += directionMove;
        countMoves++;
    }
}
void generateNewRow(char field[][FieldX],int currentTopRow) {
    for (int y = currentTopRow;y < FieldY-2;y++) {
        for (int x = 1;x < FieldX - 2;x++) {
            swap(field[y][x], field[y + 1][x]);
        }
    }
    generateRow(field, FieldY - 2);
}
int findTopEmptyRow(char field[][FieldX]) {
    for (int y = FieldY-2;y >=1;y--) {
        for (int x = 1;x < FieldX - 2;x++) {
            if (field[y][x] != ' ')break;
            if (x == FieldX - 3)return y;
        }
    }
    return -1;
}
void findFullRows(char field[][FieldX], int currentTopRow) {
    for (int y = currentTopRow;y < FieldY - 1;y++) {
        if (isRowFull(field, y)) {
            score += pointsGain;
            fillRowWithEmptySpace(field, y);
            checkFieldForDrops(field,currentTopRow);
        }
    }
}
void play(char field[][FieldX]) {
    generateRandomBlocks(field);
    while (!isGameOver(field)) {
        printField(field);
        int currentTopRow = findTopEmptyRow(field);
        std::cout << "Current score: " << score << std::endl;
        int command;
        std::cout << "What would you like to do now ?" << std::endl;
        std::cout << "Available options: \n 1:Exit \n 2:Movement command \n";
        std::cout << "Select an option: ";
        std::cin >> command;
        while (command < 1 || command>2) {
            std::cout << "Invalid Command! Enter new one: ";
            std::cin >> command;
        }
        switch (command) {
        case 1:
            if (score > maxScore) {
                writeDataToFile(username, password, score);
            }
            return;
            break;
        case 2:
            int x, y;
            char direction;
            int moves;
            std::cin >> y >> x;
            while ((x < 1 || x > FieldX - 3) || (y < 1 || y > FieldY - 2)) {
                std::cout << "Incorrect x or y! Enter new ones: ";
                std::cin >> y >> x;
            }
            std::cin >> direction;
            while (direction != 'r' && direction != 'l') {
                std::cout << "Incorrect direction! Enter new one: ";
                std::cin >> direction;
            }
            std::cin >> moves;
            while (moves<0 || moves > FieldX -3) {
                std::cout << "Incorrect input of moves! Enter new ones: ";
                std::cin >> moves;
            }
            makeAMove(field,y,x,direction,moves);
            checkFieldForDrops(field, currentTopRow);
            findFullRows(field, currentTopRow);
            break;
        default: std::cout << "ERROR";break;
        }
        generateNewRow(field, currentTopRow);
        checkFieldForDrops(field,currentTopRow+1);
        findFullRows(field, currentTopRow + 1);
    }
}
int main()
{
    char field[FieldY][FieldX];
    generateGameField(field, ' ');
    srand(time(NULL));
    std::cout << "Welcome to Bricks Drop!"<<std::endl;
    std::cout << "Enter the number of the command you want to execute: "<<std::endl;
    std::cout << "Currently available commands: " << std::endl;
    std::cout << "1: Create new profile (you can have maximum 1 profile)" << std::endl;
    std::cout << "2: Log in to an existing profile (up to 1 profile)" << std::endl;
    std::cout << "Your command: ";
    int command;
    do {
        std::cin >> command;
    } while (command < 1 || command > 2);
    switch (command) {
    case 1: 
        enterAccountInfo();
        writeDataToFile(username, password, score);
        break;
    case 2:
        enterAccountInfo();
        loginToAccount(); 
        break;
    default: std::cout << "ERROR!";break;
    }
    play(field);
    if (score > maxScore) {
        writeDataToFile(username, password, score);
    }
    std::cout << "Game over! Thanks for playing!" << std::endl;
    std::cout << "Your Points: " << score <<std::endl;
    std::cout << "Options: \n 1:End game \n 2:Start New game \n Your choice: ";
    do {
        std::cin >> command;
    } while (command < 1 || command > 2);
    switch (command) {
    case 1:return 1;break;
    case 2:main();break;
    default:std::cout << "ERROR";break;
    }
}


