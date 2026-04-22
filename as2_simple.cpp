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

    cout << "\nSorted by phone number:\n";
    quickSort(arr, 0, n - 1);
    display(arr);

    return 0;
}
