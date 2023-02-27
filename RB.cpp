#include<iostream>
#include<deque>
using namespace std;

using Color = bool;
using KEY_TYPE = int;
using VALUE_TYPE = int;

static const Color red = false;
static const Color black = true;

class RBtree_node
{
    public:
    Color color;
    RBtree_node*parent;
    RBtree_node*right;
    RBtree_node*left;

    KEY_TYPE key;
    VALUE_TYPE val;
    RBtree_node(Color _color):right(NULL),left(NULL),color(_color){}
    RBtree_node(Color _color,RBtree_node*node,KEY_TYPE _key):right(node),left(node),key(_key){}
};

class RB
{
    private:
        RBtree_node*root; 
        RBtree_node*node; // ndoe is dummyhead
    public:

    RB()
    {
        node = new RBtree_node(black); //let all node be black
        root = node; // if root is NULL let root = node
    }
    void rightRotate(RBtree_node*root);

    void leftRotate(RBtree_node*root);

    void fixinsert(RBtree_node*root);

    void insert(KEY_TYPE key);

    void Delete(KEY_TYPE key);

    void fixDelete(RBtree_node*root);

    void printf();

    void printMid(RBtree_node*root);

    RBtree_node*successor(RBtree_node * root);

    RBtree_node*searchNode(KEY_TYPE key);

};

void RB::rightRotate(RBtree_node*root_node)
{
    RBtree_node*temp = root_node -> left; 
    root_node -> left = temp -> right;  

    if(temp -> right != node) // the changed leafnode not point to dummyhead
        temp -> right -> parent = temp; //let the origin root'parent pointing to temp 
    temp -> right = root_node;

    if(root_node == root)
    {
        root = temp; // root point to temp
    }
    else if(root_node -> parent -> right = root_node)
    {
        root_node -> parent -> right = temp; //dummyhead's right point to temp   
    }
    else
    {
        root_node -> parent -> left = temp; //dummyhead's right point to temp
    }

    root_node -> parent = temp;//let previous root's parent is current root
    temp -> right = root_node; // let current root's right is previous root 
}

void RB::leftRotate(RBtree_node*left_node)
{
    RBtree_node*right_node = left_node -> right;

    left_node -> right = right_node -> left;

    if(right_node -> left != node)
        right_node-> left -> parent = right_node; // let the origin root pointing to right_node(current root)
    
    if(left_node == root)
    {
        root = right_node;
    }
    else if(left_node -> parent -> left = left_node)
    {
        left_node -> parent -> left = right_node;
    }
    else
    {
        left_node -> parent -> right = right_node;
    }

    left_node -> parent = right_node;
    right_node -> left = left_node;
}

void RB::insert(KEY_TYPE key)
{
    RBtree_node *prev = node; 
    RBtree_node *cur = root;
    while(cur != node)//to find the insert position
    {
        prev = cur;
        if(cur -> key > key)
            cur = cur -> left;
        else if (cur -> key < key)
            cur = cur -> right;
        else
            return; //the tree_key is the same with new key 
    }
    RBtree_node* new_node = new RBtree_node(red, new_node, key); //creat a new node 
    new_node -> parent = prev; 

    if(prev = node) // if tree is NULL new_node is root 
        root = new_node;
    else if(prev -> key > key) 
        prev -> left = new_node;// let prev linked to new_node
    else if(prev -> key < key)
        prev -> right = new_node;
    fixinsert(new_node); //check is RB_tree
    printf();
}

void RB::fixinsert(RBtree_node*new_node)
{
    while(new_node -> parent -> color == red)//if parent is black that the while is breaked
    {
        if(new_node -> parent == new_node -> parent -> parent ->left)//the new_node and its parent in the left
        {
            RBtree_node *uncle = new_node -> parent -> parent -> right;
            if(uncle -> color == red) //if uncle is red
            {
                uncle -> color = black;
                new_node -> parent -> color = black; //let uncle and parent become black
                new_node -> parent -> parent -> color = red; 
                new_node = new_node -> parent -> parent;
            }
            else //if uncle is black
            {
                if(new_node == new_node -> parent -> right)//if new_node in the rightside change to leftside
                {
                    new_node = new_node -> parent;
                    leftRotate(new_node);
                }
                new_node -> parent -> color = black;
                new_node -> parent -> parent -> color = red;
                rightRotate(new_node -> parent -> parent);
            }
        }
        else
        {
            RBtree_node *uncle = new_node -> parent -> parent -> left;
            if(uncle -> color == red)
            {
                uncle -> color = black;
                new_node -> parent -> color = black;
                new_node -> parent -> parent -> color = red;
                new_node = new_node -> parent;
            }
            else
            {
                if(new_node == new_node -> parent -> left)
                {
                    new_node = new_node -> parent;
                    rightRotate(new_node);
                }
                    new_node -> parent -> color = black;
                    new_node -> parent -> parent -> color= red;
                    leftRotate(new_node -> parent -> parent);
            }
        }
    }
    root -> color = black;
}

