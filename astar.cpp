#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

const int ROW = 5;
const int COL = 5;

// Structure for each cell
struct Node {
    int x, y;
    int g, h, f;

    Node* parent;

    Node(int x, int y, int g, int h, Node* parent = nullptr) {
        this->x = x;
        this->y = y;
        this->g = g;
        this->h = h;
        this->f = g + h;
        this->parent = parent;
    }
};

// Comparator for priority queue
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->f > b->f;
    }
};

// Manhattan Distance Heuristic
int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Check valid cell
bool isValid(int x, int y) {
    return (x >= 0 && x < ROW && y >= 0 && y < COL);
}

// Print final path
void printPath(Node* goalNode) {
    vector<pair<int, int>> path;

    Node* current = goalNode;

    while (current != nullptr) {
        path.push_back({current->x, current->y});
        current = current->parent;
    }

    reverse(path.begin(), path.end());

    cout << "\nShortest Path:\n";

    for (auto p : path) {
        cout << "(" << p.first << "," << p.second << ") ";
    }

    cout << endl;
}

// A* Algorithm
void aStar(vector<vector<int>>& grid,
           pair<int, int> start,
           pair<int, int> goal) {

    priority_queue<Node*, vector<Node*>, Compare> openList;

    bool closedList[ROW][COL] = {false};

    int sx = start.first;
    int sy = start.second;

    int gx = goal.first;
    int gy = goal.second;

    Node* startNode = new Node(
        sx,
        sy,
        0,
        heuristic(sx, sy, gx, gy)
    );

    openList.push(startNode);

    // Directions: Up, Down, Left, Right
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!openList.empty()) {

        Node* current = openList.top();
        openList.pop();

        int x = current->x;
        int y = current->y;

        // Goal reached
        if (x == gx && y == gy) {
            printPath(current);
            return;
        }

        closedList[x][y] = true;

        // Explore neighbors
        for (int i = 0; i < 4; i++) {

            int nx = x + dx[i];
            int ny = y + dy[i];

            if (isValid(nx, ny) &&
                grid[nx][ny] == 0 &&
                !closedList[nx][ny]) {

                int newG = current->g + 1;
                int newH = heuristic(nx, ny, gx, gy);

                Node* neighbor = new Node(
                    nx,
                    ny,
                    newG,
                    newH,
                    current
                );

                openList.push(neighbor);
            }
        }
    }

    cout << "No path found!\n";
}

// Driver Code
int main() {

    // 0 = free path
    // 1 = obstacle

    vector<vector<int>> grid = {

        {0, 0, 0, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0}
    };

    pair<int, int> start = {0, 0};
    pair<int, int> goal  = {4, 4};

    aStar(grid, start, goal);

    return 0;
}