#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct User {
    string name;
    long mobile_no;
    int amount;
};

void display(vector<User> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i].name << "\t" << arr[i].mobile_no << "\t" << arr[i].amount << endl;
    }
}

int partition(vector<User> &arr, int low, int high) {
    long pivot = arr[high].mobile_no;
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (arr[j].mobile_no >= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<User> &arr, int low, int high) {
    if (low < high) {
        long pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(vector<User> &arr, int left, int mid, int right) {
    vector<User> L(arr.begin() + left, arr.begin() + mid + 1);
    vector<User> R(arr.begin() + mid + 1, arr.begin() + right + 1);
    int i = 0, j = 0, k = left;
    while (i < L.size() && j < R.size()) {
        if (L[i].amount <= R[j].amount)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < L.size()) arr[k++] = L[i++];
    while (j < R.size()) arr[k++] = R[j++];
}

void mergeSort(vector<User> &arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    int n;
    cout << "How many elements does the array have: ";
    cin >> n;
    vector<User> arr(n);

    for (int i = 0; i < n; i++) {
        cout << "\nEnter details for User " << i + 1 << endl;
        cout << "Name: "; cin >> arr[i].name;
        cout << "Mobile Number: "; cin >> arr[i].mobile_no;
        cout << "Bill Amount: "; cin >> arr[i].amount;
    }

    cout << "\nSorted by phone number (Quick Sort):\n";
    quickSort(arr, 0, n - 1);
    display(arr);

    cout << "\nSorted by bill amount (Merge Sort):\n";
    mergeSort(arr, 0, n - 1);
    display(arr);

    return 0;
}
