#include "games.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;
using namespace std::chrono;

int main ()
{
    string file = "games.json";
    vector<Data> data = loadData(file);

    // create HashMap
    HashMap games(1031);
    // insert data into map
    games.load(data);

    while (true)
    {
        // ask how to sort games
        cout << "Enter a genre to search for: " << endl;
        string mygenre;
        cin >> mygenre;
        cout << "Enter a platform type to search for: " << endl;
        string myplatform;
        cin >> myplatform;
        cout << "Enter a minimum rating to filter by: " << endl;
        double myrating;
        cin >> myrating;

        vector<Data> mygames;
        vector<Data> allgames;
        allgames = games.sortbyrating();

        // https://www.geeksforgeeks.org/chrono-in-c/
        auto startHashMap = high_resolution_clock::now();

        for (int i = 0; i < allgames.size(); i++)
        {
            Data game = allgames[i];
            bool genresame = false;
            for (int j = 0; j < game.genre.size(); j++)
            {
                if (game.genre[j] == mygenre)
                {
                    genresame = true;
                    break;
                }
            }
            if (genresame && game.platform == myplatform && game.rating >= myrating)
            {
                mygames.push_back(game);
            }
        }
        sort(mygames.begin(), mygames.end(), comparerating);
        auto stopHashMap = high_resolution_clock::now();
        auto durationHashMap = duration_cast<microseconds>(stopHashMap - startHashMap).count();
        cout << "Time taken by sorting by Hash Map is " << durationHashMap << " microseconds!" << endl;

        json outputHashMap; // for frontend to get time data
        for (int i = 0; i < mygames.size(); i++)
        {
            json game;
            game["title"] = mygames[i].title;
            game["rating"] = mygames[i].rating;
            game["platform"] = mygames[i].platform;
            game["genre"] = mygames[i].genre;
            outputHashMap.push_back(game);
        }
        ofstream outFileHashMap("../frontend/hash_output.json");
        outFileHashMap << outputHashMap.dump(2); // pretty print!
        outFileHashMap.close();
        ofstream timeFileHashMap("../frontend/hash_time.txt");
        timeFileHashMap << durationHashMap;
        timeFileHashMap.close();

        // heap blueprint:
        Heap heap;
        auto startHeap = high_resolution_clock::now();
        for (int i = 0; i < allgames.size(); i++)
        {
            Data game = allgames[i];
            bool genresame = false;
            for (int j = 0; j < game.genre.size(); j++)
            {
                if (game.genre[j] == mygenre)
                {
                    genresame = true;
                    break;
                }
            }
            if (genresame && game.platform == myplatform && game.rating >= myrating)
            {
                heap.insert(game);
            }
        }
        bool ascending = false;                                                 // change to false for descending
        bool byRating = true;                                                   // change to false for title
        vector<Data> topGames = heap.sortbygenre(mygenre, ascending, byRating); // some way to get top games
        auto stopHeap = high_resolution_clock::now();
        auto durationHeap = duration_cast<microseconds>(stopHeap - startHeap).count();
        cout << "Time taken by sorting by Heap is " << durationHeap << " microseconds!" << endl;

        json outputHeap; // for frontend to get time data
        for (int i = 0; i < topGames.size(); i++)
        {
            json game;
            game["title"] = topGames[i].title;
            game["rating"] = topGames[i].rating;
            game["platform"] = topGames[i].platform;
            game["genre"] = topGames[i].genre;
            outputHeap.push_back(game);
        }
        ofstream outFileHeap("../frontend/heap_output.json");
        outFileHeap << outputHeap.dump(2); // pretty print!
        outFileHeap.close();
        ofstream timeFileHeap("../frontend/heap_time.txt");
        timeFileHeap << durationHeap;
        timeFileHeap.close();

        // if nothing in list, say no games found (helpful for troubleshooting)
        if (mygames.empty())
        {
            cout << "No games found :(" << endl;
            continue;
        }
        int displayed = 0;
        cout << "\nTop Games:\n";
        for (int i = 0; i < mygames.size(); i++)
        {
            if (i < 5 || (i >= 5 && displayed < mygames.size()))
            {
                cout << i + 1 << ". " << mygames[i].title
                     << " | Rating: " << mygames[i].rating
                     << " | Genre: ";
                for (int j = 0; j < mygames[i].genre.size(); j++)
                {
                    cout << mygames[i].genre[j];
                    if (j < mygames[i].genre.size() - 1)
                        cout << ", ";
                }
                cout << " | Platform: " << mygames[i].platform << endl;

                displayed++;

                if (i >= 4)
                {
                    cout << "Would you like to see more? (y/n): " << endl;
                    string answer;
                    cin >> answer;
                    if (answer != "y")
                    {
                        break;
                    }
                }
            }
        }

        cout << "Would you like to make another selection? (y/n): " << endl;
        string answertwo;
        cin >> answertwo;
        if (answertwo != "y")
        {
            break;
        }
    }

    cout << "Have fun gaming!" << endl;
    return 0;
}