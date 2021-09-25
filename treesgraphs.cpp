#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <vector>

using namespace std;


//binary tree - at most two children per node
//binary search tree - left child must be <= right child must be >

//balanced tree: left and right subtree of any node must differ by no more than one

// full and complete - all leaves are at the bottom and non leaf nodes have two children (2^n-1 nodes exactly required)


//in-order(most common), post-order, pre-order traversal

//tries - variant of an n-ary tree whicih characters are stored in each node, paths down may represent a word

//DFS vs BFS

//(1)
class node{
public:
  int data;
  node* left; //pointer to left child of node
  node* right; //pointer to the right child of the node
  vector<node*> children;//for use in graphs

  node (int info){
    this->data = info;
  }
};

//(2)
class binarySearchTree{
public:
  node* top;

  binarySearchTree(int info){
    top = new node(info);
  }


  void insert(int info){
    node* p1 = top;
    node* p2 = p1; //will be used for the previous node
    string direction;
    while (p1!=nullptr){
      p2 = p1;
      if (p1->data>=info){
        p1 = p1->left;
        direction = "left";
      }else if (p1->data<info){
        p1 = p1->right;
        direction = "right";
      }
    }
    p1 = new node(info);
    if(direction == "right"){
      p2->right = p1;
    }else if (direction == "left"){
      p2->left = p1;
    }
  }

  void remove(int info){
    ;
  }

  void print(int level = 0){
    cout<<this->top->data<<endl;


  }
};

//class for graph implementation (directed)
class graph{
  node* source;
  node* sink; //may or may not be a sink depending on the graph

  graph (int info){
    source = new node(info);
  }

  void insert (int info, node* parent1, node* parent2 = nullptr, node* parent3 = nullptr){
    node* child = new node(info);
    parent1->children.push_back(child);
    if (parent2 != nullptr)  parent2->children.push_back(child);
    if (parent3 != nullptr) parent3->children.push_back(child);
  }

  void addPath (node*parent, node* child){
    parent->children.push_back(child);
  }
};



//(3) check to see if a binary search tree is balanced
bool isBalanced (node* top){
  //recursive, check children until leaves found
  node* left = top->left;
  node* right = top->right;

  //base case 1, find that tree is unbalanced
  if (left == nullptr && right!=nullptr){
    if (right->left != nullptr or right->right != nullptr){//right side of tree is >1 depth than left
      return false;
    }
    if (right->left == nullptr & right->right == nullptr){//right side of tree is exactly 1 depth more than left
      return true;
    }
  }else if (right == nullptr && left!=nullptr){
    if (left->left != nullptr or left->right != nullptr){ //left side of tree is >1 depth more than right
      return false;
    }
    if (left->left == nullptr && left->right == nullptr){//left side of tree is 1 depth more than right
      return true;
    }
  }else if (right == nullptr && left == nullptr){ //tree ends at this node
    return true;
  }

  //recursive case, calling the function to check and see if the right and left subtrees of this node are also balanced
   if (isBalanced(top->right) && isBalanced(top->left)){
     return true;
   }
   return false; //shouldnt reach here
}




//given a directed graph, determine if there is a path between two nodes
//using DFS
bool isPath (node* start, node* end){
  vector<node*> open = {start};
  vector<node*> closed;

  while (open.size()!= 0){
    current = open[0];
    if (current == end) return true; //path has been found
    kids = current->children.size()-1;
    while (kid>=0){ //check children of current node, add to open if not currently in open or closed 
      if (find(open.begin(), open.end(), kid)==open.end() && find(closed.begin(), closed.end(), kid) == closed.end()){
        open.push_back(kid);
      }
    open.erase(open.begin());
    closed.push_back(current);

    }
    //add children of start to open if not there already
    //move open start to closed
    //

  }



  return false;
}





int main(){

  //check isBalanced, functioning properly
  binarySearchTree myTree(5);
  myTree.insert(4);
  myTree.insert(6);
  myTree.insert(8);
  myTree.insert(5);
  myTree.insert(5);
  //myTree.insert()
  cout<<isBalanced(myTree.top)<<endl;



  return 0;
}
