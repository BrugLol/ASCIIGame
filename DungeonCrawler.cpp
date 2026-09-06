#include <iostream>
#include <vector>
#include <random>

using namespace std;

struct Position { //allows the easy modification of structs
    int x;
    int y;

    Position(int ypos, int xpos) {
        x = xpos;
        y = ypos;
    }
};



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



int randomGen() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 100);

    int randomNum = dist(gen);
    return randomNum;
}

Position randomPos(int ysize, int xsize, vector<vector <char>>& board) {
    random_device rd;
    mt19937 gen(rd());


    
    while (true) {
        uniform_int_distribution<int> y(1, ysize-1);
        uniform_int_distribution<int> x(1, xsize-1);
        
       int xp = x(gen);
       int yp = y(gen);

        if (board[yp][xp] == '.') {
            Position p(yp, xp);

            return p;
        }
    }
    
}

bool IsDungeonClearable(vector<vector<char>> board, Player k, Position p) {
    vector<Position> visitedtiles;
    vector<Position> queue;

    Position plrpos(k.posy, k.posx);

    // Player can't start inside a wall
    if (board[k.posy][k.posx] == '#') {
        return false;
    }

    queue.push_back(plrpos);
    visitedtiles.push_back(plrpos);

    int i = 0;

    while (i < queue.size()) {

        Position current = queue[i];
        i++;

        // We reached the exit
        if (current.x == p.x && current.y == p.y) {
            return true;
        }

        // Four possible directions
        int dx[] = { 0, 0, -1, 1 };
        int dy[] = { -1, 1, 0, 0 };

        for (int j = 0; j < 4; j++) {
            int newX = current.x + dx[j];
            int newY = current.y + dy[j];

            // Make sure we're inside the board
            if (newX < 0 || newX >= board[0].size() ||
                newY < 0 || newY >= board.size()) {
                continue;
            }

            // Don't walk through walls
            if (board[newY][newX] == '#') {
                continue;
            }

            Position next(newY, newX);

            // Check if we've already visited this tile
            bool alreadyVisited = false;

            for (Position visited : visitedtiles) {
                if (visited.x == next.x && visited.y == next.y) {
                    alreadyVisited = true;
                    break;
                }
            }

            if (!alreadyVisited) {
                visitedtiles.push_back(next);
                queue.push_back(next);
            }
        }
    }

    // Explored everything and never found the exit
    return false;
}

void GenerateBoard(vector<vector <char>>& board, int ysize, int xsize, Player k) {
    for (int col = 0; col < ysize; col++) {
        board.push_back({'#'});

        for (int row = 0; row < xsize-1; row++) {
            if (col == 0 || col == ysize-1) {
                board[col].push_back({'#'});
            } else {
                if (randomGen() <= 30) {
                    board[col].push_back({'#'});
                } else {
                    board[col].push_back({'.'});
                }
            }
        }

        board[col][xsize-1] = '#';
    }



    Position rpos = randomPos(ysize, xsize, board); //get's the random pos

    int rx = rpos.x;
    int ry = rpos.y;

    board[ry][rx] = '>';


    if (!IsDungeonClearable(board, k, rpos)) {
        board.clear();
        GenerateBoard(board, ysize, xsize, k);
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
    

    GenerateBoard(board, ysize, xsize, knight);

    


    // Game loop
    while (true) {
        system("cls");
        
        DrawBoard(board, knight);
        knight.Move(board, ysize, xsize);

        cout << endl;
    }
}