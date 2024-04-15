
#include <iostream>
#include <fstream>
//zadacha 2 playlist

// the construct will be the following: we have in an enum class the number of shifts needed to put the bit 1 on the correct position
// in the genre.type we will not save a correct symbol, we will just add the bit 1 to the correct position
// example: 0000 0001 = Rock  -> we did 0 shifts
// example: 0000 0010 = Pop -> we did 1 shift
// example: 0000 0011 = Pop&Rock

//all functionalities mentioned in the task are made, but they might not be in order
void strcopy(char* dest, const char* source) {
    if(dest == nullptr || source == nullptr)return;
    while (*source) {
        (*dest) = (*source);
        dest++;
        source++;
    }
    (*dest) = '\0';
}
int strleng(const char* str) {
    if (!str)return -1;
    int count = 0;
    while (*str) {
        str++;
        count++;
    }
    return count;
}
bool strcompare(const char* str1, const char* str2) {
    if (!str1 || !str2)return false;
    while ((*str1) && (*str2)) {
        if ((*str1) != (*str2))return false;
        str1++;
        str2++;
    }
    return (*str1) == (*str2);
}
int getFileSize(std::ifstream& ifs) {
    int currentPos = ifs.tellg();
    ifs.seekg(0, std::ios::end);
    int size = ifs.tellg();
    ifs.seekg(currentPos);
    return size;
}
constexpr size_t MAX_SONGS = 30;
constexpr size_t MAX_CONTENT = 256 + 1; // for the '\0' symbol at the end
const size_t MAX_BITS_CHAR = 8;
const int SECONDS_IN_MINUTE = 60;
const int SECONDS_IN_HOUR = 3600;
const char rock = 'r';
const char pop = 'p';
const char hip_hop = 'h';
const char electro = 'e';
const char jazz = 'j';
int getSeconds(int hours, int minutes, int seconds) {
    int result = seconds + SECONDS_IN_MINUTE * minutes + SECONDS_IN_HOUR * hours;
    return result;
}
void strconcat(char* str1, const char* str2) {
    if (!str1 || !str2)return;
    int len = strleng(str1);
    str1 += len;
    while (*str2) {
        (*str1) = (*str2);
        str1++;
        str2++;
    }
    (*str1) = '\0';
}
enum class GENRE_SHIFTS {
    ROCK = 0,
    POP = 1,
    HIP_HOP = 2,
    ELECTRO = 3,
    JAZZ = 4
};
struct Genre {
private:
    char type = '\0';
public:
    const char* getGenreType() const {
        char result[64] = { 0 };
        bool isComplex = false;
        for (int i = 1;i <= MAX_BITS_CHAR;i++) {
            int bit = 1;
            bit <<= (i - 1);
            int isGenre = type & bit;
            if (isGenre != 0) {
                if (isComplex)strconcat(result, "&");
                switch (i - 1) {
                case (int)GENRE_SHIFTS::ROCK: strconcat(result, "Rock");isComplex = true;break;
                case (int)GENRE_SHIFTS::POP: strconcat(result, "Pop");isComplex = true;break;
                case (int)GENRE_SHIFTS::HIP_HOP: strconcat(result, "Hip-Hop");isComplex = true;break;
                case (int)GENRE_SHIFTS::ELECTRO: strconcat(result, "Electro");isComplex = true;break;
                case (int)GENRE_SHIFTS::JAZZ: strconcat(result, "Jazz");isComplex = true;break;
                default:break;
                }
            }
        }
        return result;
    }
    char getGenreSymbol() const {
        return this->type;
    }
    void setGenreType(const char* type) {
        if (!type)return;
        this->type = '\0';
        while (*type) {
            int bit = 1;
            switch (*type) {
            case rock: bit <<= (int)GENRE_SHIFTS::ROCK; this->type |= bit;break;
            case pop: bit <<= (int)GENRE_SHIFTS::POP; this->type |= bit;break;
            case hip_hop: bit <<= (int)GENRE_SHIFTS::HIP_HOP; this->type |= bit;break;
            case electro: bit <<= (int)GENRE_SHIFTS::ELECTRO; this->type |= bit;break;
            case jazz: bit <<= (int)GENRE_SHIFTS::JAZZ; this->type |= bit;break;
            default:break;
            }
            type++;
        }
    }
};
struct Song {
private:
    char name[64] = { 0 };
    int duration = 0;
    char fileName[64] = { 0 };
    char content[MAX_CONTENT] = { 0 };
    void readFromBinary(const char* fileName);
    void writeToBinary(const char* fileName) const;
    void convertBits(int& passedBits, int k, int index);
public:
    Genre genre;
    Song() = default;
    Song(const char* name, int duration, const char* fileName, const char* genre) {
        if (!name || !fileName || !genre) {
            std::cout << "Nullptr detected!";
            return;
        }
        strcopy(this->name, name);
        this->duration = duration;
        strcopy(this->fileName, fileName);
        //for the content
        readFromBinary(fileName);
        this->genre.setGenreType(genre);
    }
    const char* getName() const {
        return this->name;
    }
    const char* getFileName() const {
        return this->fileName;
    }
    const char* getContent() const {
        return this->content;
    }
    int getDurationInSeconds() const {
        return this->duration;
    }
    void setName(const char* name) {
        if (!name)return;
        strcopy(this->name, name);
    }
    void setDuration(int seconds) {
        if (seconds <= 0)return;
        this->duration = seconds;
    }
    void setFileName(const char* fileName) {
        if (!fileName)return;
        if (!fileName)return;
        strcopy(this->fileName, fileName);
    }
    // if the file with the content doesnt exist
    void setContent(const char* content, const char* fileName) {
        if (!content) return;
        strcopy(this->content, content);
        writeToBinary(fileName);
    }
    void printDuration() const {
        std::cout << duration / SECONDS_IN_HOUR << ":";
        std::cout << duration / SECONDS_IN_MINUTE % SECONDS_IN_MINUTE << ":";
        std::cout << duration % SECONDS_IN_MINUTE;
    }
    void readContent(const char* fileName) {
        if (!fileName)return;
        readFromBinary(fileName);
    }
    void writeContent(const char* fileName) const {
        if (!fileName)return;
        writeToBinary(fileName);
    }
    //if the file with the content doesnt already exist
    void convertKToBit(int k);
    void print() const;
};
void Song::convertBits(int& passedBits, int k, int index) {
    int bit = 1;
    for (int j = 1;j <= MAX_BITS_CHAR;j++, passedBits++) {
        if (passedBits % k == 0) {
            bit <<= (j - 1);
            content[index] |= bit;
            bit = 1;
        }
    }
}
void Song::convertKToBit(int k) {
    int size = strleng(content);
    int passedBits = 1;
    for (int i = size - 1;i >= 0;i--) {
        convertBits(passedBits, k, i);
    }
}
void Song::readFromBinary(const char* fileName) {
    std::ifstream ifs(fileName, std::ios::in | std::ios::binary);
    if (!ifs.is_open()) {
        std::cout << "Cannot open file for reading!";
        return;
    }
    ifs.read((char*)content, getFileSize(ifs));
    setFileName(fileName);
    ifs.clear();
    ifs.close();
}
void Song::writeToBinary(const char* fileName) const{
    std::ofstream ofs(fileName, std::ios::out | std::ios::binary);
    if (!ofs.is_open()) {
        std::cout << "Cannot open file for writing!";
    }
    ofs.write((const char*)content, strleng(content));
    ofs.clear();
    ofs.close();
}
void Song::print() const {
    std::cout << name << ' ';
    printDuration();
    std::cout << ' ';
    char genreType[MAX_CONTENT];
    strcopy(genreType, genre.getGenreType());
    std::cout << genreType<<std::endl;
}
struct Playlist {
private:
    void mixContents(char* content1, const char* content2);
    void swapSongs(Song& song1, Song& song2);
    int findSongIndex(const char* songName) const;
public:
    Song songs[MAX_SONGS];
    size_t songsCount = 0;
    // we will have functions with the same name but different parameters
    // the second one is the one that was stated in the functionalities part of the task
    void mixSongs(Song& song1, const Song& song2);
    void mixSongs(const char* song1, const char* song2);
    //other functionalities
    void add(const char* songName, int hours, int minutes, int seconds, const char* genreType, const char* fileName);
    void printPlaylist() const;
    void searchSongByName(const char* songName) const;
    void searchSongsByGenre(char genreType) const;
    //high-order function so we can make it as abstract as possible and make it cover different scenarios
    void sort(bool(*pred)(const Song&, const Song&));
    //criterias will be defined before the implementation of sort
    void convertKToBit(const char* songName, int k);
    void saveToBinary(const char* songName, const char* fileName) const;
};

