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
        cerr << "Error opening file: " << filename << endl;
        return {};
    }
    json j;
    file >> j;
    vector<Data> dataList;
    for (const auto &item : j)
    {
        Data data;
        data.title = item["title"].get<string>();
        data.platform = item["platform"].get<string>();
        data.genre = item["genre"].get<vector<string>>();
        data.rating = item["rating"].get<double>();
        dataList.push_back(data);
    }
    return dataList;
}
bool comparerating(Data &x, Data &y) {
    return x.rating > y.rating;
}

int HashMap::hash(string key) {
    return key.length() % tablesize;
}
void HashMap::resizetable(int size) {
    tablesize = size;
    games.resize(tablesize);
}
HashMap::HashMap(){

}
HashMap::HashMap(int size) {
    resizetable(size);
}
void HashMap::insert(string key, Data &data) {
    if(entries / tablesize >= loadfactor){
        resizetable(tablesize + 100);
    }
    int index = hash(key);
    int i = 1;
    while(games[index].occupied && games[index].key != key){
        index = (index + i*i) % tablesize;
        i++;
    }
    if(!games[index].occupied){
        games[index].key = key;
        games[index].value = {data};
        games[index].occupied = true;
        entries++;
    }
    else{
        games[index].value.push_back(data);
    }
}
void HashMap::load(vector<Data> &mygame) {
    for(int i = 0; i < mygame.size(); i++){
        insert(mygame[i].title, mygame[i]);
    }
}
vector<Data>HashMap::sortbyrating(){
    vector<Data> allgames;
    for(int i = 0; i < tablesize; i++){
        if(games[i].occupied){
            for(int j = 0; j < games[i].value.size(); j++){
                allgames.push_back(games[i].value[j]);
            }
        }
    }
    sort(allgames.begin(), allgames.end(), comparerating);
    return allgames;
}
vector<Data>HashMap::sortbygenre(string genre) {
    vector<Data> genregames;
    for(int i = 0; i < games.size(); i++){
        if(games[i].occupied){
            for(int j = 0; j < games[i].value.size();j++){
                Data game = games[i].value[j];
                for(int k = 0; k < game.genre.size(); k++){
                    if(genre == game.genre[k]){
                        genregames.push_back(games[i].value[j]);
                        break;
                    }
                }
            }
        }
    }
    sort(genregames.begin(), genregames.end(), comparerating);
    return genregames;
}
vector<Data>HashMap::sortbyplatform(string platform) {
    vector<Data> platformgames;
    for(int i = 0; i < games.size(); i++){
        if(games[i].occupied){
            for(int j = 0; j < games[i].value.size();j++){
                Data game = games[i].value[j];
                if(game.platform == platform){
                    platformgames.push_back(games[i].value[j]);
                }
            }
        }
    }
    sort(platformgames.begin(), platformgames.end(), comparerating);
    return platformgames;
}