#ifndef AVL_H
#define AVL_H

#include "BST.h"

class AVL
{
    public:
        AVL();
        ~AVL();

        void insert(char *);
        int search(char *);
        AVL* deletion(char *);
        AVL* findMinNode();
        void inorder();
        void preorder();
        void postorder();

    private:
        char *word;
        AVL* left;
        AVL* right;
        int counter;
        int height; 
        int newHeight(); 
        int balance; 
        int newBalance(); 

        void LeftRotation();
        void RightRotation();
};

#endif 
