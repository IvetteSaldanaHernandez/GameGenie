#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;
#include "games.h"
// function to load data from a JSON file, using nlohmann/json library
// reference: https://github.com/nlohmann/json?tab=readme-ov-file#read-json-from-a-file
vector<Data> loadData(string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        //error statement
        cerr << "Error opening file: " << filename << endl;
        return {};
    }
    json j;
    file >> j;
    vector<Data> dataList;
    for (const auto &item : j)
    {
        Data data;
        data.title = item["game"].get<string>();
        data.platform = item["platform"].get<string>();
        //changed genre to a vector since there can be multiple genres
        data.genre = item["genre"].get<vector<string>>();
        data.rating = item["rating"].get<double>();
        dataList.push_back(data);
    }
    return dataList;
}
//function used when sorting data in Hashmap
bool comparerating(Data &x, Data &y) {
    return x.rating > y.rating;
}
//check if number is prime for hash table
bool isprime(int n) {
    if (n <= 1){
        return false;
    }
    else{
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0){
                return false;
            }
        }
    }
    return true;
}
//find next prime number
int nextprime(int n) {
    while (!isprime(n)){
        n++;
    }
    return n;
}

int HashMap::hash(string key) {
    int val = 0;
    //calculate index of value
    //use 31 to spread out values to reduce collisions
    for (char c : key){
        val = (val * 31 + c) % tablesize;
    }
    return val;
}
//resize table when there are collisions
void HashMap::resizetable(int size) {
    //create a vector of original table
    vector<HashValue> oldgames = games;
    //increase table size to the next prime number
    tablesize = nextprime(size);
    //resize
    games.resize(tablesize);
    //reset entries
    entries = 0;

    //reinsert old entries
    for(int i = 0; i < oldgames.size(); i++){
        if(oldgames[i].occupied){
            for(int j = 0; j < oldgames[i].value.size(); j++){
                insert(oldgames[i].key, oldgames[i].value[j]);
            }
        }
    }
}
//default constructor
HashMap::HashMap(){
    resizetable(1031);
}
//parameterized constructor
HashMap::HashMap(int size) {
    resizetable(size);
}
void HashMap::insert(string key, const Data &data) {
    //if entries/buckets > loadfactor, resize
    if (static_cast<float>(entries)/tablesize >= loadfactor) {
        resizetable(tablesize * 2);
    }
    //calculated new index
    int index = hash(key);
    int i = 1;

    //if there are collisions
    while (games[index].occupied && games[index].key != key) {
        index = (hash(key) + i * i) % tablesize;
        i++;
    }

    //insert data
    if (!games[index].occupied) {
        games[index].key = key;
        games[index].value = {data};
        games[index].occupied = true;
        entries++;
    } else {
        //if title has already been inserted and there is more data
        games[index].value.push_back(data);
    }
}
//load data into HashMap
void HashMap::load(vector<Data> &mygame) {
    for(int i = 0; i < mygame.size(); i++){
        insert(mygame[i].title, mygame[i]);
    }
}
vector<Data>HashMap::sortbyrating(){
    //create vector to store sorted games
    vector<Data> allgames;
    for(int i = 0; i < tablesize; i++){
        //go through the table and only look at the occupied spots
        if(games[i].occupied){
            for(int j = 0; j < games[i].value.size(); j++){
                //add games to vector
                allgames.push_back(games[i].value[j]);
            }
        }
    }
    //sort the games by rank
    sort(allgames.begin(), allgames.end(), comparerating);
    return allgames;
}
vector<Data>HashMap::sortbygenre(string genre) {
    //create vector to store games of a certain genre
    vector<Data> genregames;
    for(int i = 0; i < tablesize; i++){
        //only look at occupied spots in table
        if(games[i].occupied){
            for(int j = 0; j < games[i].value.size();j++){
                Data game = games[i].value[j];
                //games can have multiple genres, so loop through all the genres
                for(int k = 0; k < game.genre.size(); k++){
                    if(genre == game.genre[k]){
                        //if it equals target genre, add game to vector
                        genregames.push_back(games[i].value[j]);
                        //don't add again
                        break;
                    }
                }
            }
        }
    }
    //sort games by rating
    sort(genregames.begin(), genregames.end(), comparerating);
    return genregames;
}
vector<Data>HashMap::sortbyplatform(string platform) {
    //create a vector for the platforms
    vector<Data> platformgames;
    for(int i = 0; i < tablesize; i++){
        //look at occupied spots in table
        if(games[i].occupied){
            for(int j = 0; j < games[i].value.size();j++){
                Data game = games[i].value[j];
                //if platform is the same as target, add to vector
                if(game.platform == platform){
                    platformgames.push_back(games[i].value[j]);
                }
            }
        }
    }
    //sort vector by rating
    sort(platformgames.begin(), platformgames.end(), comparerating);
    return platformgames;
}