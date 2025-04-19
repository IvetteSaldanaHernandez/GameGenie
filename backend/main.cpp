#include "games.h"
#include <iostream>
using namespace std;

int main(){
    string file = "games.json";
    vector<Data> data = loadData(file);

    //create HashMap
    HashMap games(1031);
    //insert data into map
    games.load(data);

    while(true){
        //ask how to sort games
        cout << "How would you like the games sorted? (enter number 1-3)" << endl;
        cout << "1. Ratings" << endl;
        cout << "2. Genre" << endl;
        cout << "3. Platform" << endl;
        int choice;
        cin >> choice;

        vector<Data> mygames;
        if(choice == 1){
            mygames = games.sortbyrating();
        }
        else if(choice == 2){
            cout << "Enter a genre to search for:" << endl;
            string mygenre;
            cin >> mygenre;
            mygames = games.sortbygenre(mygenre);
        }
        else if(choice == 3){
            cout << "Enter a platform type to search for:" << endl;
            string myplatform;
            cin >> myplatform;
            mygames = games.sortbyplatform(myplatform);
        }
        else{
            cout << "Please enter a valid input." << endl;
            continue;
        }
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