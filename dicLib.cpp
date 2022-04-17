#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <conio.h>
#include <cstring>
#include "AVL.cpp"
using namespace std;

struct dictionary
{
    char word[50];
    char pron[60];
    char type[4];
    char meaning[200];
};

AVL avl;

void initialize()
{
    ifstream reader;
    dictionary dic;
    int filePointer;
    reader.open("dic.bin", ios::in);
    if (!reader.fail())
    {
        while (reader.peek() != EOF)
        {
            dicIndex indx;
            filePointer = reader.tellg();
            reader.read((char *)&dic, sizeof(dic));
            strcpy(indx.word, dic.word);
            indx.posList.insert(filePointer);
            avlNode *p = avl.search(indx);
            if (p == nullptr)
            {
                if (strcmp(dic.word, "") != 0)
                {
                    avl.insert(indx);
                }
            }
            else
            {
                p->data.posList.insert(filePointer);
            }
        }
        reader.close();
    }
    else
    {
        cout << "\nNo Records added yet!\nAdd Records on the menu after pressing a key\n\n";
        system("pause");
    }
}

void addRecord()
{
    dicIndex indx;
    dictionary dic;
    int filePointer;
    cout << setfill('+') << setw(20) << "\n";
    cout << "  Adding Record\n";
    cout << setfill('+') << setw(20) << "\n\n";
    cout << "Enter word: ";
    cin >> dic.word;
    cout << "Enter type: ";
    cin >> dic.type;
    cin.ignore();
    cout << "Enter pronounciation: ";
    cin.getline(dic.pron, 59);
    cout << "Enter meaning: ";
    cin.getline(dic.meaning, 199);

    ofstream writer;
    writer.open("dic.bin", ios::binary | ios::app);
    filePointer = writer.tellp();
    writer.write((char *)&dic, sizeof(dic));
    strcpy(indx.word, dic.word);
    indx.posList.insert(filePointer);
    avlNode *p = avl.search(indx);
    if (p == nullptr)
    {
        //if not found search again by changing case of first letter
        if (indx.word[0] >= 'A' && indx.word[0] <= 'Z')
        {
            indx.word[0] += 32;
        }
        else
        {
            indx.word[0] -= 32;
        }
        p = avl.search(indx);
        //reverse case of first letter to original case
        if (indx.word[0] >= 'A' && indx.word[0] <= 'Z')
        {
            indx.word[0] += 32;
        }
        else
        {
            indx.word[0] -= 32;
        }
    }
    if (p == nullptr)
    {
        avl.insert(indx);
        cout << "\nNew record Added!\n\n";
        system("pause");
    }
    else
    {
        p->data.posList.insert(filePointer);
        cout << "\nRecord Updated!\n\n";
        system("pause");
    }
    writer.close();
    avl.~AVL();
    initialize();
}

void removeRecord()
{
    dicIndex indx;
    dictionary dic;
    int filePointer;
    cout << setfill('-') << setw(20) << "\n";
    cout << "  Removing Record\n";
    cout << setfill('-') << setw(20) << "\n\n";
    cout << "Enter word: ";
    cin >> dic.word;
    strcpy(indx.word, dic.word);
    avlNode *p = avl.search(indx);
    if (p == nullptr)
    {
        if (indx.word[0] >= 'A' && indx.word[0] <= 'Z')
        {
            indx.word[0] += 32;
        }
        else
        {
            indx.word[0] -= 32;
        }
        p = avl.search(indx);
    }
    if (p == nullptr)
    {
        cout << "Record not found!\n";
        system("pause");
    }
    else
    {
        fstream f;
        node<int> *cur;
        int count = p->data.posList.getCount();
        f.open("dic.bin", ios::in | ios::binary | ios::out);
        if (!f.fail())
        {
            if (count == 1)
            {
                cur = p->data.posList.getHead();
                filePointer = cur->data;
                f.seekp(filePointer);
                strcpy(dic.word, "");
                strcpy(dic.type, "");
                strcpy(dic.pron, "");
                strcpy(dic.meaning, "");
                f.write((char *)&dic, sizeof(dic));
                avl.remove(p->data);
                cout << "Record Deleted\n";
                f.close();
                system("pause");
            }
            else
            {
                cout << "Many types found with this word '" << p->data.word << "'" << endl;
                cout << "Do you want to delete all associated records?";
                cout << "\nEnter 'y' to delete all or 'any key' to delete a specific type" << endl;
                char res;
                cin >> res;
                if (res == 'y' || res == 'Y')
                {
                    f.close();
                    int i = 0;
                    cur = p->data.posList.getHead();
                    while (i < count)
                    {
                        f.open("dic.bin", ios::in | ios::binary | ios::out);
                        filePointer = cur->data;
                        f.seekp(filePointer);
                        strcpy(dic.word, "");
                        strcpy(dic.type, "");
                        strcpy(dic.pron, "");
                        strcpy(dic.meaning, "");
                        f.write((char *)&dic, sizeof(dic));
                        cur = cur->next;
                        i++;
                        f.close();
                    }
                    avl.remove(p->data);
                    cout << "All associated Records Deleted\n";
                    f.close();
                    system("pause");
                }
                else
                {
                    f.close();
                    cout << "Enter the specific type of word\n";
                    char typ[4];
                    cin >> typ;
                    int position = -1;
                    ifstream readerPos;
                    int i = 0;
                    cur = p->data.posList.getHead();
                    while (i < count)
                    {
                        readerPos.open("dic.bin", ios::binary | ios::in);
                        filePointer = cur->data;
                        readerPos.seekg(filePointer);
                        readerPos.read((char *)&dic, sizeof(dic));
                        if (strcmp(typ, dic.type) == 0)
                        {
                            position = filePointer;
                            break;
                        }
                        cur = cur->next;
                        i++;
                        readerPos.close();
                    }
                    if (position == -1)
                    {
                        cout << "No such type found with this word!\n";
                        system("pause");
                    }
                    else
                    {
                        f.open("dic.bin", ios::in | ios::binary | ios::out);
                        f.seekp(position);
                        strcpy(dic.word, "");
                        strcpy(dic.type, "");
                        strcpy(dic.pron, "");
                        strcpy(dic.meaning, "");
                        f.write((char *)&dic, sizeof(dic));
                        p->data.posList.remove(position);
                        cout << "Record Deleted\n";
                        f.close();
                        system("pause");
                    }
                }
            }
        }
        else
        {
            cout << "File could not be opened!\n";
            system("pause");
        }
    }
}

