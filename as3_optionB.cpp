#include <iostream>
#include <queue>
using namespace std;

class gnode {
public:
    int vertex;
    gnode *next;

    gnode(int v) {
        vertex = v;
        next = NULL;
    }
};

class graph {
    gnode *head[20];
    string name[20];
    int n;

public:
    graph() {
        cout << "Enter number of users: ";
        cin >> n;

        for (int i = 0; i < n; i++) {
            cout << "Enter name of user " << i << ": ";
            cin >> name[i];
            head[i] = new gnode(i);  // dummy head
        }
    }

    void create() {
        char ans;
        int v;

        for (int i = 0; i < n; i++) {
            gnode *temp = head[i];

            do {
                cout << "Enter friend ID of user " << i
                     << " (" << name[i] << "): ";
                cin >> v;

                if (v == i) {
                    cout << "Self friendship not allowed\n";
                } else {
                    gnode *curr = new gnode(v);
                    temp->next = curr;
                    temp = curr;
                }

                cout << "Add more friends for " << name[i] << " (y/n)? ";
                cin >> ans;

            } while (ans == 'y' || ans == 'Y');
        }
    }

    void display() {
        cout << "\nAdjacency List:\n";
        for (int i = 0; i < n; i++) {
            cout << i << " (" << name[i] << ") -> ";
            gnode *temp = head[i]->next;

            while (temp != NULL) {
                cout << temp->vertex
                     << " (" << name[temp->vertex] << ") -> ";
                temp = temp->next;
            }
            cout << "NULL\n";
        }
    }

    // -------- Iterative BFS (no change needed) --------
    void bft(int start) {
        bool visited[20] = {false};
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "\nBFT starting from " << name[start] << ": ";

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            cout << v << " (" << name[v] << ") ";

            gnode *temp = head[v]->next;
            while (temp != NULL) {
                if (!visited[temp->vertex]) {
                    visited[temp->vertex] = true;
                    q.push(temp->vertex);
                }
                temp = temp->next;
            }
        }
        cout << endl;
    }

    // -------- Iterative DFT (no change needed) --------
    void dft(int start) {
        bool visited[20] = {false};

        cout << "\nDFT starting from " << name[start] << ": ";

        // Using recursion inline — but visited[] stays here (created once)
        // We use a lambda-style approach via a nested call trick
        // Actually for iterative DFT we use a stack:
        // But original code used recursion — so let's keep recursion,
        // just call dft(v, visited) directly (Option B style)
        dft(start, visited);   // calls the overloaded version below
        cout << endl;
    }

    // Overloaded dft — this IS the recursive function now (no separate util)
    void dft(int v, bool visited[]) {
        visited[v] = true;
        cout << v << " (" << name[v] << ") ";

        gnode *temp = head[v]->next;
        while (temp != NULL) {
            if (!visited[temp->vertex]) {
                dft(temp->vertex, visited);  // recurse directly
            }
            temp = temp->next;
        }
    }

    // -------- Recursive BFS (Option B — visited[] passed from main) --------
    void bfs_recursive(int v, bool visited[], queue<int>& q) {
        if (q.empty()) return;

        int curr = q.front();
        q.pop();

        cout << curr << " (" << name[curr] << ") ";

        gnode *temp = head[curr]->next;
        while (temp != NULL) {
            if (!visited[temp->vertex]) {
                visited[temp->vertex] = true;
                q.push(temp->vertex);
            }
            temp = temp->next;
        }

        bfs_recursive(curr, visited, q);  // recurse
    }

    // -------- Recursive DFS (Option B — visited[] passed from main) --------
    void dfs_recursive(int v, bool visited[]) {
        visited[v] = true;
        cout << v << " (" << name[v] << ") ";

        gnode *temp = head[v]->next;
        while (temp != NULL) {
            if (!visited[temp->vertex]) {
                dfs_recursive(temp->vertex, visited);  // recurse directly
            }
            temp = temp->next;
        }
    }
};

int main() {
    graph g;
    g.create();
    g.display();

    int start;
    cout << "\nEnter starting user ID for traversals: ";
    cin >> start;

    // Iterative BFS & DFT — no setup needed
    g.bft(start);
    g.dft(start);   // calls overloaded dft internally

    // Recursive BFS — caller (main) creates visited[] and queue
    bool vis1[20] = {false};
    queue<int> q;
    vis1[start] = true;
    q.push(start);
    cout << "\nRecursive BFS starting from: ";
    g.bfs_recursive(start, vis1, q);
    cout << endl;

    // Recursive DFS — caller (main) creates visited[]
    bool vis2[20] = {false};
    cout << "\nRecursive DFS starting from: ";
    g.dfs_recursive(start, vis2);
    cout << endl;

    return 0;
}
