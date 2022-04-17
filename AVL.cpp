#include "list.cpp"
#include <cstring>
#include <iostream>

//---------------------------------->Class definition<-------------------------------------------------//

struct dicIndex
{
    char word[50];
    List<int> posList;
};

struct avlNode
{
    dicIndex data;
    int height;
    avlNode *left;
    avlNode *right;
};

class AVL
{
public:
    AVL();          //default constructor
    AVL(AVL &avl);  //copy constructor
    virtual ~AVL(); //destructor
    bool isEmpty() { return root == nullptr; }
    void inorder();
    void insert(dicIndex data);   //uses insert private
    void remove(dicIndex target); //uses remove private
    void display();               //uses inorder private
    avlNode *search(dicIndex data);

protected:
private:
    avlNode *root;
    int height(avlNode *n);
    avlNode *singleRightRotate(avlNode *n);
    avlNode *doubleRightRotate(avlNode *n);
    avlNode *singleLeftRotate(avlNode *n);
    avlNode *doubleLeftRotate(avlNode *n);
    int getBalance(avlNode *n);
    avlNode *insert(dicIndex data, avlNode *avlRoot);
    avlNode *remove(dicIndex data, avlNode *avlRoot);
    void inorder(avlNode *avlRoot);
    void copy(avlNode *src, avlNode *&dst);
    avlNode *makeEmpty(avlNode *t);
    avlNode *findMin(avlNode *r);
    avlNode *findMax(avlNode *r);
    int max(int a, int b) { return (a > b) ? a : b; }
    avlNode *search(dicIndex data, avlNode *t);
};

//------------------------------------>Class implementation<----------------------------------------//

AVL::AVL()
{
    root = nullptr;
}

AVL::AVL(AVL &avl)
{
    copy(root, avl.root);
}

void AVL::copy(avlNode *src, avlNode *&dst)
{
    avlNode *p;
    if (src == NULL)
    {
        dst = NULL;
    }
    else
    {
        p = new avlNode;
        p->data = src->data;
        p->left = p->right = NULL;
        dst = p;
        copy(src->left, dst->left);
        copy(src->right, dst->right);
    }
}

AVL::~AVL()
{
    root = makeEmpty(root);
}

avlNode *AVL::makeEmpty(avlNode *t)
{

    if (t == NULL)
    {
        return NULL;
    }
    else
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    return NULL;
}

void AVL::inorder()
{
    inorder(root);
}

void AVL::inorder(avlNode *t)
{
    if (t == NULL)
    {
        return;
    }
    else
    {
        inorder(t->left);
        cout << t->data.word << "\t\t";
        t->data.posList.display();
        cout << endl;
        inorder(t->right);
    }
}

void AVL::display()
{
    inorder(root);
}

void AVL::insert(dicIndex data)
{
    root = insert(data, root);
}

void AVL::remove(dicIndex data)
{
    root = remove(data, root);
}

avlNode *AVL::insert(dicIndex data, avlNode *avlRoot)
{
    if (avlRoot == NULL)
    {
        avlRoot = new avlNode;
        strcpy(avlRoot->data.word, data.word);
        data.posList.copy(avlRoot->data.posList);
        avlRoot->left = avlRoot->right = NULL;
        avlRoot->height = 1;
    }

    else if (strcmp(data.word, (avlRoot->data).word) == -1)
        avlRoot->left = insert(data, avlRoot->left);
    else if (strcmp(data.word, (avlRoot->data).word) == 1)
        avlRoot->right = insert(data, avlRoot->right);
    else
        return avlRoot;

    avlRoot->height = 1 + max(height(avlRoot->left), height(avlRoot->right));

    int balance = getBalance(avlRoot);

    // Left Left Case
    if (balance > 1 && strcmp(data.word, (avlRoot->left->data).word) == -1)
        return doubleLeftRotate(avlRoot);

    // Left Right Case
    if (balance > 1 && strcmp(data.word, (avlRoot->left->data).word) == 1)
        return singleLeftRotate(avlRoot);

    // Right Right Case
    if (balance < -1 && strcmp(data.word, (avlRoot->right->data).word) == 1)
        return doubleRightRotate(avlRoot);

    // Right Left Case
    if (balance < -1 && strcmp(data.word, (avlRoot->right->data).word) == -1)
        return singleRightRotate(avlRoot);

    return avlRoot;
}

