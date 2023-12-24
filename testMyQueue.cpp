#include "myQueue.hpp"

#include <stdio.h>


int main(int argc, char const *argv[])
{
    myQueue q = myQueue(4);

    q.enqueue(1);
    printf("tail=%d\thead=%d\n",q.getTail(),q.getHead());

    q.enqueue(2);
    printf("tail=%d\thead=%d\n",q.getTail(),q.getHead());

    q.enqueue(3);
    printf("tail=%d\thead=%d\n",q.getTail(),q.getHead());

    q.enqueue(4);
    printf("tail=%d\thead=%d\n",q.getTail(),q.getHead());

    printf("mainnnnnnnnnnnnnnn\n\n");
    while (!q.isempty())
    {
        printf("%d\t",q.dequeue());
        printf("tail=%d\thead=%d\n",q.getTail(),q.getHead());
    }
    printf("\n\n");

    q.enqueue(3);
    q.enqueue(4);
    while (!q.isempty())
    {
        printf("%d\t",q.dequeue());
    }
    q.erase();
    return 0;
}
