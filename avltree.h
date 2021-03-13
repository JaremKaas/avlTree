#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED
#include <string>

template <typename Key,typename Info>
struct Node
    {
        Key key;
        Info info;

        int bfactor;
        Node<Key,Info> *left;
        Node<Key,Info> *right;

    };

template <typename Key,typename Info>
class Dictionary
{
    Node<Key,Info> *root;
    int size;


    int heightOfTree(Node<Key,Info> *temp)
    {
        if(!temp)
            return 0;
        else
            return 1 + max(heightOfTree(temp->left),heightOfTree(temp->right));
    }

    int max(int first,int second)
    {
        if(first>=second)
            return first;
        else
            return second;
    }

    Node<Key,Info>* findNode(const Key searchKey)
    {
        Node<Key,Info>* temp= root;
        while(temp)
        {
            if(temp->key==searchKey)
                return temp;
            else if(temp->key > searchKey)
                temp=temp->left;
            else
                temp=temp->right;
        }
        return temp;
    }


    void insertInto(Node<Key,Info> *&temp,Node<Key,Info> *&newNode,bool &ifAdded)
    {
        if(!temp)
        {
            temp=newNode;
            ifAdded=true;
            size++;
        }
        else if(temp->key>newNode->key) // add left
        {
            insertInto(temp->left,newNode,ifAdded);
            if(ifAdded)
            {
                switch(temp->bfactor)
                {
                case -1: // has been left high // need rotation
                    balanceFromLeft(temp);
                    ifAdded=false;
                    break;
                case 0: // has been perfect balance
                    temp->bfactor=-1;
                    ifAdded=true;
                    break;
                case 1: // has been right high
                    temp->bfactor=0;
                    ifAdded=false;
                }
            }
        }
        else
        {
            insertInto(temp->right,newNode,ifAdded);
            if(ifAdded)
            {
                switch(temp->bfactor)
                {
                case -1: // has been left high
                    temp->bfactor=0;
                    ifAdded=false;
                    break;
                case 0: // has been perfect balance
                    temp->bfactor=1;
                    ifAdded=true;
                    break;
                case 1: // has been right high // need rotation
                    balanceFromRight(temp);
                    ifAdded=false;
                }
            }
        }
    }

    void rotateToLeft(Node<Key,Info> *&root)
    {
        if(!root || !root->right) // no node to rotate
            return;
        else
        {
            Node<Key,Info> *temp;
            temp=root->right;
            root->right=temp->left;
            temp->left=root;
            root=temp;
        }
    }

    void rotateToRight(Node<Key,Info> *&root)
    {
        if(!root || !root->left) // no node to rotate
            return;
        else
        {
            Node<Key,Info> *temp;
            temp=root->left;
            root->left=temp->right;
            temp->right=root;
            root=temp;
        }
    }

    void balanceFromLeft(Node<Key,Info> *&root)
    {
        Node<Key,Info> *n;
        Node<Key,Info> *m;
        n=root->left;

        switch(n->bfactor)
        {
        case -1:
            root->bfactor = 0;
            n->bfactor=0;
            rotateToRight(root);
            break;
        case 1:  // double rotation
            m=n->right;
            switch(m->bfactor)
            {
            case -1:
                root->bfactor=1;
                n->bfactor=0;
                break;
            case 0:
                root->bfactor=0;
                n->bfactor=0;
                break;
            case 1:
                root->bfactor =0;
                n->bfactor=-1;
            }
            m->bfactor=0;
            rotateToLeft(n);
            root->left=n;
            rotateToRight(root);
        }
    }
    void balanceFromRight(Node<Key,Info> *&root)
    {
        Node<Key,Info> *n;
        Node<Key,Info> *m;
        n=root->right;

        switch(n->bfactor)
        {
        case -1: // double rotation
            m=n->left;
            switch(m->bfactor)
            {
            case -1:
                root->bfactor=0;
                n->bfactor=1;
                break;
            case 0:
                root->bfactor=0;
                n->bfactor=0;
                break;
            case 1:
                root->bfactor =-1;
                n->bfactor=0;
            }
            m->bfactor=0;
            rotateToRight(n);
            root->right=n;
            rotateToLeft(root);
            break;
        case 1:
            root->bfactor = 0;
            n->bfactor=0;
            rotateToLeft(root);
        }
    }

    void deleteAll(Node<Key,Info> *&temp)
    {
        if(temp)
        {
            deleteAll(temp->left);
            deleteAll(temp->right);
            delete temp;
            temp=nullptr;
            size--;
        }
    }

    void printInorder(Node<Key,Info> *temp)
    {
        if(temp)
        {
            printInorder(temp->left);
            std::cout<<"["<<temp->key<<","<<temp->info<<"]   ";
            printInorder(temp->right);
        }
    }

public:
    Dictionary() : root(nullptr), size(0) {}
    ~Dictionary()
        { deleteAll(root); }

    bool isEmpty()
        { return !root; }
    int getSize() const
        { return size; }

    void clear()
        { deleteAll(root);}

    int height()
        { return heightOfTree(root); }

    bool doesExist(Key searchKey)
    { return findNode(searchKey); }

    void insert(const Key &newKey, const Info &newInfo)
    {
        if(!doesExist(newKey))
        {
            Node<Key, Info> *newNode=new Node<Key,Info>;
            newNode->bfactor=0;
            newNode->info=newInfo;
            newNode->key=newKey;
            newNode->left=nullptr;
            newNode->right=nullptr;
            bool ifAdded =false;
            insertInto(root, newNode,ifAdded);
        }
    }

    void print()
    {
        printInorder(root);
        std::cout<<std::endl;
    }

    Info& operator[](Key index)
    {
        if(!root || doesExist(index)==false)
            insert(index,0);
        Node<Key,Info> *temp=findNode(index);
        return temp->info;
    }

};

#endif
