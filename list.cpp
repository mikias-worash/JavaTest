/*
    linked list pointer implementation using head and tail
    
    Written by - Mikiyas Worash & Mihret Teshale
*/
using namespace std;
//---------------------------------->List Class definition<-------------------------------------------------//

template <class T>
struct node {
    T data;
    node<T> * next;
};

template <class T>
class List {
    public:
        List(); //default constructor
        List(List<T> &L); //copy constructor
        virtual ~List(); //destructor
        bool isEmpty(){return head == nullptr;}
        void insert(T data);//insert always by tail
        void remove(T data);
        node<T>* find(T data);
        void empty();
        //virtual DList<T> * copy();
        void display();
        int getCount() {return count;}
        void copy(List<T> & dst);
        node<T> * getHead() {return head;}
    protected:
        node<T> * head;
        node<T> * tail;
        int count;
    private:
        bool nodeToDelete(T data, node<T>* &prev, node<T>* &cur);


};

//------------------------------------>List Class implementation<----------------------------------------//

template <class T>
List<T>::List() {
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template <class T>
List<T>::~List() {
    empty();
}

template <class T>
List<T>::List(List<T> &src) {
    node<T> * cur = src.head;
    head = nullptr;
    tail = nullptr;
    count = 0;
    while (cur != nullptr) {
        insert(cur->data);
        cur = cur->next;
    }
}

template <class T>
void List<T>::copy(List<T> &dst) {
    node<T> * cur = head;
    dst.head = nullptr;
    dst.tail = nullptr;
    count = 0;
    while (cur != nullptr) {
        dst.insert(cur->data);
        cur = cur->next;
    }

}

template <class T>
void List<T>:: insert(T data) {
    node<T>* p = new node<T>;
    if (p != nullptr) {
        p -> data = data;
        p -> next = nullptr;
        if(head == nullptr) {
            head = p;
            tail = p;
            count++;
        } else {
            tail->next = p;
            tail = p;
            count++;
        }
    }
}

template <class T>
void List<T>::display() {
    node<T>* cur = head;
    if (cur == nullptr) {
        cout<<"List is Empty!";
    }
    while (cur != nullptr) {
        cout << cur->data << "  ";
        cur = cur->next;
    }
}

template <class T>
bool List<T>::nodeToDelete(T data, node<T>* &prev, node<T>* &cur) {
    cur = head;
    prev = nullptr;
    while(cur != nullptr) {
        if (cur->data == data) {
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

template <class T>
void List<T>:: remove(T data) {
    node<T>* prev;
    node<T>* cur;
    if (nodeToDelete(data, prev, cur)) {
        prev->next = cur->next;
        delete cur;
        count--;
    }
}

template <class T>
node<T>* List<T>:: find(T data) {
    node<T>* cur = head;
    while(cur != nullptr) {
        if(cur->data == data) {
            return cur;
        }
        cur = cur->next;
    }
    return cur;
}

template <class T>
void List<T>:: empty() {
    node<T> * p;
    while(head != nullptr){
        p = head;
        head = head->next;
        delete p;
    }
    count = 0;
    tail = nullptr;
}


