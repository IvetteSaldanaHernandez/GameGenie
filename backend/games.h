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

class HashMap
{
private:
    int entries = 0;
    int tablesize = 0;
    const float loadfactor = 0.5;
    struct HashValue
    {
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
    void insert(string key, const Data &games);
    void load(vector<Data> &games);
    vector<Data> sortbyrating();
    vector<Data> sortbygenre(string genre);
    vector<Data> sortbyplatform(string platform);
};

class Heap
{
private:
    vector<Data> games;
    struct CompareRating
    {
        bool ascending; // true for asc, false for desc
        CompareRating(bool ascending) : ascending(ascending) {}
        bool operator()(const Data &a, const Data &b) const
        {
            // min heap for asc, max heap for desc
            return ascending ? (a.rating > b.rating) : (a.rating < b.rating);
        }
    };
    struct CompareTitle
    {
        bool ascending;
        CompareTitle(bool ascending) : ascending(ascending) {}
        bool operator()(const Data &a, const Data &b) const
        {
            return ascending ? (a.title > b.title) : (a.title < b.title);
        }
    };
    vector<Data> sortGames(const vector<Data> &filtered, bool ascending, bool byRating);

public:
    Heap();
    void insert(const Data &game);
    void load(const vector<Data> &games);
    vector<Data> sortbyrating(bool ascending = false); // default desc
    vector<Data> sortbytitle(bool ascending = true);   // default asc
    vector<Data> sortbygenre(const string &genre, bool ascending = false, bool byRating = true);
    vector<Data> sortbyplatform(const string &platform, bool ascending = false, bool byRating = true);
};

#endif // GAMEGENIE_GAMES_H
