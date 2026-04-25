#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int vertex;
    Node* next;
};

Node* head[20];
string name[20];
int n;

Node* newNode(int v) {
    Node* node = new Node();
    node->vertex = v;
    node->next = NULL;
    return node;
}

void inputUsers() {
    cout << "Enter number of users: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Enter name of user " << i << ": ";
        cin >> name[i];
        head[i] = newNode(i);
    }
}

void createGraph() {
    char ans;
    int v;
    for (int i = 0; i < n; i++) {
        Node* temp = head[i];
        do {
            cout << "Enter friend ID of user " << i << " (" << name[i] << "): ";
            cin >> v;
            if (v == i) {
                cout << "Self friendship not allowed\n";
            } else {
                Node* curr = newNode(v);
                temp->next = curr;
                temp = curr;
            }
            cout << "Add more friends for " << name[i] << " (y/n)? ";
            cin >> ans;
        } while (ans == 'y' || ans == 'Y');
    }
}

void displayGraph() {
    cout << "\nAdjacency List:\n";
    for (int i = 0; i < n; i++) {
        cout << i << " (" << name[i] << ") -> ";
        Node* temp = head[i]->next;
        while (temp != NULL) {
            cout << temp->vertex << " (" << name[temp->vertex] << ") -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
}

void bft(int start) {
    bool visited[20] = {false};
    queue<int> q;
    visited[start] = true;
    q.push(start);
    cout << "\nBFT from " << name[start] << ": ";
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        cout << v << " (" << name[v] << ") ";
        Node* temp = head[v]->next;
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

void dft(int v, bool isFirst = true) {
    static bool visited[20];
    if (isFirst) {
        fill(visited, visited + 20, false);
        cout << "\nDFT from " << name[v] << ": ";
    }
    visited[v] = true;
    cout << v << " (" << name[v] << ") ";
    Node* temp = head[v]->next;
    while (temp != NULL) {
        if (!visited[temp->vertex]) dft(temp->vertex, false);
        temp = temp->next;
    }
    if (isFirst) cout << endl;
}

void bfs_recursive(int start, bool isFirst = true) {
    static bool visited[20];
    static queue<int> q;
    if (isFirst) {
        fill(visited, visited + 20, false);
        while (!q.empty()) q.pop();
        visited[start] = true;
        q.push(start);
        cout << "\nRecursive BFS from " << name[start] << ": ";
    }
    if (q.empty()) { cout << endl; return; }
    int v = q.front(); q.pop();
    cout << v << " (" << name[v] << ") ";
    Node* temp = head[v]->next;
    while (temp != NULL) {
        if (!visited[temp->vertex]) {
            visited[temp->vertex] = true;
            q.push(temp->vertex);
        }
        temp = temp->next;
    }
    bfs_recursive(start, false);
}

void dfs_recursive(int v, bool isFirst = true) {
    static bool visited[20];
    if (isFirst) {
        fill(visited, visited + 20, false);
        cout << "\nRecursive DFS from " << name[v] << ": ";
    }
    visited[v] = true;
    cout << v << " (" << name[v] << ") ";
    Node* temp = head[v]->next;
    while (temp != NULL) {
        if (!visited[temp->vertex]) dfs_recursive(temp->vertex, false);
        temp = temp->next;
    }
    if (isFirst) cout << endl;
}

int main() {
    inputUsers();
    createGraph();
    displayGraph();

    int start;
    cout << "\nEnter starting user ID: ";
    cin >> start;

    bft(start);
    dft(start);
    bfs_recursive(start);
    dfs_recursive(start);

    return 0;
}