void editRecord()
{
    dicIndex indx;
    dictionary dic;
    int filePointer;
    cout << setfill('+') << setw(20) << "\n";
    cout << "  Editing Record\n";
    cout << setfill('+') << setw(20) << "\n\n";
    cout << "Enter word: ";
    cin >> dic.word;
    strcpy(indx.word, dic.word);
    avlNode *p = avl.search(indx);
    if (p == nullptr)
    {
        if (indx.word[0] >= 'A' && indx.word[0] <= 'Z')
        {
            indx.word[0] += 32;
        }
        else
        {
            indx.word[0] -= 32;
        }
        p = avl.search(indx);
    }
    if (p == nullptr)
    {
        cout << "Record not found!\n";
        system("pause");
    }
    else
    {
        fstream f;
        node<int> *cur;
        int count = p->data.posList.getCount();
        f.open("dic.bin", ios::in | ios::binary | ios::out);
        if (!f.fail())
        {
            if (count == 1)
            {
                cur = p->data.posList.getHead();
                filePointer = cur->data;
                f.seekp(filePointer);
                cout << "Enter new data for the word '" << p->data.word << "'" << endl;
                cout << "Enter type: ";
                cin >> dic.type;
                cin.ignore();
                cout << "Enter pronounciation: ";
                cin.getline(dic.pron, 59);
                cout << "Enter meaning: ";
                cin.getline(dic.meaning, 199);
                f.write((char *)&dic, sizeof(dic));
                cout << "Record Edited\n";
                f.close();
                system("pause");
            }
            else
            {
                f.close();
                cout << "Many types found with this word '" << p->data.word << "'" << endl;
                cout << "Enter the specific type of word\n";
                char typ[4];
                cin >> typ;
                int position = -1;
                ifstream readerPos;
                int i = 0;
                cur = p->data.posList.getHead();
                while (i < count)
                {
                    readerPos.open("dic.bin", ios::binary | ios::in);
                    filePointer = cur->data;
                    readerPos.seekg(filePointer);
                    readerPos.read((char *)&dic, sizeof(dic));
                    if (strcmp(typ, dic.type) == 0)
                    {
                        position = filePointer;
                        break;
                    }
                    cur = cur->next;
                    i++;
                    readerPos.close();
                }
                if (position == -1)
                {
                    cout << "No such type found with this word!\n";
                    system("pause");
                }
                else
                {
                    f.open("dic.bin", ios::in | ios::binary | ios::out);
                    f.seekp(position);
                    cout << "Enter new data for the word '" << p->data.word << "'" << endl;
                    cout << "Enter type: ";
                    cin >> dic.type;
                    cin.ignore();
                    cout << "Enter pronounciation: ";
                    cin.getline(dic.pron, 59);
                    cout << "Enter meaning: ";
                    cin.getline(dic.meaning, 199);
                    f.write((char *)&dic, sizeof(dic));
                    cout << "Record Edited\n";
                    f.close();
                    system("pause");
                }
            }
        }
        else
        {
            cout << "File could not be opened!\n";
            system("pause");
        }
    }
}

