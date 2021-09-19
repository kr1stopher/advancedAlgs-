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
    cout<<this->top->data<<" has been added to the stack"<<endl;
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
  //myStack.printStack();
  cout<<myStack.pop()<<endl;
  cout<<myStack.pop()<<endl;
  cout<<myStack.pop()<<endl;
  myStack.printStack();

  stack myStack2 = arrayStack(a,6);
  myStack2.printStack();

  stack* threeStack[3];
  

}
