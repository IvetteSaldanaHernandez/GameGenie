#include "games.h"
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main(){
    string file = "games.json";
    vector<Data> data = loadData(file);

    //create HashMap
    HashMap games(1031);
    //insert data into map
    games.load(data);

    while(true){
        //ask how to sort games
        cout << "Enter a genre to search for:" << endl;
        string mygenre;
        cin >> mygenre;
        cout << "Enter a platform type to search for:" << endl;
        string myplatform;
        cin >> myplatform;
        cout << "Enter a rating to filter by:" << endl;
        float myrating;
        cin >> myrating;

        vector<Data> mygames;
        vector<Data> allgames;
        allgames = games.sortbyrating();

        auto start = high_resolution_clock::now();

        for (int i = 0; i < allgames.size(); i++) {
            Data game = allgames[i];
            bool genresame = false;
            for (int j = 0; j < game.genre.size(); j++) {
                if (game.genre[j] == mygenre) {
                    genresame = true;
                    break;
                }
            }
            if (genresame && game.platform == myplatform && game.rating >= myrating) {
                mygames.push_back(game);
            }
        }
        sort(mygames.begin(), mygames.end(), comparerating);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start).count();
        cout << "Time taken by sorting is " << duration << " seconds." << endl;
        //if nothing in list, say no games found (helpful for troubleshooting)
        if(mygames.empty()){
            cout << "No games found." << endl;
            continue;
        }
        int displayed = 0;
        cout << "\nTop Games:\n";
        for (int i = 0; i < mygames.size(); i++) {
            if (i < 5 || (i >= 5 && displayed < mygames.size())) {
                cout << i + 1 << ". " << mygames[i].title
                     << " | Rating: " << mygames[i].rating
                     << " | Genre: ";
                for (int j = 0; j < mygames[i].genre.size(); j++) {
                    cout << mygames[i].genre[j];
                    if (j < mygames[i].genre.size() - 1) cout << ", ";
                }
                cout << " | Platform: " << mygames[i].platform << endl;

                displayed++;

                if (i >= 4) {
                    cout << "Would you like to see more? (y/n):" << endl;
                    string answer;
                    cin >> answer;
                    if (answer != "y") {
                        break;
                    }
                }
            }
        }

        cout << "Would you like to make another selection? (y/n):" << endl;
        string answertwo;
        cin >> answertwo;
        if (answertwo != "y") {
            break;
        }
    }

    cout << "Have fun gaming!" << endl;
    return 0;
}