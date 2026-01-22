#include <iostream>
using namespace std;

class sortings{
private:
public:

int bnry_search(vector<int> &a,int n,int key);
int r_bnry_search(vector<int> &a,int key,int high,int low);
void solve();
};

int sortings::bnry_search(vector<int> &a,int n,int key){
    int high=n-1;
    int low=0;

    int flag=0;
    int pos=0;
    while(high>=low){
        int mid=floor((low+high)/2);
        if(key==a[mid]){
            flag=1;
            pos=mid;
            break;
        }

        else if(key>a[mid]){
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    if(flag==0){
        return -1;
    }
    else{
        return pos;
    }
}

int sortings::r_bnry_search(vector<int> &a,int key,int high,int low){
    int mid=floor((high+low)/2);
    if(low>high){
        return -1;
    }

    if(a[mid]==key){
        return mid;
    }

    else if(key>mid){
        r_bnry_search(a,key,high,mid+1);
    }

    else{
        r_bnry_search(a,key,mid-1,low);
    }

    return -1;
}

void sortings::solve(){
    cout<<"Enter the length of the array\n";
    int n;
    cin>>n;
    
    int high=n-1;
    int low=0;

    cout<<"Enter the array\n";
    vector<int> a(n);
    for(int i=0;i<n;i++)cin>>a[i];

    cout<<"Enter the key you want to search now\n";
    int key;
    cin>>key;

    cout<<"iterative answer(if not found , answer will be -1) "<<bnry_search(a,n,key)<<endl;
    cout<<"recursive answer(if not found , answer will be -1) "<<r_bnry_search(a,key,high,low)<<endl;
}

int main(){
    sortings s;
    s.solve();
}