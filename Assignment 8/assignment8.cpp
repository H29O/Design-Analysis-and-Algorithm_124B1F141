
#include <iostream>
#include <queue>
#include <vector>
#include <climits>
using namespace std;

int n;
int cost[10][10];
int bestCost = INT_MAX;
vector<int> bestPath;

struct Node {
    vector<int> path;
    int visited[10] = {0};
    int level;
    int currentCost;
    int bound;
};

struct Compare {
    bool operator()(Node a, Node b) {
        return a.bound > b.bound;
    }
};

int calculateBound(Node node) {
    int bound = node.currentCost;

    for (int i = 0; i < n; i++) {
        if (!node.visited[i] || i == node.path.back()) {
            int minCost = INT_MAX;

            for (int j = 0; j < n; j++) {
                if (i != j && cost[i][j] < minCost)
                    minCost = cost[i][j];
            }

            if (minCost != INT_MAX)
                bound += minCost;
        }
    }

    return bound;
}

void tsp() {
    priority_queue<Node, vector<Node>, Compare> pq;

    Node start;
    start.path.push_back(0);
    start.visited[0] = 1;
    start.level = 1;
    start.currentCost = 0;
    start.bound = calculateBound(start);

    pq.push(start);

    while (!pq.empty()) {
        Node curr = pq.top();
        pq.pop();

        if (curr.bound >= bestCost)
            continue;

        if (curr.level == n) {
            int total = curr.currentCost + cost[curr.path.back()][0];

            if (total < bestCost) {
                bestCost = total;
                bestPath = curr.path;
                bestPath.push_back(0);
            }
            continue;
        }

        int last = curr.path.back();

        for (int i = 0; i < n; i++) {
            if (!curr.visited[i] && cost[last][i] > 0) {
                Node child = curr;
                child.path.push_back(i);
                child.visited[i] = 1;
                child.level = curr.level + 1;
                child.currentCost =
                    curr.currentCost + cost[last][i];
                child.bound = calculateBound(child);

                if (child.bound < bestCost)
                    pq.push(child);
            }
        }
    }
}

int main() {
    cout << "Enter number of cities (max 10): ";
    cin >> n;

    if (n < 2 || n > 10) {
        cout << "Invalid number of cities.\n";
        return 0;
    }

    cout << "Enter the cost matrix (0 means no direct road):\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
        }
    }

    tsp();

    if (bestCost == INT_MAX) {
        cout << "No complete tour exists.\n";
    } else {
        cout << "\nMinimum Cost: " << bestCost;
        cout << "\nOptimal Route: ";

        for (int city : bestPath)
            cout << city << " ";

        cout << "\n";
    }

    return 0;
}