avlNode *AVL::doubleLeftRotate(avlNode *n)
{
    avlNode *x = n->left;
    avlNode *y = x->right;

    x->right = n;
    n->left = y;

    n->height = max(height(n->left), height(n->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

avlNode *AVL::doubleRightRotate(avlNode *n)
{
    avlNode *x = n->right;
    avlNode *y = x->left;

    x->left = n;
    n->right = y;

    n->height = max(height(n->left), height(n->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

avlNode *AVL::singleLeftRotate(avlNode *n)
{
    n->left = doubleRightRotate(n->left);
    return doubleLeftRotate(n);
}

avlNode *AVL::singleRightRotate(avlNode *n)
{
    n->right = doubleLeftRotate(n->right);
    return doubleRightRotate(n);
}

int AVL::getBalance(avlNode *n)
{
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

int AVL::height(avlNode *n)
{
    if (n == NULL)
        return 0;
    return n->height;
}

avlNode *AVL::findMin(avlNode *r)
{
    if (r == NULL)
        return NULL;
    else if (r->left == NULL)
        return r;
    else
        return findMin(r->left);
}

avlNode *AVL::findMax(avlNode *r)
{
    if (r == NULL)
        return NULL;
    else if (r->right == NULL)
        return r;
    else
        return findMin(r->right);
}

avlNode *AVL::remove(dicIndex data, avlNode *avlRoot)
{
    if (avlRoot == NULL)
        return avlRoot;
    if (strcmp(data.word, avlRoot->data.word) == -1)
        avlRoot->left = remove(data, avlRoot->left);
    else if (strcmp(data.word, avlRoot->data.word) == 1)
        avlRoot->right = remove(data, avlRoot->right);
    else
    {
        if ((avlRoot->left == NULL) || (avlRoot->right == NULL))
        {
            avlNode *temp = avlRoot;
            if (avlRoot->left == NULL)
                avlRoot = avlRoot->right;
            else if (avlRoot->right == NULL)
                avlRoot = avlRoot->left;
            delete temp;
        }
        else
        {
            avlNode *temp = findMin(avlRoot->right);
            avlRoot->data = temp->data;
            avlRoot->right = remove(temp->data, avlRoot->right);
        }
    }

    if (avlRoot == NULL)
        return avlRoot;

    avlRoot->height = 1 + max(height(avlRoot->left), height(avlRoot->right));

    int balance = getBalance(avlRoot);

    // Left Left Case
    if (balance > 1 && strcmp(data.word, avlRoot->left->data.word) == -1)
        return doubleLeftRotate(avlRoot);

    // Left Right Case
    if (balance > 1 && strcmp(data.word, avlRoot->left->data.word) == 1)
        return singleLeftRotate(avlRoot);

    // Right Right Case
    if (balance < -1 && strcmp(data.word, avlRoot->right->data.word) == 1)
        return doubleRightRotate(avlRoot);

    // Right Left Case
    if (balance < -1 && strcmp(data.word, avlRoot->right->data.word) == -1)
        return singleRightRotate(avlRoot);

    return avlRoot;
}

avlNode *AVL::search(dicIndex data)
{
    return search(data, root);
}

avlNode *AVL::search(dicIndex data, avlNode *t)
{
    if (t == NULL)
        return NULL;
    else if (strcmp(data.word, t->data.word) == 0)
    {
        return t;
    }
    else if (strcmp(data.word, t->data.word) == -1)
    {
        return search(data, t->left);
    }
    else
    {
        return search(data, t->right);
    }
}
