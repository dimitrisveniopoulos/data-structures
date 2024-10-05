#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <stdlib.h>
#include <chrono>
#include "BST.h"
#include "HashTable.h"
#include "AVL.h"
#define random_size 2000

using namespace std;

bool removeChars(char *str) 
{
    int count=0;
    for (int i=0;str[i]!='\0';i++)
        if (isupper(str[i]) || islower(str[i]))
            str[count++]=str[i];
    str[count]='\0';
    if (count>0) 
        return true;
    else
        return false;
}

int main()
{

    ifstream f;
    f.open("small-file.txt");
    if (f.is_open())
    {

        BST *bst=new BST;
        AVL *avl=new AVL;
        HashTable *htable=new HashTable;
        cout<<"Reading words from text file and inserting them to the data structures..."<<endl;
        char **Q; 
        Q=new char*[random_size];  
        char str[100]; 
        int count=0; 
        srand(time(0));
        while (!f.eof()) 
        {
            f>>str;
            if (removeChars(str))
            {

                bst->insert(str);
                avl->insert(str)
                htable->insert(str);
                if (count<random_size && rand()%31==0)
                {
                    Q[count]=new char[strlen(str)+1];
                    strcpy(Q[count],str);
                    count++;
                }
            }
        }
        f.close();
        cout<<"All words have been added to the data structures."<<endl<<"Initiating search..."<<endl;
        long long int bst_total_time=0,avl_total_time=0,htable_total_time=0;
        chrono::time_point<chrono::steady_clock> start,end;
        int times_found;
        for (int i=0;i<count;i++)
        {
            cout<<"----------------------------------------------"<<endl;
            start=chrono::steady_clock::now();
            times_found=bst->search(Q[i]);
            end=chrono::steady_clock::now();
            bst_total_time+=chrono::duration_cast<chrono::nanoseconds>(end-start).count();
            cout<<Q[i]<<" was found "<<times_found<<" times in BST"<<endl;
            start=chrono::steady_clock::now();
            times_found=avl->search(Q[i]);
            end=chrono::steady_clock::now();
            avl_total_time+=chrono::duration_cast<chrono::nanoseconds>(end-start).count();
            cout<<Q[i]<<" was found "<<times_found<<" times in AVL tree"<<endl;
            start=chrono::steady_clock::now();
            times_found=htable->search(Q[i]);
            end=chrono::steady_clock::now();
            htable_total_time+=chrono::duration_cast<chrono::nanoseconds>(end-start).count();
            cout<<Q[i]<<" was found "<<times_found<<" times in hash table"<<endl;
        }

        cout<<endl<<"Search completed."<<endl<<"Showing results..."<<endl;
        cout<<"Elapsed time for BST search: "<<bst_total_time<<" ns"<<endl;
        cout<<"Elapsed time for AVL tree search: "<<avl_total_time<<" ns"<<endl;
        cout<<"Elapsed time for hash table search: "<<htable_total_time<<" ns"<<endl;
    }
    else
        cout<<"File could not be opened!"<<endl;
    return 0;
}