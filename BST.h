#ifndef BST_H
#define BST_H

class BST
{
    public:
        BST();
        ~BST();

        void insert(char *);
        int search(char *);
        BST* deletion(char *);
        BST* findMinNode();
        void inorder();
        void preorder();
        void postorder();

    private:
        char *word; 
        int counter; 
        BST *left; 
        BST *right; 
};

#endif 
