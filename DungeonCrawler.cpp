#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<string> c = {};
    string text;

    cin >> text;

    c.push_back(text);
    cout << c[1];
}