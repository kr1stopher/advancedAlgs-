#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>

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
  node* next; //for linkedLists
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
  binarySearchTree(){

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

  void print(node* root = nullptr, int spacing = 0){
    char char1= ' ';
    if (root == nullptr) root = this->top;
    if (root->right!=nullptr) print(root->right, spacing+1);
    cout<<string(spacing*3, char1)<<root->data<<endl;
    if (root->left!=nullptr) print(root->left, spacing+1);


  }
};

//class for graph implementation (directed)
class graph{
public:
  node* source;
  node* sink; //may or may not be a sink depending on the graph

  graph (int info){
    source = new node(info);
  }

  node* insert (int info, node* parent1, node* parent2 = nullptr, node* parent3 = nullptr){
    node* child = new node(info);
    parent1->children.push_back(child);
    if (parent2 != nullptr)  parent2->children.push_back(child);
    if (parent3 != nullptr) parent3->children.push_back(child);
    return child;
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
    node* current = open[0];
    if (current == end) return true; //path has been found
    int kid = current->children.size()-1;
    while (kid>=0){ //check children of current node, add to open if not currently in open or closed
      node* child = current->children[kid];
      if (find(open.begin(), open.end(), child)==open.end() && find(closed.begin(), closed.end(), child) == closed.end()){
        open.push_back(current->children[kid]);
      }
    kid--;
    }
    open.erase(open.begin()); //remove current from open
    closed.push_back(current); //add current to closed
  }



  return false;
}

//create a binary search tree with minimum height given a sorted (increasing order) array w/unique integer elements
binarySearchTree buildTree (int* arr, int length){
  //start from middle element, and add moving outward
  int middle = floor(length/2);

  //move pointer to center of array
  int center = floor(length/2);
  while (center>0){
    arr++, center--;
  }
  int* arr1 = arr;
  binarySearchTree myTree(*arr);


  int i = 0;
  while (i<(length/2)-(length%2)){
    arr1--, arr++; i++;
    myTree.insert(*arr1);
    myTree.insert(*arr);
  }
  if (length%2 == 1){ //if the length of the array was even you will have one additional value on the right side of the array to add
    arr++;
    myTree.insert(*arr);
  }

  return myTree;
}

//updated build tree alg
binarySearchTree buildTree1 (int* arr, int length, binarySearchTree* myTree){
  //recursively add to tree
  cout<<length<<" is the length"<<endl;
  int* center = arr;
  int i  = 0;
  while (i<floor(length/2)){
    center++,i++;
  }


  if (length == 1){
    myTree->insert(*center);
    return *myTree;
  }else if(length == 2){
    myTree->insert(*center);
    myTree->insert(*(++center));
    return *myTree;
  }else {
    myTree->insert(*center);
    buildTree1(arr, floor((length-1)/2), myTree); //calling left array
    buildTree1(++center, ceil((length-1)/2), myTree);//calling right array

  }
  return *myTree;
}


//returns the depth of the tree
int treeDepth(node* top){


  //recursive, returns +1 of the subtrees below it
  if (top->right == nullptr && top->left == nullptr){
    return 1;
  }else if(top->right == nullptr && top->left !=nullptr){
    return treeDepth(top->left)+1;
  }else if(top->left == nullptr && top->right !=nullptr){
    return treeDepth(top->right)+1;
  }else if(top->right != nullptr && top->left != nullptr){
    return (treeDepth(top->right)<treeDepth(top->left)) ? treeDepth(top->left) +1 : treeDepth(top->right) + 1;
  }

  return 0; //errror

}


//given a binary tree, create a linked list containing all nodes in each depth of the tree
vector<node*> linkedTree(binarySearchTree myTree){
  vector<node*>  linkedLists;
  vector<node*> open; //open nodes to explore in breadthFirstSearch
  node* start = myTree.top;
  open.push_back(myTree.top); //add starting node to open

  //linkedLists.push_back(new node(myTree.top->data));
  int j = -1; //iterator for tree level
   while (open.size()!=0){
     int i = open.size(); //iterator for determining children of this level
     j++;
     while (i>0){
       if (open[0]->left != nullptr) open.push_back(open[0]->left); //add right child to open
       if (open[0]->right != nullptr) open.push_back(open[0]->right); //add right child to open
       //add open[0] to its proper spot in linked list
       if (linkedLists.size()==j) {
         linkedLists.push_back(new node(open[0]->data));
         //j++;
       }else {
         node* ptr = linkedLists[linkedLists.size()-1];
         while (ptr->next != nullptr){
           ptr=ptr->next;
         }
         ptr->next = new node(open[0]->data);
       }
       open.erase(open.begin());
       //++j;
       --i;
     }
   }


  return linkedLists;
}

