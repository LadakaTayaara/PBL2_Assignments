#include <iostream>
#include <queue>
#include <stack>
using namespace std;

struct Node {
    int vertex;
    Node* next;
};

Node* head[20];
string name[20];
int n;
bool visited[20];

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

void bfs(int v) {
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }
    queue<int> q;
    q.push(v);
    visited[v] = true;
    
    cout << "\nBFS from " << name[v] << ": ";
    while (!q.empty()) {
        v = q.front();
        q.pop();
        cout << v << " (" << name[v] << ") ";
        
        Node* temp = head[v]->next;
        while (temp != NULL) {
            int w = temp->vertex;
            if (!visited[w]) {
                q.push(w);
                visited[w] = true;
            }
            temp = temp->next;
        }
    }
    cout << endl;
}

void dft(int v) {
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }
    stack<int> s;
    s.push(v);
    visited[v] = true;
    
    cout << "\nDFT from " << name[v] << ": ";
    do {
        v = s.top();
        s.pop();
        cout << v << " (" << name[v] << ") ";
        
        Node* temp = head[v]->next;
        while (temp != NULL) {
            int w = temp->vertex;
            if (!visited[w]) {
                s.push(w);
                visited[w] = true;
            }
            temp = temp->next;
        }
    } while (!s.empty());
    cout << endl;
}



void dfs_recursive(int v) {
    cout << v << " (" << name[v] << ") ";
    visited[v] = true;
    
    Node* temp = head[v]->next;
    while (temp != NULL) {
        int w = temp->vertex;
        if (!visited[w]) {
            dfs_recursive(w);
        }
        temp = temp->next;
    }
}

int main() {
    inputUsers();
    createGraph();
    displayGraph();

    int start;
    cout << "\nEnter starting user ID: ";
    cin >> start;

    bfs(start);
    dft(start);
    
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }
    cout << "\nRecursive DFS from " << name[start] << ": ";
    dfs_recursive(start);
    cout << endl;

    return 0;
}
