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
            head[i] = new gnode(i);   // dummy head
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

                cout << "Add more friends for "
                     << name[i] << " (y/n)? ";
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

    // BFT
    void bft(int start) {
        bool visited[20] = {false};
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "\nBFT starting from "
             << name[start] << ": ";

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

    // -------- DFT (DFS helper) --------
    void dfsUtil(int v, bool visited[]) {
        visited[v] = true;
        cout << v << " (" << name[v] << ") ";

        gnode *temp = head[v]->next;
        while (temp != NULL) {
            if (!visited[temp->vertex]) {
                dfsUtil(temp->vertex, visited);
            }
            temp = temp->next;
        }
    }

    
    void dft(int start) {
        bool visited[20] = {false};

        cout << "\nDFT starting from "
             << name[start] << ": ";
        dfsUtil(start, visited);
        cout << endl;
    }

    // -------- Recursive BFS --------
    void bfsRecursiveUtil(queue<int>& q, bool visited[]) {
        if (q.empty()) return;

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

        bfsRecursiveUtil(q, visited); // recursive call
    }

    void bfs_recursive(int start) {
        bool visited[20] = {false};
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "\nRecursive BFS starting from " << name[start] << ": ";
        bfsRecursiveUtil(q, visited);
        cout << endl;
    }

    // -------- Recursive DFS --------
    void dfsRecursiveUtil(int v, bool visited[]) {
        visited[v] = true;
        cout << v << " (" << name[v] << ") ";

        gnode *temp = head[v]->next;
        while (temp != NULL) {
            if (!visited[temp->vertex]) {
                dfsRecursiveUtil(temp->vertex, visited); // recursive call
            }
            temp = temp->next;
        }
    }

    void dfs_recursive(int start) {
        bool visited[20] = {false};

        cout << "\nRecursive DFS starting from " << name[start] << ": ";
        dfsRecursiveUtil(start, visited);
        cout << endl;
    }
};

int main() {
    graph g;
    g.create();
    g.display();

    int start;
    cout << "\nEnter starting user ID for BFT & DFT: ";
    cin >> start;

    g.bft(start);
    g.dft(start);
    g.bfs_recursive(start);
    g.dfs_recursive(start);

    return 0;
}