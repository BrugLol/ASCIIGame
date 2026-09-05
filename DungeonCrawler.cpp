#include <iostream>
#include <vector>
#include <map>

using namespace std;



int main() {
    vector<vector <char>> board;

    int xsize = 15; //size of the dungeon (X-axis)
    int ysize = 5; //size of the dungeon (Y-axis)

    int middlex = xsize / 2;
    int middley = ysize / 2;

    for (int col = 0; col < ysize; col++) {
        board.push_back({'#'});

        for (int row = 0; row < xsize-1; row++) {
            if (col == 0 || col == ysize-1) {
                board[col].push_back({'#'});
            } else {
                board[col].push_back({'.'});
            }
        }


        board[col][xsize-1] = '#';
    }

    // The player spawns
    board[middley][middlex] = '@';

    for (auto& row : board) {
        for (char val : row) {
            cout << val;

            
        }

        cout << endl;
    }
}