#include <iostream>
using namespace std;

int main() {
    int n, W;
    cin >> n >> W;

    int wt[n + 1], val[n + 1];

    cout << "Enter the weights: " << endl;
    for (int i = 1; i <= n; i++) {
        cin >> wt[i];
    }

    cout << "Enter the values: " << endl;
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
    }

    int B[n + 1][W + 1];

    for (int w = 0; w <= W; w++) {
        B[0][w] = 0;
    }

    for (int i = 0; i <= n; i++) {
        B[i][0] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (wt[i] <= w) {
                B[i][w] = max(B[i - 1][w], val[i] + B[i - 1][w - wt[i]]);
            } else {
                B[i][w] = B[i - 1][w];
            }
        }
    }

    cout << B[n][W] << endl;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            cout << B[i][j] << " ";
        }
        cout << endl;
    }

    cout << "backtracking to find the elements.." << endl;
    int i = n, w = W;

    cout << "Selected items:\n";
    while (i > 0 && w > 0) {
        if (B[i][w] == B[i - 1][w]) {
            i--;
        } else {
            cout << "Item " << i
                 << " (wt=" << wt[i]
                 << ", val=" << val[i] << ")\n";
            w = w - wt[i];
            i--;
        }
    }

    return 0;
}
