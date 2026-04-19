#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

class graph{
    
    public:
    int cost[10][10];
    int n;
    
    graph();
    void create();
    void display();
    void prims(int v);
};

graph :: graph(){
    
    cout << "enter total no of cities\n";
    cin >> n;
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cost[i][j]=999;
        }
    }
}

void graph :: create(){
    
    int c1,c2,d;
    char ch;
    do{
        cout << "enter pincodes of city you wanna connect and distance between them\n";
        cin >> c1 >> c2 >> d;
        
        if(cost[c1][c2]==999){
            cost[c1][c2]=d;
            cost[c2][c1]=d;
        }
        else{
            cout << "these two cities are alr connected\n";
        }
        
        cout << "do you wanna connect more cities?\n";
        cin >> ch;
        
    }while(ch=='Y' || ch=='y');;
}

void graph :: display(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << cost[i][j] << "\t";
        }
        cout << "\n";
    }
}

void graph :: prims(int v){
    
    int nearest[10], t[10][3];
    int r=0;
    int mincost=0;
    int min ,j;
    
    nearest[v]=-1;
    for(int i=0; i<n; i++){
        if(i!=v){
            nearest[i]=v;
        }
    }
    
    for(int i=1; i<n; i++){
        min = 999;
        
        for(int k=0; k<n; k++){
            if(nearest[k]!=-1 && cost[k][nearest[k]] < min){
                   j=k;
                   min=cost[k][nearest[k]];
            }
        }
        
        t[r][0]=nearest[j];
        t[r][1]=j;
        t[r][2]=min;
        r=r+1;
        
       mincost=mincost + cost[j][nearest[j]];
        nearest[j]=-1;
        
        for(int k=0; k<n ;k++){
           if(nearest[k]!=-1 && cost[k][nearest[k]] > cost[k][j])  {       
               nearest[k]=j;
               
           }
        }
    } 
        cout << "weight of MST : " << mincost <<endl;
        
        cout << "edges present in MST :\n";
        for(int i=0; i<n-1; i++){
            cout << t[i][0] << "->" << t[i][1] << "[" << t[i][2] << "]" << endl;
        }
        cout << "\n";
    }
    

    
    int main(){
        
    graph g;
  
    
    g.create();
    g.display();
    
    int v;
    cout << "enter start vertex \n";
    cin >> v;
    g.prims(v);
    
    return 0;
    
     
    
}