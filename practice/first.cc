#include <iostream>

using namespace std;

int main(){
    int x, total;
    total = 0;

    while(true){
       if(cin>>x){
        total += x;
       }
       else {
        if (cin.eof()) break;
        cin.clear();
        cin.ignore();
        }
       }
    cout<<"Total is:"<<total<<endl;
    return 0;
}