RBtree_node*RB::searchNode(KEY_TYPE key)
{
    RBtree_node*cur = root;    
    while(root != node)
    {
        if(cur -> val > key)
        {
            cur = cur -> left;
        }
        else if(cur -> val < key)
        {
            cur = cur -> left;
        }
        else
        {
            return;
        }
    }
    return cur;
}

RBtree_node*RB::successor(RBtree_node * trs)
{
    if(trs -> right != node) //trs have right children
    {
        RBtree_node *res = trs -> right; //find the smallest in rightside
        while(res -> left!= node)
        {
            res = res -> left ;
        }
        return res;
    }
    else //trs not have right children
    {
        while(trs != root && trs != trs -> parent -> left)
        {
            trs = trs -> parent;
        }
        return trs -> parent;
    }

}

void RB::Delete(KEY_TYPE key)
{
    RBtree_node *key_node = searchNode(key);
    RBtree_node *delete_node = NULL; //(it is not key, it is the key'children smallest node)
    RBtree_node *delete_son = NULL; //(it is the node delete node 's children)
    
    if(key_node -> right != node && key_node -> left != node)
    {
        delete_node = successor(key_node); // the smallest node
        delete_son = delete_node -> right; //it is NULL
    }
    else //if only one side or both all null it is key_node(who i want to delete)
    {
        delete_node = key_node; //delete_node is key_node
        if(key_node -> left != node)
        {
            delete_son = key_node -> left;
        }
        else
        {
            delete_son = key_node -> right;
        }
    }
    
    delete_son -> parent = delete_node -> parent; //connect grandpa and son

    if(delete_node == root) 
    {
        root = delete_son;
    }
    else if(delete_node == delete_node -> parent -> left)
    {
        delete_son = delete_node -> parent -> left;
    }
    else
    {
        delete_son = delete_node -> parent -> right;
    }

    key_node -> key = delete_node -> key;
    key_node -> val = delete_node -> val; //cover the key_node with delete_node

    if(delete_node -> color == black) // less the one black 
    {
        fixDelete(delete_son);
    }

    delete delete_node;
    printf();
}

void RB::fixDelete(RBtree_node*delete_son)
{
    while(delete_son != root && delete_son -> color == black) //delete_son is black
    {
        if(delete_son == delete_son -> parent -> left) // delete_son is in the left side
        {
            RBtree_node*delete_bro = delete_son -> parent -> right; //bro is son another side
            //1. bro is red
            if(delete_bro -> color == red) //son in left side if bro is red 1. bro -> black 2. parent -> red 3. leftrotate 4.bro -> bro -> right
            {
                delete_bro -> color = black;      
                delete_son -> parent -> color = red;
                leftRotate(delete_son -> parent);
                delete_bro = delete_son -> parent -> right;
            }
            
            // 2. bor is black and right side one more than left side with black node
            if(delete_bro -> right -> color == black && delete_bro -> left -> color == black)
            {
                delete_bro -> color = red;
                delete_son = delete_son -> parent;
            }
            if(delete_bro -> right -> color == black)   //to become left black right red
            {
                delete_bro -> color = red;
                delete_bro -> left -> color = black;
                rightRotate(delete_bro);
            }
            else 
            {
                delete_bro -> color = delete_bro -> parent -> color; 
                delete_bro -> parent -> color = black;
                delete_bro -> right -> color = black;
                leftRotate(delete_son -> parent);
                delete_son = root; // stop
            }
        }
        else
        {
            RBtree_node*bro = delete_son -> parent -> left;
            if(bro -> color == red)
            {
                bro -> color = black;
                delete_son -> parent -> color = red;
                rightRotate(delete_son -> parent);
                bro = delete_son -> parent -> left;
            }

            if(bro -> right -> color == black && bro -> left -> color == black)
            {
                bro -> color = red;
                delete_son = delete_son -> parent;
            }

            if(bro -> left -> color == black)
            {
                bro -> color = red;
                bro -> right -> color = black;
                leftRotate(bro -> parent);
            }
            else
            {
                bro -> color = bro -> parent -> color;
                bro -> parent -> color = black;
                bro -> left -> color = black;
                rightRotate(delete_son -> parent);
                delete_son = root; //stop
            }
        }
    }
    delete_son -> color = black;
}

void RB::printf()
{
    std::deque<RBtree_node*>deque;
    deque.push_back(root);
    while(!deque.empty())
    {
        int size = deque.size();
        for(int i = 0; i < size; i++)
        {
            RBtree_node*temp = deque.front();
            deque.pop_front();
            if(temp -> left != NULL)
                deque.push_back(temp -> left);
            if(temp -> right != NULL)
                deque.push_back(temp -> right);
            std::string color = temp -> color? "b:":"r:";
            std::string key = temp == NULL?"dummyhead":std::to_string(temp -> key);
            std::cout<<color<<key<<" ";
        }
        std::cout<<endl;
    }
    
}

void RB::printMid(RBtree_node*root)
{
    if(root == NULL)
        return;
    if(root -> left)
        printMid(root -> left);
    std::string color = root -> color ?"b":"r";
    std::cout<<color<<std::to_string(root -> key)<<" ";
    if(root -> right)
        printMid(root -> right);
}
