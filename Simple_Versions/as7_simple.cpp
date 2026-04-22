#include <iostream>
#include <vector>
using namespace std;

bool isSafe(vector<vector<int>> &board, int row, int col, int n) {
    int i, j;
    for (i = 0; i < row; i++) {
        if (board[i][col] == 1)
            return false;
    }
    for (i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1)
            return false;
    }
    for (i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 1)
            return false;
    }
    return true;
}

void place(int row, int n, vector<vector<int>> &board) {
    if (row == n) {
        cout << "Solution:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        return;
    }
    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col, n)) {
            board[row][col] = 1;
            place(row + 1, n, board);
            board[row][col] = 0;
        }
    }
}

int main() {
    int n = 8;
    vector<vector<int>> board(n, vector<int>(n, 0));
    place(0, n, board);
    return 0;
}
