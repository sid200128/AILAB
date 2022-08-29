// Online C++ compiler to run C++ program online
#include <math.h>
#include <iostream>
#include <queue>
#include <tuple>
#include <array>

using namespace std;

typedef pair<int, int> Pair;
typedef tuple<double, int, int> Tuple;

class Cell {
    public:
    Pair parent;
    double f, g, h;
    Cell(): parent(-1, -1), f(-1), g(-1), h(-1) {        
    }
};

template <size_t ROW, size_t COL>
bool isValid(array<array<int, COL>, ROW> grid, Pair node) {
    if (node.first < 0 || node.first>=ROW || node.second < 0 || node.second >= COL || grid[node.first][node.second] == 0) return false;
    return true;
}

template <size_t ROW, size_t COL>
double calculateHValue(array<array<int, COL>, ROW> grid, Pair node, Pair dest) {
    double x = node.first - dest.first;
    double y = node.second - dest.second;
    return (sqrt(x*x + y*y));
}


template <size_t ROW, size_t COL>
void aStarSearch(array<array<int, COL>, ROW> grid, Pair src, Pair dest) {
    if (!isValid(grid, src)) {
        cout << "The Source Node is invalid" << endl;
        return;
    }
    
    if (!isValid(grid, dest)) {
        cout << "The Destination Node is invalid" << endl;
        return;
    }
    
    if (src == dest) {
        cout << "We are already at destination" << endl;
        return;
    }
    
    vector<vector<bool>> closedList(ROW, vector<bool> (COL, false));
    
    array<array<Cell, COL>, ROW> cellDetails;
    
    int i = src.first, j = src.second;
    cellDetails[i][j].parent = {i, j};
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    
    priority_queue<Tuple, vector<Tuple>, greater<Tuple>> openList;
    
    openList.emplace(0.0, i, j);
    
    while (!openList.empty()) {
        Tuple curr = openList.top();
        openList.pop();
        i = get<1>(curr);
        j = get<2>(curr);
        closedList[i][j] = true;
        
        int rows[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int cols[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        
        for (int k = 0; k<8; k++) {
            Pair neighbor(i+rows[k], j+cols[k]);
            if (isValid(grid, neighbor)) {
                if (neighbor == dest) {
                    cellDetails[neighbor.first][neighbor.second].parent = {i, j};
                    cout << "Destination Found" << endl;
                    return;
                }
                if (!closedList[neighbor.first][neighbor.second]) {
                    double fNew, gNew, hNew;
                    gNew = cellDetails[i][j].g + 1.0;
                    hNew = calculateHValue(grid, neighbor, dest);
                    fNew = gNew + hNew;
                    if (cellDetails[neighbor.first][neighbor.second].f == -1 || cellDetails[neighbor.first][neighbor.second].f > fNew) {
                        openList.emplace(fNew, neighbor.first, neighbor.second);
                        cellDetails[neighbor.first][neighbor.second].parent = {i, j};
                        cellDetails[neighbor.first][neighbor.second].f = fNew;
                        cellDetails[neighbor.first][neighbor.second].g = gNew;
                        cellDetails[neighbor.first][neighbor.second].h = hNew;
                    }
                }
            }
        }
    }
    cout << "Destination not found" << endl;
}


int main() {
    array<array<int, 10>, 9> grid{
        { { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 } },
          { { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 } },
          { { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 } },
          { { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 } },
          { { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 } },
          { { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 } },
          { { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 } },
          { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 } },
          { { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } } }
    }; 

    Pair src = {8, 0};

    Pair dest = {1, 8};
    
    aStarSearch(grid, src, dest);

    return 0;
}