/*
    Testing method for testing AVL

    Written by - Mikiyas Worash & Mihret Teshale
*/
#include <iostream>
using namespace std;
#include "AVL.cpp"
#include<cstring>
int main(){
    AVL t;
    dicIndex d1, d2, d3, d4;

    strcpy(d1.word, "Hello");
    d1.posList.insert(145);
    d1.posList.insert(4565);
    d1.posList.insert(788);

    strcpy(d2.word, "World");
    d2.posList.insert(234);

    strcpy(d3.word, "from");
    d3.posList.insert(2354);

    strcpy(d4.word, "mike");
    d4.posList.insert(274);
    d4.posList.insert(322);

    t.insert(d1);
    t.insert(d2);
    t.insert(d3);
    t.insert(d4);

    t.display();
    cout<<t.isEmpty();
    t.~AVL();
    cout<<endl;
    t.display();
    cout<<t.isEmpty();
}
