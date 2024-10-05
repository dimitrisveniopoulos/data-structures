#include "AVL.h"
#include <cstring>
#include <iostream>
using namespace std;

AVL::AVL()
{
    word=nullptr;
    left=nullptr;
    right=nullptr;
    counter=0;
    height=0;
    balance=0;
}

AVL::~AVL()
{
    delete []word;
    word=nullptr;
}

int AVL::newHeight() 
{
    int L=-1,R=-1;
    if (left!=nullptr)
        L=left->height; 
    if (right!=nullptr)
        R=right->height;
    if (L>R)
        return L+1;
    else
        return R+1;
}

int AVL::newBalance()
{
    int L=0,R=0; 
    if (left!=nullptr)
        L=1+left->height; 
    if (right!=nullptr)
        R=1+right->height;
    return L-R;
}

void AVL::LeftRotation() 
{
     AVL *temp=this->right; 

    AVL* root_copy=new AVL;
    root_copy->word=new char [strlen(this->word)+1];
    strcpy(root_copy->word,this->word);
    root_copy->counter=this->counter;
    root_copy->left=this->left;
    root_copy->right=temp->left;

    delete []word; 
    this->word=new char[strlen(temp->word)+1];
    strcpy(this->word,temp->word);
    this->counter=temp->counter;

    this->right=temp->right;
    this->left=root_copy; 
    delete temp; 

    this->left->height=this->left->newHeight();
    this->height=newHeight();
}

void AVL::RightRotation()
{
    AVL *temp=this->left; 

    AVL* root_copy=new AVL;
    root_copy->word=new char [strlen(this->word)+1];
    strcpy(root_copy->word,this->word);
    root_copy->counter=this->counter;
    root_copy->right=this->right;
    root_copy->left=temp->right;

    delete []word; 
    this->word=new char[strlen(temp->word)+1]; 
    strcpy(this->word,temp->word);
    this->counter=temp->counter;

    this->left=temp->left; 
    this->right=root_copy;
    delete temp; 

    this->right->height=this->right->newHeight();
    this->height=newHeight();
}

void AVL::insert(char *w) 
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
            left=new AVL;
        left->insert(w);
    }
    else
    {
        if (right==nullptr)
            right=new AVL;
        right->insert(w);
    }
    height=newHeight(); 
    balance=newBalance(); 
    if (balance>1) 
    {
        if (strcmp(w,left->word)<0) 
                this->RightRotation(); 
        else if(strcmp(w,left->word)>0)
        {
            left->LeftRotation(); 
            this->RightRotation(); 
        }
    }
    else if (balance <-1)
    {
        if (strcmp(w,right->word)>0) 
            this->LeftRotation();
        else if (strcmp(w,right->word)<0) 
        {
            right->RightRotation();
            this->LeftRotation();
        }
    }
}
AVL* AVL::deletion(char *w)
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
            AVL *newChild=left;
            delete this;
            return newChild;
        }
        else if (left==nullptr)
        {
            AVL *newChild=right;
            delete this;
            return newChild;
        }
        else
        {
            AVL* temp=right->findMinNode();
            strcpy(word,temp->word);
            counter=temp->counter;
            right=right->deletion(temp->word);
            return this;
        }
    }

    height=newHeight(); 
    balance=newBalance(); 
    int b;
    if (balance>1) 
    {
        b=(left->balance=left->newBalance()); 
        if (b>=0) 
            this->RightRotation(); 
        else 
        {
            left->LeftRotation(); 
            this->RightRotation(); 
        }
    }
    else if (balance<-1) 
    {
        b=(right->balance=right->newBalance()); 
        if (b>0) 
        {
            right->RightRotation(); 
            this->LeftRotation(); 
        }
        else 
            this->LeftRotation(); 
    }
    return this;
}

int AVL::search(char *w)
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

AVL* AVL::findMinNode()
{
    AVL *min=this;
    while (min->left!=nullptr)
        min=min->left;
    return min;
}

void AVL::inorder()
{
    if(word==nullptr)
        return;
    if (left!=nullptr)
        left->inorder();
    cout<<word<<" height is "<<height<<endl;
    if (right!=nullptr)
        right->inorder();
}

void AVL::preorder()
{
    if(word==nullptr)
        return;
    cout<<word<<endl;
    if (left!=nullptr)
        left->preorder();
    if (right!=nullptr)
        right->preorder();
}

void AVL::postorder()
{
    if(word==nullptr)
        return;
    if (left!=nullptr)
        left->postorder();
    if (right!=nullptr)
        right->postorder();
    cout<<word<<endl;
}
