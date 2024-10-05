#include "HashTable.h"
#include <cstring>
#include <iostream>

using namespace std;

HashTable::HashTable() 
{
    size=50000; 
    filled=0; 
    table=new char*[size]; 
    for (int i=0;i<size;i++) 
        table[i]=nullptr;
    counter=new int[size]; 
    for (int i=0;i<size;i++) 
        counter[i]=0;
}

HashTable::HashTable(int s) 
{                           

    size=s;
    filled=0;
    table=new char*[size];
    for (int i=0;i<size;i++)
        table[i]=nullptr;
    counter=new int[size];
    for (int i=0;i<size;i++)
        counter[i]=0;
}

HashTable::~HashTable() 
{
    delete []table;
    delete []counter;
}

int HashTable::hash(char *w,int i) 
{
    int c=31; 
    unsigned int h=0; 
    for (int j=0;w[j]!='\0';j++) 
        h=c*h+w[j]; 
    return (h+i*i)%size; 
}

void HashTable::insert(char *w)
{

    if (filled==size)  
        return;       
    int i=0,pos; 
    pos=hash(w,i); 
    while (table[pos]!=nullptr) 
    {
        if (strcmp(w,table[pos])==0) 
        {
            counter[pos]++;
            return;
        }
        i++; 
        pos=hash(w,i); 
    }

    table[pos]=new char[strlen(w)+1]; 
    strcpy(table[pos],w);
    counter[pos]=1; 
    filled++; 
}

int HashTable::search(char *w) 
{
    int i=0,pos; 
    pos=hash(w,i); 
    while (i<size) 
    {
        if (table[pos]==nullptr) 
            return 0;
        else if (strcmp(table[pos],w)==0) 
            return counter[pos];
        i++; 
        pos=hash(w,i); 
    }
    return 0; 
}

void HashTable::show() 
{
    for (int i=0;i<size;i++)
        if (table[i]!=nullptr)
            cout<<table[i]<<endl;
}
