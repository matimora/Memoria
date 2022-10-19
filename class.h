#include <bits/stdc++.h>

using namespace std;


class Node{

  public:

    int t_min;
    int t_max;
    int t_excess;
    int t_ones;
    int t_numchunk;
    Node* parent;
    Node* left;
    Node* right;

};

class InternalNode : public Node {

  public:

    
    int t_min;
    int t_max;
    int t_excess;
    int t_ones;
    int t_numchunk;
    Node* left;
    Node* right;
    Node* parent;
     
    InternalNode();
  

    
  

};

class Block{

  
  public:

    
    char eti;
    vector <bool> vect;
    Node* leaf;
    Block* next;
    Block* prev;


    Block();
};

class Leaf : public Node {

  public:

    int t_min;
    int t_max;
    int t_excess;
    int t_ones;
    int t_numchunk;
    Block* block;
    Node *parent;
  
  
    Leaf();
   
  

};


class LinkedList{

  public:
    Block* head;
    Block* tail;
    LinkedList();
    void InsertBlock(Block*);
};