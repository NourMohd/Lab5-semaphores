#include <iostream>
#include <stdlib.h>
#include <queue>

class myQueue
{
private:
    int *arr;
    int head;
    int tail;
    int maxSize;
    int actualSize;

public:
    myQueue(int ms);
    void enqueue(int element);
    int dequeue();
    bool isempty();
    void erase();
    int getTail();
    int getHead();
    // ~myQueue();
};

myQueue::myQueue(int ms)
{
    maxSize = ms;
    arr = (int*)malloc(maxSize*sizeof(int));
    tail = 0;
    head = 0;
    actualSize=0;
}
void myQueue::enqueue(int element){
    if(actualSize<maxSize){
        arr[tail]=element;
        tail=(tail+1)%maxSize;
        actualSize++;
    }
}
int myQueue::dequeue(){
    if(actualSize>0)
    {
        int tmp= arr[head];
        head=(head+1)%maxSize;
        actualSize--;
        return tmp;
    }
    return -1;
}
bool myQueue::isempty(){
    return actualSize==0;
}

void myQueue::erase(){
    free(arr);
}
int myQueue::getTail(){
    return tail;
}
int myQueue::getHead(){
    return head;
}
