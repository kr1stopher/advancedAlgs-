#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

//nodes will  be required for stack and queue implementation:
class node{
public:
  int data;
  node* next = nullptr;

  node(int info){
    this->data = info;
  }
};


class stack {
public:
  node* top = nullptr;


  void  push(int item){
    node* input = new node(item);
    input->data = item;
    input->next = this->top;
    this->top = input;
  }

  int pop(){
    node* popOff = this->top;
    this->top = this->top->next;
    return popOff->data;
  }
  void printStack(){
    int i = 0;
    while (this!= nullptr && this->top !=nullptr){
      cout<<"This is item # "<<i<<" on the stack: "<< this->pop() <<endl;
      ++i;
    }
  }
};


//implement a class that uses a set of stacks, when a stack reaches max capacity you start a new one 
class setOfStacks{
public:
  node* top = nullptr; // I think I can remove
  vector<stack> stacks; //vector containing stack objects
  int stackLimit = 10;  //limit to the size each stack can be
  int stacked = 0;

  void  push(int item){
    node* input = new node(item);
    if (stacked == 10 or stacked == 0){
      stack newStack;
      stacks.push_back(newStack);
      stacked = 0;
    }
    stacks.back().push(item);
  }

  int pop(){
    int dataOut = stacks.back().pop();
    stacked--;
    if (stacked ==0 and stacks.size()!=0){
      stacks.pop_back();
      stacked = 10;
    }
    return dataOut;
  }

  void printStack(){
    while (stacks.size() != 0){
      stacks.back().printStack();
      stacks.pop_back();
      stacked = 10;
    }
    stacked =0;
    }
};

//turns an array into a stack of nodes, given the array and # of elements in the array
stack arrayStack (int* p, int length){
  int i = 0;
  stack myStack;
  while (i<length){
    myStack.push(*p);
    p++;
    ++i;
  }
  return myStack;
}




int main (){
  stack myStack;
  int a[] = {1,2,3,4,5,6};
  for (int i =0; i<sizeof(a)/sizeof(int); i++){
    myStack.push(a[i]);
  }
  stack myStack2 = arrayStack(a,6);
  myStack2.printStack();


  //setOfStacks testing
  cout<<endl<<endl<<endl<<"playing with stack sets now "<<endl;
  setOfStacks stackSet;
  int elements = 30;
  int b[elements] = {0};
  for (int j =0; j<elements; j++){
    b[j] = j;
  }
  for (int i =0; i<sizeof(b)/sizeof(int); i++){
    stackSet.push(b[i]);
  }
  //stackSet.printStack();


}
