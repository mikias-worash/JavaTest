# Dictionary app

# Features

    - Add new records
    - Search for records
    - Update records
    - Remove records

- It has a Dictionary file containing words together with their type, pronounce and meaning with a binary format.

- It uses self balancing binary search tree (avl) to hold the data in memory

- To make the application uses memory efficiently only the word and its associated reference on the file are stored in the tree.

- As a word can have more than one type and meaning the data part is a structure composed of the word and linked list of references(used a single linked list with head and tail implementation) for each dictionary record for that word

The dictionary record is specified by the following structure

        struct dictionary{
            char word[50];
            char pron[60]; //pronunciation
            char type[4];
            char meaning[200];
        }

An index to dictionary file is specified by the following structure

        struct dicIndex{
            char word[50];
            list posList;   // list of position(references) of record on the file
        }

            //  Where list is a single linked list with head and tail implementation
