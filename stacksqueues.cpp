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
  int min;

  node(int info){
    this->data = info;
    int min = info;
  }
};

class stack {
public:
  node* top = nullptr;


  void  push(int item){
    node* input = new node(item);
    input->data = item;
    input->min = item;
    input->next = this->top;
    if (top != nullptr && input->min > top->min){ //change min value to reflect that of the stack below  it
      input->min = top->min;
    }
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

  int getMin(){
    return this->top->min;
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
    ++stacked;
    stacks.back().push(item);
  }

  int pop(){
    int dataOut = stacks.back().pop();
    stacked--;
    if (stacks.back().top == nullptr && stacks.size()!=0){
      stacks.pop_back();
      stacked = 10;
    }
    return dataOut;
  }

  void printStack(){
    int i =  stacks.size();
    while (stacks.size() != 0){
      cout<<"This is stack "<<i<<endl;
      stacks.back().printStack();
      stacks.pop_back();
      --i;
      stacked = 10;
    }
    stacked =0;
    }
  int  popAt(int i){
    cout<<stacks.size()<<endl;
    return stacks[i].pop();
  }
};


//given a tower (disks stacked in ascending size from top->bottom) and empty stacks move the tower to another stack
//disks can only be stacked on disks larger thna themselves, can only move one disk at a time
//stack hanoiTower(stack tower){
//}

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

//use two stacks to implement a queue
class myQueue{
public:
  stack front;
  stack back;
  //queue follows first in first out
  void append(int info){
    if (front.top == nullptr){
      front.push(info);
    }else{
      back.push(info);
    }
  }

  int pop(){
    if (front.top == nullptr){
      cerr<<"You tried to pop an empty queue"<<endl;
    }
    int info = front.pop();
    if (front.top == nullptr){
      while (back.top != nullptr){
        front.push(back.pop());
      }
    }
    return info;
    }
};

//sort a stack using only one additional stack and a temp variable
stack stackSort (stack myStack){
  stack sorted;
  sorted.push(myStack.pop());
  int temp;
  while (myStack.top!=nullptr){
    if(myStack.top->data > sorted.top->data){
        sorted.push(myStack.pop());
    }else{
      temp = myStack.pop();
      while (sorted.top != nullptr && sorted.top->data > temp){
        myStack.push(sorted.pop());
      }
      sorted.push(temp);
      while(myStack.top!= nullptr and myStack.top->data > sorted.top->data){
        sorted.push(myStack.pop());
      }
    }
  }
  return sorted;
};



int main (){
  stack myStack;
  int a[] = {3,5,6,3,8,6,7};
  for (int i =0; i<sizeof(a)/sizeof(int); i++){
    myStack.push(a[i]);
  }
  stack myStack2 = arrayStack(a,6);
  cout<<"the minimum value is "<<myStack2.getMin()<<endl;
  myStack.printStack();


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
  cout<<stackSet.popAt(1)<<endl;
  stackSet.printStack();


  //myQueue testing, working properly
  myQueue test1;
  test1.append(2);
  test1.append(3);
  test1.append(4);
  cout<<test1.pop()<<endl;
  test1.append(5);
  cout<<test1.pop()<<endl;
  cout<<test1.pop()<<endl;

//testing stackSort, working properly
  stack myStack3 = arrayStack(a,6);
  stackSort(myStack3).printStack();


}
