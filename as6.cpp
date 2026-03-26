#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class knapsack{
    private:
    int n;
    vector<int> w;
    vector<int> p;
    int capacity;

    public:
    void accept();
    void display();
    void algo();
};

void knapsack::accept(){
    cout<<"Enter value of n\n";
    cin>>n;
    if(n <= 0){ cout<<"Invalid n\n"; return; }


    cout<<"Enter the capacity of knapsack\n";
    cin>>capacity;
    if(capacity <= 0){ cout<<"Invalid capacity\n"; return; }


    w.resize(n);
    p.resize(n);

    cout<<"Enter the weights\n";
    for(int i=0;i<n;i++)cin>>w[i];

    cout<<"Enter the profits\n";
    for(int i=0;i<n;i++)cin>>p[i];
}

void knapsack::display(){
    cout<<"Weights:\n";
    for(int i=0;i<n;i++)cout<<w[i]<<' ';
    cout<<endl;

    cout<<"Profits:\n";
    for(int i=0;i<n;i++)cout<<p[i]<<' ';
    cout<<endl;
}

void knapsack::algo(){
    vector<vector<int>> b(n+1, vector<int>(capacity+1, 0));
    
    for(int i=1; i<=n; i++){
        for(int c=1; c<=capacity; c++){
            if(w[i-1] <= c){
                b[i][c] = max(b[i-1][c], b[i-1][c - w[i-1]] + p[i-1]);
            }
            else{
                b[i][c] = b[i-1][c];
            }
        }
    }
    cout<<"Maximum profit: "<<b[n][capacity]<<endl;
}

int main(){
    knapsack k;
    k.accept();
    k.display();
    k.algo();
    return 0;
}