//determine if a binary tree is a binary search tree
bool isSearch (node* top){//check to see if a tree or subtree is a binary search tree given a starting node
  bool left = true;
  bool right = true;
  if (top->right == nullptr && top->left == nullptr) return true;

  //right side
  if (top->right!=nullptr){
    if (top->right->data<=top->data) return false;
    right = isSearch(top->right);
  }

  //left side
  if (top->left!=nullptr){
    if (top->left->data>top->data) return false;
    right = isSearch(top->left);
  }

  return left && right;

}


//find the common ancestor  of two nodes in a binary tree
node* grandpa(node* top, node* node1, node* node2){
  //find the  nodes
  return new node(7);
}

//determine if tree2 is a subtree of tree1, given pointers to the top nodes of each
bool isSubtree (node* tree1, node* tree2){
  vector<node*> open;
  open.push_back(tree1);

  while (open.size() !=  0){
    node* current = open[0];
    open.erase(open.begin());


    if (current != nullptr && current->data == tree2->data){ //if they match, check to see if the rest of the tree matches
      vector<node*> openT1;
      vector<node*>openT2;
      openT1.push_back(current);
      openT2.push_back(tree2);
      bool isSubtree = true;

      while (isSubtree == true && openT1.size()!=0 && openT2.size()!=0){ //breadthFirstSearch until a mismatch is foudn or all nodes have been checked
        if (openT1[0]==nullptr or openT2[0]==nullptr){//if one is a nullptr but not the other there is no match
          if (openT1[0]!=openT2[0]) isSubtree = false;
          if (openT1[0]== nullptr && openT2[0] == nullptr){
            openT1.erase(openT1.begin());
            openT2.erase(openT2.begin());
          }
        }else if (openT1[0]->data != openT2[0]->data){ //if data doesnt match there is no subtree
          isSubtree = false;
        }else if (openT1[0]->data == openT2[0]->data){ //add children to open to compare
          openT1.push_back(openT1[0]->left);
          openT1.push_back(openT1[0]->right);
          openT2.push_back(openT2[0]->left);
          openT2.push_back(openT2[0]->right);
          openT1.erase(openT1.begin());
          openT2.erase(openT2.begin());
        }
         }
         if (isSubtree == true) return true;
    }

    if (current!= nullptr) open.push_back(current->left);
    if (current!= nullptr) open.push_back(current->right);

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

  //testing graph and is path, working properly
  graph myGraph(1);
  myGraph.insert(2, myGraph.source);
  node* testNode = myGraph.insert(3, myGraph.source);
  myGraph.insert(4, myGraph.source->children[0]);
  node* end = myGraph.insert(5, myGraph.source->children[0]->children[0]);
  if (isPath(myGraph.source, end)) cout<<"there is a path from source to end"<<endl;
  if (!isPath(testNode, end)) cout<<"there is not a path from (3) to (5)"<<endl;

  //testing builtTree
  int arr1[] = {0,1,2,3,4,5,6};
  int arr2[] = {0,1,2,3,4,5,6};
  /*
  binarySearchTree minTree = buildTree(arr1, sizeof(arr1)/sizeof(int));
  cout<<"the depth of the tree is "<<treeDepth(minTree.top)<<endl;
  cout<<endl<<endl<<endl;
  minTree.print();

  binarySearchTree *minTree2 =  new binarySearchTree(1);
  binarySearchTree minTree3 = buildTree1(arr2, sizeof(arr2)/sizeof(int), minTree2);
  cout<<"below is mintree 3"<<endl;
  minTree3.print();
  cout<<endl<<endl<<endl<<endl;

  */
  //testing the print function
  binarySearchTree printTree(7);
  printTree.insert(5);
  printTree.insert(9);
  printTree.insert(4);
  printTree.insert(6);
  printTree.insert(8);
  printTree.insert(10);

  printTree.print();


//Testing linkedTree function
  vector<node*> myLists = linkedTree(printTree);
  int i = 0;
  while (i<myLists.size()){
    node* ptr = myLists[i];
    while (ptr!=nullptr){
      cout<<ptr->data;
      if (ptr->next != nullptr) cout<<"  |  ";
      ptr = ptr->next;
    }
    cout<<endl<<"next list"<<endl;
    i++;
  }
  cout<<isSearch(printTree.top)<<endl;

  //testing isSubtree function, tested and functioning 
  binarySearchTree myTree12(5);
  myTree12.insert(6);
  myTree12.insert(4);
  cout<<isSubtree(printTree.top, printTree.top)<< " is/is not a subtree "<<endl;
  cout<<isSubtree(printTree.top, myTree12.top)<< " is/is not a subtree "<<endl;
  myTree12.insert(12);
  myTree12.print();
  cout<<isSubtree(printTree.top, myTree12.top)<< " is/is not a subtree "<<endl;



  return 0;
}
