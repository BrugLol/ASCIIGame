#include <iostream>
#include <vector>
#include <map>

using namespace std;



int main() {
    map<char, int> tiles = {{}};

    int xsize = 3; //size of the dungeon (X-axis)
    int ysize = 3; //size of the dungeon (Y-axis)

    for (int y = 0; y < ysize; y++) {

        cout << "#";

        for (int x = 0; x < xsize; x++) {
            cout << "#";

            
        }

        cout << endl;
    }
}