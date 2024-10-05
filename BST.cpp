#include "BST.h"
#include <cstring>
#include <iostream>
using namespace std;

BST::BST() 
{
    word=nullptr;
    left=nullptr;
    right=nullptr;
    counter=0;
}

BST::~BST() 
{
        delete []word;
        word=nullptr;
}

void BST::insert(char *w) 
{
    if (word==nullptr) 
    {
        word=new char[strlen(w)+1];
        strcpy(word,w);
        counter++;
        return;
    }
    int flag=strcmp(w,word); 
    if (flag==0) 
        counter++;
    else if (flag<0) 
    {
        if (left==nullptr) 
            left=new BST;
        left->insert(w); 
    }
    else 
    {
        if (right==nullptr) 
            right=new BST;
        right->insert(w); 
    }
}

int BST::search(char *w) 
{
    if (word==nullptr) 
        return 0;
    int flag=strcmp(w,word); 
    if (flag==0) 
        return counter;
    else if (flag<0) 
    {
        if (left!=nullptr)
            return left->search(w); 
    }
    else 
    {
        if (right!=nullptr)
            return right->search(w); 
    }
    return 0; 
}

BST* BST::deletion(char *w) 
{
    if (word==nullptr) 
           return nullptr;
    int flag=strcmp(w,word); 
    if (flag<0) 
    {
        if (left!=nullptr)
            left=left->deletion(w); 
    }
    else if (flag>0) 
    {
        if (right!=nullptr)
            right=right->deletion(w);
    }
    else 
    {
        if (left==nullptr && right==nullptr) 
        {
            delete this; 
            return nullptr;
        }
        else if (right==nullptr) 
        {
            BST *newChild=left; 
            delete this; 
            return newChild; 
        }
        else if (left==nullptr) 
        {
            BST *newChild=right; 
            delete this; 
            return newChild; 
        }
        else 
        {
            BST* temp=right->findMinNode(); 
            strcpy(word,temp->word); 
            counter=temp->counter;
            right=right->deletion(temp->word); 
            return this;                      
        }
    }
    return this;
}

BST* BST::findMinNode() 
{

    BST *min=this; 
    while (min->left!=nullptr) 
        min=min->left;        
    return min; 
}

void BST::inorder() 
{
    if(word==nullptr) 
        return;
    if (left!=nullptr) 
        left->inorder(); 
    cout<<word<<endl; 
    if (right!=nullptr) 
        right->inorder(); 
}

void BST::preorder() 
{                    
    if(word==nullptr)
        return;
    cout<<word<<endl;
    if (left!=nullptr)
        left->preorder();
    if (right!=nullptr)
        right->preorder();
}

void BST::postorder() 
{                    
    if(word==nullptr)
        return;
    if (left!=nullptr)
        left->postorder();
    if (right!=nullptr)
        right->postorder();
    cout<<word<<endl;
}
