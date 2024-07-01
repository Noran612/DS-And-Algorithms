#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>

using namespace std;

struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

struct PointHash {
    size_t operator()(const Point& p) const {
        return hash<int>()(p.x) ^ hash<int>()(p.y);
    }
};

struct Node {
    Point point;
    double g, h;
    Node* parent;

    Node(Point p, double g, double h, Node* parent = nullptr) : point(p), g(g), h(h), parent(parent) {}
};

struct CompareNode {
    bool operator()(Node* a, Node* b) {
        return (a->g + a->h) > (b->g + b->h);
    }
};

double heuristic(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

vector<Point> aStar(Point start, Point goal, vector<vector<int>>& grid) {
    priority_queue<Node*, vector<Node*>, CompareNode> openSet;
    unordered_map<Point, Node*, PointHash> allNodes;
    vector<Point> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    openSet.push(new Node(start, 0, heuristic(start, goal)));

    while (!openSet.empty()) {
        Node* current = openSet.top();
        openSet.pop();

        if (current->point == goal) {
            vector<Point> path;
            while (current != nullptr) {
                path.push_back(current->point);
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (auto& dir : directions) {
            Point neighbor(current->point.x + dir.x, current->point.y + dir.y);
            if (neighbor.x < 0 || neighbor.y < 0 || neighbor.x >= grid.size() || neighbor.y >= grid[0].size() || grid[neighbor.x][neighbor.y] == 1) {
                continue;
            }
            double tentativeG = current->g + 1;
            if (allNodes.find(neighbor) == allNodes.end() || tentativeG < allNodes[neighbor]->g) {
                Node* neighborNode = new Node(neighbor, tentativeG, heuristic(neighbor, goal), current);
                openSet.push(neighborNode);
                allNodes[neighbor] = neighborNode;
            }
        }
    }
    return {};
}

int main() {
    vector<vector<int>> grid = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0},
    };
    Point start = {0, 0};
    Point goal = {4, 4};

    vector<Point> path = aStar(start, goal, grid);
    if (!path.empty()) {
        cout << "Path found:" << endl;
        for (auto& p : path) {
            cout << "(" << p.x << ", " << p.y << ")" << endl;
        }
    } else {
        cout << "No path found." << endl;
    }

   
