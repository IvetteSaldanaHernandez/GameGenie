#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

struct Data
{
    string title;
    string platform;
    string genre;
    float rating;
};

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
    vector<Data> data;
    for (const auto &item : j)
    {
        Data data;
        data.title = item["title"].get<string>();
        data.platform = item["platform"].get<string>();
        data.genre = item["genre"].get<string>();
        data.rating = item["rating"].get<double>();
        data.push_back(data);
    }
    return data;
}