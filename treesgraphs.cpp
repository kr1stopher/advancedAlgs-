#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;


//binary tree - at most two children per node
//binary search tree - left child must be <= right child must be >

//balanced tree: left and right subtree of any node must differ by no more than one

// full and complete - all leaves are at the bottom and non leaf nodes have two children (2^n-1 nodes exactly required)


//in-order(most common), post-order, pre-order traversal

//tries - variant of an n-ary tree whicih characters are stored in each node, paths down may represent a word

//DFS vs BFS

class node(){
public:
  int data;
  node* left; //pointer to left child of node
  node* right; //pointer to the right child of the node

  node (int info){
    this->data = info;
  }
}

class binarySearchTree (){
public:
  node* top;

  binarySearchTree(int info){
    top = new node(info);
  }


  void insert(int info){
    ;
  }
  void delete(int info){
    ;
  }
}

//check to see if a binary search tree is balanced
bool isBalanced (node* top){
  //recursive, check children until leaves found
  left = top->left;
  right = top->right;

  //base case 1, find that tree is unbalanced
  if (left == nullptr && right!=nullptr){ //right side of tree is >1 depth than left
    if (right->left != nullptr or right->right != nullptr){
      return false;
    }
    if (right->left == nullptr & right->right == nullptr){
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


  //base cases leaves found
  //left = null & right->right or right->left != null inbalanced or opposite
  //

}


int main(){



  return 0;
}
