#ifndef HASHTABLE_H
#define HASHTABLE_H

class HashTable
{
    public:
        HashTable();
        HashTable(int);

        ~HashTable();
        void insert(char*);
        int search(char*);
        void show();

    private:
        char **table; 
        int *counter; 
        int size; 
        int filled; 
        int hash(char*,int); 
};

#endif 
