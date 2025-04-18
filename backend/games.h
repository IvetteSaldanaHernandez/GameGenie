#ifndef GAMEGENIE_GAMES_H
#define GAMEGENIE_GAMES_H
#include <string>
#include <vector>
using namespace std;
struct Data
{
    string title;
    string platform;
    vector<string> genre;
    float rating;
};

vector<Data> loadData(string &filename);
bool comparerating(Data &x, Data &y);

class HashMap{
private:
    int entries = 0;
    int tablesize = 0;
    const float loadfactor = 0.75;
    struct HashValue{
        string key;
        vector<Data> value;
        bool occupied = false;
    };
    vector<HashValue> games;
    int hash(string key);
    void resizetable(int size);

public:
    HashMap();
    HashMap(int size);
    void insert(string key, Data &games);
    void load(vector<Data> &games);
    vector<Data> sortbyrating();
    vector<Data> sortbygenre(string genre);
    vector<Data> sortbyplatform(string platform);
};
#endif //GAMEGENIE_GAMES_H
