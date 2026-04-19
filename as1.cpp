#include <iostream>
#include <vector>
using namespace std;

int binary_search_rec(vector<int> &arr,int low,int high,int key){
    while(low<=high){
        int mid = (high+low)/2;
        if(arr[mid] == key){
            cout << "key found at index:" << mid << endl;
            return 0;
        }
        else if(key<arr[mid]){
            return binary_search_rec(arr,low,mid-1,key);
        }
        else{
            return binary_search_rec(arr,mid+1,high,key);
        }

    }
    return 0;
}

void binary_search_iter(vector<int> &arr,int low,int high,int key){
    while(low<=high){
        int mid = (high+low)/2;
        if(arr[mid] == key){
            cout << "key found at index:" << mid << endl;
            return;
        }
        else if(key<arr[mid]){
            high = mid-1;
        }
        else{
            low = mid+1;
        }

    }
    cout << "key not found in the array" << endl;
}

void linear_search(vector<int> &arr,int key){
    for(int i=0;i<arr.size();i++){
        if(arr[i] == key){
            cout << "key found at index(using linear search):" << i << endl;
            return;
        }
    }
    cout << "key not found in the array" << endl;
}

void selection_sort(vector<int> &arr){
    int len = arr.size();
    for(int i =0;i<len-1;i++){
    int minpos = i;
    for(int j=i+1;j<len;j++){
        if(arr[j] < arr[minpos]){
            minpos = j;
        }
    }
    int temp = arr[minpos];
    arr[minpos] = arr[i];
    arr[i] = temp;
}}

void bubble_sort(vector<int>&arr){
    int len = arr.size();
    for(int i=0;i<len-1;i++){
        for(int j=0;j<len;j++){
            if(arr[j]>arr[j+1]){
                int temp = arr[j];
                arr[j+1] = arr[j];
                arr[j] = temp;
                
            }
        }
    }
}

void printArray(vector<int> &arr) {
    for (int &val : arr) {
        cout << val << " ";
    }
    cout << endl;
}


int main(){
    cout << "how many elements does the array have:";
    int n; 
    cin >> n;
    vector<int>arr(n);
    for(int i=0;i<n;i++){
        cout << "enter value of index" << i << ":";
        cin >> arr[i];
    }
    cout << "sorting using selection sort.." << endl;
    selection_sort(arr);
    printArray(arr);
    
    cout << "sorting using bubble sort.." << endl;
    bubble_sort(arr);
    printArray(arr);

    int low = 0;
    int high = arr.size()-1;
    cout << "which value to search:";
    int key;
    cin >> key;
    binary_search_rec(arr,low,high,key);
    binary_search_iter(arr,low,high,key);
    linear_search(arr,key);

    return 0;
}