void Playlist::mixContents(char* content1, const char* content2) {
    while ((*content1) && (*content2)) {
        (*content1) ^= (*content2);
        content1++;
        content2++;
    }
}
void Playlist::mixSongs(Song& song1, const Song& song2) {
    char song1Content[MAX_CONTENT];
    strcopy(song1Content, song1.getContent());
    char song2Content[MAX_CONTENT];
    strcopy(song2Content, song2.getContent());
    mixContents(song1Content, song2Content);
    song1.setContent(song1Content, song1.getFileName());
}
int Playlist::findSongIndex(const char* songName) const {
    for (int i = 0;i < songsCount;i++) {
        if (strcompare(songs[i].getName(), songName)) {
            return i;
        }
    }
    return MAX_SONGS + 1;
}
void Playlist::mixSongs(const char* song1, const char* song2) {
    if (!song1 || !song2) {
        return;
    }
    int index1, index2;
    index1 = findSongIndex(song1);
    index2 = findSongIndex(song2);
    if (index1 >= MAX_SONGS || index2 >= MAX_SONGS) {
        std::cout << "One of the songs doesnt exist!";
        return;
    }
    mixSongs(songs[index1], songs[index2]);
}
void Playlist::add(const char* songName, int hours, int minutes, int seconds, const char* genreType, const char* fileName) {
    Song song(songName, getSeconds(hours, minutes, seconds), fileName, genreType);
    song.readContent(fileName);
    songs[songsCount++] = song;
}
void Playlist::searchSongByName(const char* songName) const{
    for (int i = 0;i < songsCount;i++) {
        if (strcompare(songs[i].getName(), songName)) {
            songs[i].print();
            return;
        }
    }
    std::cout << "Could not find the song you are lookin for!";
}
void Playlist::searchSongsByGenre(char genre) const {
    int bit = 1;
    switch (genre) {
    case rock: bit <<= (int)GENRE_SHIFTS::ROCK;break;
    case pop: bit <<= (int)GENRE_SHIFTS::POP;break;
    case hip_hop: bit <<= (int)GENRE_SHIFTS::HIP_HOP;break;
    case electro: bit <<= (int)GENRE_SHIFTS::ELECTRO;break;
    case jazz: bit <<= (int)GENRE_SHIFTS::JAZZ;break;
    default:std::cout << "Genre Not Available! \n";return;
    }
    for (int i = 0;i < songsCount;i++) {
        if ((songs[i].genre.getGenreSymbol() & bit) != 0) {
            songs[i].print();
        }
    }
}
void Playlist::swapSongs(Song& song1, Song& song2) {
    Song temp = song1;
    song1 = song2;
    song2 = temp;
}
//criteria functions
bool durationCriteria(const Song& song1, const Song& song2) {
    return song1.getDurationInSeconds() < song2.getDurationInSeconds();
}
bool compareNames(const char* name1, const char* name2) {
    if (!name1 || !name2)return false;
    while ((*name1) && (*name2)) {
        if ((*name1) < (*name2))return true;
        else if ((*name1) > (*name2)) return false;
        name1++;
        name2++;
    }
    return (*name1) < (*name2);
}
bool nameCriteria(const Song& song1, const Song& song2) {
    char song1Name[MAX_CONTENT];
    strcopy(song1Name, song1.getName());
    char song2Name[MAX_CONTENT];
    strcopy(song2Name, song2.getName());
    return compareNames(song1Name, song2Name);
}
//no more criteria functions
//now the high-order function implementation
void Playlist::sort(bool(*pred)(const Song&, const Song&)) {
    //selection sort in order to make the lowest amount of swaps between structures
    for (int i = 0; i < songsCount - 1; i++)
    {
        int minElementIndex = i;
        for (int j = i + 1; j < songsCount; j++)
        {
            if (pred(songs[j], songs[minElementIndex]))
                minElementIndex = j;
        }
        if (minElementIndex != i)
            swapSongs(songs[i], songs[minElementIndex]);
    }
}
void Playlist::printPlaylist() const {
    for (int i = 0;i < songsCount;i++) {
        songs[i].print();
    }
}
void Playlist::convertKToBit(const char* songName, int k) {
    if (!songName)return;
    int index = findSongIndex(songName);
    if (index >= MAX_SONGS) {
        std::cout << "Song with such name doesnt exist!";
        return;
    }
    songs[index].convertKToBit(k);
}
void Playlist::saveToBinary(const char* songName, const char* fileName) const {
    if (!songName || !fileName)return;
    int index = findSongIndex(songName);
    if (index >= MAX_SONGS) {
        std::cout << "Song with such name doesnt exist!";
        return;
    }
    songs[index].writeContent(fileName);
}
int main()
{
    Playlist p;
    //you can use this if you want
    p.songs[0].setContent("AV", "song1.dat");
    p.add("Song1", 0, 1, 55, "rp", "song1.dat");
    p.songs[1].setContent("BYU", "song2.dat");
    p.add("Song2", 0, 2, 10, "ej", "song2.dat");
    p.songs[2].setContent("KASKA", "song3.dat");
    p.add("Song3", 0, 6, 33, "jre", "song3.dat");
    p.songs[3].setContent("lfai", "song4.dat");
    p.add("Song4", 0, 3, 127, "p", "song4.dat");
    p.songs[4].setContent("moad", "song5.dat");
    p.add("Song5", 0, 4, 56, "jp", "song5.dat");
    p.printPlaylist();
}