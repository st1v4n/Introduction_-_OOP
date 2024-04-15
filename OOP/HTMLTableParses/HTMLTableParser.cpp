
#include <iostream>
#include <sstream>
#include <fstream>
//creating a special namespace that we will include and use for this program - it contains the usable tags and commands we need to solve the problem
namespace HTML_SYMBOLS_AND_COMMANDS {
    const char BORDER_SYMBOL = '|';
    const char HEADING_SYMBOL = '*';
    char Heading[4] = "<th";
    char NormalCell[4] = "<td";
    char TableTag[7] = "<table";
    char RowTag[4] = "<tr";
    char PrintCommand[6] = "print";
    char addCommand[4] = "add";
    char removeCommand[7] = "remove";
    char editCommand[5] = "edit";
    char exitCommand[5] = "exit";
}

using namespace HTML_SYMBOLS_AND_COMMANDS;
constexpr size_t MAX_ROWS = 100 + 1; // we dont count the 0 row
constexpr size_t MAX_COLS = 15 + 1; // we dont count the 0 col
constexpr size_t MAX_TEXT = 50 + 1; // 50 characters + '\0';
int strleng(const char* str) {
    if (str == nullptr)return -1;
    int count = 0;
    while (*str) {
        count++;
        str++;
    }
    return count;
}
char* clearEmpty(char* str) {
    while ((*str) == ' ')str++;
    return str;
}
bool strcompare(char* str1, const char* str2) {
    if(str1 == nullptr || str2 == nullptr)return false;
    str1 = clearEmpty(str1);
    while ((*str1) && (*str2)) {
        if ((*str1) != (*str2))return false;
        str1++;
        str2++;
    }
    return(*str1) == (*str2);
}
void strconcat(char* str1, const char* str2) {
    if(str1 == nullptr || str2 == nullptr)return;
    str1 += strleng(str1);
    while (*str2) {
        (*str1) = (*str2);
        str2++;
        str1++;
    }
    (*str1) = '\0';
}
int stringToNumber(const char*& str) {
    if (str == nullptr)return -1;
    int number = 0;
    while (*str) {
        if ((*str) >= '0' && (*str) <= '9') {
            (number *= 10) += ((*str) - '0');
        }
        else {
            str--;
            return number;
        }
        str++;
    }
    return number;
}
char uncodeString(const char*& str) {
    if(str == nullptr)return 0;
    char number = stringToNumber(str);
    return number;
}
void strcopy(char* dest, const char* source) {
    if(dest == nullptr || source == nullptr)return;
    while (*source) {
        //this if statement is here to encode the character, because we support different codings
        if ((*source) == '&' && (*(source + 1)) && (*(source + 1)) == '#') {
            source += 2;
            (*dest) = uncodeString(source);
        }
        else (*dest) = (*source);
        dest++;
        source++;
    }
    (*dest) = '\0';
}
struct Column {
private:
    char text[MAX_TEXT] = {0};
    int length = 0;
    bool isHeading = false;
    bool isEmpty = true;
public:
    Column() = default;
    bool getHeadingFlag() const {
        return this->isHeading;
    }
    const char* getText() const {
        return this->text;
    }
    int getLength() const {
        return this->length;
    }
    char getFirstSymbol() const {
        return this->text[0];
    }
    bool isColumnEmpty() const {
        return this->isEmpty;
    }
    void setEmpty(bool isEmpty) {
        this->isEmpty = isEmpty;
    }
    void setLength(int length) {
        //we make the validation before calling this function
        this->length = length;
    }
    void setFirstSymbol(char symbol) {
        this->text[0] = symbol;
    }
    void setText(const char* text) {
        //we make the validation before calling this function
        strcopy(this->text, text);
        int len = strleng(this->text);
        if (len > MAX_TEXT)this->text[0] = '\0';
        else {
            setLength(len);
            this->isEmpty = false;
        }
    }
    void setHeadingFlag(bool isHeading) {
        this->isHeading = isHeading;
    }
 
};
struct Row {
    Column columns[MAX_COLS];
};
struct Table {
private:
    // i will declare and write the entire function only on the smallest functions
    void swapCols(Column& col1, Column& col2) {
        Column temp = col1;
        col1 = col2;
        col2 = temp;
    }
    void swapRows(Row& row1, Row& row2) {
        for (int j = 1;j <= colsCount;j++) {
            swapCols(row1.columns[j], row2.columns[j]);
        }
    }
    // a function used to shift the table by the add command
    void shiftTableUpwards(int row) {
        for (int i = rowsCount;i > row;i--) {
            swapRows(rows[i], rows[i - 1]);
        }
    }
    // this is used by the remove function to shift the table so the empty row comes to the bottom of the table
    void shiftTableDownwards(int row) {
        for (int i = row;i < rowsCount;i++) {
            swapRows(rows[i], rows[i + 1]);
        }
    }
    // these functions are big and are only declared here, we will implement them somewhere else
    int getMaxColumnSize(int col) const;
    void printSpace(int space) const;
    void printColumn(int row,int col) const;
public:
    int rowsCount = 0;
    int colsCount = 0;
    Row rows[MAX_ROWS];
    void removeRow(Row& row, int pos);
    void addRow(int row);
    void editColumn(int row, int col);
    void print() const;
    // added a command to help the user stop writing commands in the console and exit the program
    void exitTable(bool& isOver) const;
};
constexpr size_t MAX_BUFFER_SIZE = 128;
//counting the amount of collumns
int columnsCount = 0;
void generateCol(Table& table, char* buffer, std::stringstream& ss, int currRow) {
    ++columnsCount;
    if(columnsCount >= MAX_COLS)return;
    ss.getline(buffer, MAX_BUFFER_SIZE, '<');
    int bufferLeng = strleng(buffer);
    int columnTextLeng = bufferLeng + 1;
    table.rows[currRow].columns[columnsCount].setText(buffer);
}
void readRowFromFile(Table& table, std::stringstream& ss) {
    char buffer[MAX_BUFFER_SIZE];
    ss.getline(buffer, MAX_BUFFER_SIZE, '>');
    if (strcompare(buffer, RowTag)) {
        columnsCount = 0;
        table.rowsCount++;
        if (table.rowsCount >= MAX_ROWS)return;
    }
    else if (strcompare(buffer, Heading)) {
        int currRow = table.rowsCount;
        table.rows[currRow].columns[columnsCount + 1].setHeadingFlag(true);
        generateCol(table, buffer, ss, currRow);
    }
    else if (strcompare(buffer, NormalCell)) {
        int currRow = table.rowsCount;
        generateCol(table, buffer, ss, currRow);
    }
    else {
        return;
    }
    // checking the case when we have different commands on the same row
    if (ss.peek() != '\n') {
        ss.getline(buffer, MAX_BUFFER_SIZE, '>');
        if (ss.peek() != '\n') {
            readRowFromFile(table, ss);
        }
    }
}
void readTable(Table& table, std::ifstream& ifs) {
    char buff[20];
    // if we have some empty space before the first <....>
    while (ifs.peek() == ' ' || ifs.peek() == '\n') {
        ifs.ignore();
    }
    ifs.getline(buff, 20, '>');
    //checking for the <table tag. If we dont have it, we instantly stop the program
    if(!strcompare(buff, TableTag))return;
    while (!ifs.eof()) {
        char buffer[MAX_BUFFER_SIZE];
        ifs.getline(buffer, MAX_BUFFER_SIZE);
        //we want the '\n' because later on we will check whether we have a few commands on the same row and this symbol will help
        char newRow[2] = "\n";
        strconcat(buffer, newRow);
        std::stringstream ss(buffer);
        readRowFromFile(table, ss);
        if (columnsCount > table.colsCount && columnsCount < MAX_COLS) {
            table.colsCount = columnsCount;
        }
        //checking if either the rows count or the cols count is bigger than the max size stated in the task
        if (table.rowsCount >= MAX_ROWS || table.colsCount >= MAX_COLS)return;
    }
    ifs.clear();
    ifs.seekg(0, std::ios::beg);
}
int Table::getMaxColumnSize(int col) const{
    int max = 0;
    for (int i = 1;i <= rowsCount;i++) {
        bool isHeading = rows[i].columns[col].getHeadingFlag();
        //if it is a heading it will have 2 more symbols added to its length
        int len = rows[i].columns[col].getLength();
        if (len > max) {
            max = len;
        }
    }
    return max;
}
void Table::printSpace(int space) const{
    for (int i = 1;i <= space;i++) {
        std::cout << ' ';
    }
}
void Table::printColumn(int row, int col) const{
    std::cout << BORDER_SYMBOL;
    bool isHeading = rows[row].columns[col].getHeadingFlag();
    bool isEmpty = rows[row].columns[col].isColumnEmpty();
    if (isHeading == true && !isEmpty)std::cout << HEADING_SYMBOL;
    else {
        std::cout << ' ';
    }
    int maxLeng = getMaxColumnSize(col);
    if (!isEmpty) {
        std::cout << rows[row].columns[col].getText();
        // if it is a heading we will need to add the amount of symbols
        int len = rows[row].columns[col].getLength();
        int space = maxLeng - len;
        printSpace(space);
    }
    else {
        printSpace(maxLeng);
    }
    if (isHeading == true && !isEmpty)std::cout << HEADING_SYMBOL;
    else {
        std::cout << ' ';
    }
    std::cout << BORDER_SYMBOL;
}
void Table::print() const{
    for (int i = 1;i <= rowsCount;i++) {
        for (int j = 1;j <= colsCount;j++) {
            printColumn(i, j);
        }
        std::cout << std::endl;
    }
}
void writeTableToFile(const Table& table, std::ofstream& ofs) {
    ofs << TableTag << '>' << '\n';
    for (int i = 1;i <= table.rowsCount;i++) {
        ofs << " " << RowTag << '>' << '\n';
        for (int j = 1;j <= table.colsCount;j++) {
            if (!table.rows[i].columns[j].isColumnEmpty()) {
                if (table.rows[i].columns[j].getHeadingFlag()) {
                    ofs << "  " << Heading << '>' << table.rows[i].columns[j].getText() << "</th>" << '\n';
                }
                else {
                    ofs << "  " << NormalCell << '>' << table.rows[i].columns[j].getText() << "</td>" << '\n';
                }
            }
        }
        ofs << " </tr>" << '\n';
    }
    ofs << "</table>";
    ofs.clear();
    ofs.seekp(0);
}
void Table::editColumn(int row, int col) {
    char newValue[50];
    std::cin.getline(newValue, 50);
    int len = strleng(newValue) + 1;
    rows[row].columns[col].setText(newValue);
    rows[row].columns[col].setLength(len - 1);
}
void Table::removeRow(Row& row, int pos) {
    for (int j = 1;j <= colsCount;j++) {
        row.columns[j].setEmpty(true);
    }
    shiftTableDownwards(pos);
    rowsCount--;
}
void Table::addRow(int row) {
    rowsCount++;
    shiftTableUpwards(row);
    for (int i = 1;i <= colsCount;i++) {
        char newValue[50];
        std::cin >> newValue;
        int len = strleng(newValue) + 1;
        rows[row].columns[i].setText(newValue);
        rows[row].columns[i].setLength(len - 1);
    }
}
void Table::exitTable(bool& isOver) const{
    isOver = true;
}
constexpr size_t MAX_COMMAND_SIZE = 10;
void readCommand(Table& table, const char* path, bool& isOver) {
    char command[MAX_COMMAND_SIZE] = { 0 };
    std::cin >> command;
    if (strcompare(command, PrintCommand)) {
        table.print();
    }
    else if (strcompare(command, editCommand)) {
        int row, col;
        std::cin >> row >> col;
        if (row == 0 || row > table.rowsCount || col == 0 || col > table.colsCount) {
            std::cout << "Invalid row or col" << std::endl;
            return;
        }
        table.editColumn(row, col);
    }
    else if (strcompare(command, removeCommand)) {
        int row;
        std::cin >> row;
        if (row == 0 || row > table.rowsCount) {
            std::cout << "Invalid row" << std::endl;
            return;
        }
        table.removeRow(table.rows[row], row);
    }
    else if (strcompare(command, addCommand)) {
        int row;
        std::cin >> row;
        if (row == 0 || row > table.rowsCount + 1) {
            std::cout << "Invalid row" << std::endl;
            return;
        }
        table.addRow(row);
    }
    else if (strcompare(command, exitCommand)) {
        table.exitTable(isOver);
    }
    else {
        std::cout << "Invalid command!" << std::endl;
        return;
    }
}
int main()
{
    char path[MAX_BUFFER_SIZE];
    std::cout << "Enter path: ";
    std::cin >> path;
    if (path == nullptr)return -1;
    std::ifstream ifs(path, std::ios::in | std::ios::out);
    if (!ifs.is_open()) {
        std::cout << "File could not be loaded!";
        return -1001;
    }
    ifs.seekg(0);
    Table table;
    readTable(table, ifs);
    ifs.clear();
    ifs.close();
    //the task doesnt state when the program ends, but i will assume that it ends when we use the command print
    bool isOver = false;
    while (!isOver) {
        std::cout << "Enter command: ";
        readCommand(table, path, isOver);
    }
    std::ofstream ofs(path);
    if (!ofs.is_open()) {
        std::cout << "Cannot open the file for writing!";
        return -1001;
    }
    writeTableToFile(table, ofs);
}

