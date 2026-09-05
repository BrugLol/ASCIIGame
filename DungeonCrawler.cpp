#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Player {
public:
    int posx;
    int posy;

    Player(int x, int y) {
        posx = x;
        posy = y;
    }

    void Move(vector<vector <char>>& board, int ysize, int xsize) {
        char direction;
        cout << "What direction would you like to move? (w, a, s d) ";

        cin >> direction;

        int newY;
        int newX;

        if (direction == 'w' && posy-1 != 0) {
            newY = posy - 1;

            if (board[newY][posx] == '#') {
                newY = posy;
            } else {
                posy = newY;
            }
        }
        if (direction == 's' && posy+1 != ysize-1) {
            newY = posy + 1;

            if (board[newY][posx] == '#') {
                newY = posy;
            } else {
                posy = newY;
            }
        }
        if (direction == 'a' && posx-1 != 0) {
            newX = posx - 1;

            if (board[posy][newX] == '#') {
                newX = posx;
            } else {
                posx = newX;
            }
        }
        if (direction == 'd' && posx+1 != xsize-1) {
            newX = posx + 1;

            if (board[posy][newX] == '#') {
                newX = posx;
            } else {
                posx = newX;
            }
        }
    }
};

void GenerateBoard(vector<vector <char>>& board, int ysize, int xsize) {
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
}


void DrawBoard(vector<vector <char>> board, Player p) {
    board[p.posy][p.posx] = '@';

    for (auto& row : board) {
        for (char val : row) {
            cout << val;

            
        }

        cout << endl;
    }
}



int main() {
    vector<vector <char>> board;
    

    int xsize = 15; //size of the dungeon (X-axis)
    int ysize = 5; //size of the dungeon (Y-axis)

    int middlex = xsize / 2;
    int middley = ysize / 2;

    //Creates an defines the initial position of the player.
    Player knight(middlex, middley);
    

    GenerateBoard(board, ysize, xsize);


    // Game loop
    while (true) {
        system("cls");
        
        DrawBoard(board, knight);
        knight.Move(board, ysize, xsize);

        cout << endl;
    }
}