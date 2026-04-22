#include <iostream>
using namespace std;

int cost[10][10];
int n;

void initGraph() {
    cout << "Enter total number of cities: ";
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cost[i][j] = 999;
}

void createGraph() {
    int c1, c2, d;
    char ch;
    do {
        cout << "Enter city1, city2 and distance: ";
        cin >> c1 >> c2 >> d;
        if (cost[c1][c2] == 999) {
            cost[c1][c2] = d;
            cost[c2][c1] = d;
        } else {
            cout << "These two cities are already connected\n";
        }
        cout << "Connect more cities? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
}

void displayGraph() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << cost[i][j] << "\t";
        }
        cout << "\n";
    }
}

void prims(int v) {
    int nearest[10], t[10][3];
    int r = 0;
    int mincost = 0;
    int min, j;

    nearest[v] = -1;
    for (int i = 0; i < n; i++) {
        if (i != v) {
            nearest[i] = v;
        }
    }

    for (int i = 1; i < n; i++) {
        min = 999;
        for (int k = 0; k < n; k++) {
            if (nearest[k] != -1 && cost[k][nearest[k]] < min) {
                j = k;
                min = cost[k][nearest[k]];
            }
        }
        t[r][0] = nearest[j];
        t[r][1] = j;
        t[r][2] = min;
        r = r + 1;

        mincost = mincost + cost[j][nearest[j]];
        nearest[j] = -1;

        for (int k = 0; k < n; k++) {
            if (nearest[k] != -1 && cost[k][nearest[k]] > cost[k][j]) {
                nearest[k] = j;
            }
        }
    }

    cout << "Weight of MST: " << mincost << endl;
    cout << "Edges in MST:\n";
    for (int i = 0; i < n - 1; i++) {
        cout << t[i][0] << "->" << t[i][1] << "[" << t[i][2] << "]" << endl;
    }
    cout << "\n";
}

int main() {
    initGraph();
    createGraph();
    displayGraph();

    int v;
    cout << "Enter start vertex: ";
    cin >> v;
    prims(v);

    return 0;
}