void searchRecord()
{
    dicIndex indx;
    dictionary dic;
    int filePointer;
    cout << setfill('<') << setw(20) << "\n";
    cout << "  Search Record\n";
    cout << setfill('>') << setw(20) << "\n\n";
    cout << "Enter word: ";
    cin >> dic.word;
    strcpy(indx.word, dic.word);
    avlNode *p = avl.search(indx);
    if (p == nullptr)
    {
        if (indx.word[0] >= 'A' && indx.word[0] <= 'Z')
        {
            indx.word[0] += 32;
        }
        else
        {
            indx.word[0] -= 32;
        }
        p = avl.search(indx);
        if (indx.word[0] >= 'A' && indx.word[0] <= 'Z')
        {
            indx.word[0] += 32;
        }
        else
        {
            indx.word[0] -= 32;
        }
    }
    if (p == nullptr)
    {
        cout << "Record not found!\n";
        system("pause");
    }
    else
    {
        ifstream reader;
        int count = p->data.posList.getCount();
        reader.open("dic.bin", ios::binary | ios::in);
        if (!reader.fail())
        {
            node<int> *cur;
            int j;
            for (int i = 0; i < 4; i++)
            {
                cur = p->data.posList.getHead();
                j = 0;
                while (j < count)
                {
                    filePointer = cur->data;
                    reader.seekg(filePointer);
                    reader.read((char *)&dic, sizeof(dic));
                    if (i == 0 && strcmp(dic.type, "n") == 0 || i == 1 && strcmp(dic.type, "v") == 0 || i == 2 && strcmp(dic.type, "adj") == 0 || i == 3 && strcmp(dic.type, "adv") == 0)
                    {
                        cout << endl;
                        cout << "Word: " << dic.word << endl;
                        cout << "Type: " << dic.type << endl;
                        cout << "Pron: " << dic.pron << endl;
                        cout << "Meaning: " << dic.meaning << endl
                             << endl;
                    }
                    cur = cur->next;
                    j++;
                }
            }

            system("pause");
        }
        reader.close();
    }
}

void displayAll()
{
    cout << setfill('*') << setw(25) << "\n";
    cout << "  List of Records\n";
    cout << setfill('*') << setw(25) << "\n\n";
    ifstream reader;
    dictionary dic;
    reader.open("dic.bin", ios::in);
    if (!reader.fail())
    {
        while (reader.peek() != EOF)
        {
            reader.read((char *)&dic, sizeof(dic));
            if (strcmp(dic.word, "") != 0)
            {
                cout << "Word: " << dic.word << endl;
                cout << "Type: " << dic.type << endl;
                cout << "Pron: " << dic.pron << endl;
                cout << "Meaning: " << dic.meaning << endl
                     << endl;
            }
        }
        system("pause");
        reader.close();
    }
    else
    {
        cout << "Record is Empty!\n";
        system("pause");
    }
}

void inorder()
{
    cout << setfill('^') << setw(28) << "\n";
    cout << "  Inorder traversal of AVL\n";
    cout << setfill('^') << setw(28) << "\n\n";
    cout << "Words\t\tList of references\n";
    cout << setfill('-') << setw(35) << "\n";
    avl.display();
    cout << endl
         << endl;
    system("pause");
}

void menu()
{
    initialize();
    int choice;
    do
    {
        system("cls");
        cout << setfill('*') << setw(49) << "\n";
        cout << setfill(' ') << setw(35) << "Dictionary Application\n";
        cout << setfill('*') << setw(50) << "\n\n";

        cout << "\t1. Add Record\n";
        cout << "\t2. Remove Record\n";
        cout << "\t3. Edit Record\n";
        cout << "\t4. Search for Record\n";
        cout << "\t5. Display All Records\n";
        cout << "\t6. Display Tree\n\n";
        cout << "\t0. Exit Applicaton\n\n";
        cout << setfill('-') << setw(14) << "\n";
        cout << "Enter Choice: ";
        cin >> choice;
        system("cls");

        switch (choice)
        {
        case 1:
            addRecord();
            break;
        case 2:
            removeRecord();
            break;
        case 3:
            editRecord();
            break;
        case 4:
            searchRecord();
            break;
        case 5:
            displayAll();
            break;
        case 6:
            inorder();
            break;
        default:
            if (choice != 0)
            {
                cout << "\n\tInvalid choice!\n\tTry again\n\n";
                system("pause");
            }
            break;
        }
    } while (choice != 0);

    cout << "\n\tApplication Closed!  GoodBye!\n\n";
}
