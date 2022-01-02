/*
    Testing method for testing list

    Written by - Mikiyas Worash & Mihret Teshale
*/
#include <iostream>
using namespace std;
#include "list.cpp"
int main() {
    List<int> list;
    list.insert(90);
    list.insert(20);
    list.insert(30);
    list.insert(40);
    list.insert(50);
    list.insert(25);
    list.insert(555);
    list.display();
    cout<<endl<<list.getCount();
    cout<<endl;
    list.remove(50);
    list.remove(20);
    list.display();
    cout<<endl<<list.getCount();
    cout<<endl;
    cout<<list.isEmpty()<<endl;
    cout<<endl;
    List<int> list2;
    list.copy(list2);
    list2.display();
    list2.insert(44);
    list2.insert(4899);
    list.insert(1);
    cout<<endl;
    list2.display();
    cout<<endl;
    list.display();

}
