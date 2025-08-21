/*
10. Write a program to define a self-referential structure and then create a linked list of 5 nodes using your
defined structure. Declare two members for the structure: one to store a key (an int or double value), and
another to make a node point to the next node in the implementation of the linked list. You may store the
values of the nodes by writing the values explicitly, i.e. hardcoding them, in your source code. Display the
list in a single line as the final output of your program.
*/

#include <stdio.h>

struct node
{
    double key;
    struct node *nodeNext;
};

int main()
{
    struct node n1, n2, n3, n4, n5, *nodeBegin, *ii;
    int i;
    //entering the values to keys
    n1.key=11;n2.key=22;n3.key=33;n4.key=44;n5.key=55;
    //linking the structures
    nodeBegin=&n1;
    n1.nodeNext=&n2;
    n2.nodeNext=&n3;
    n3.nodeNext=&n4;
    n4.nodeNext=&n5;
    n5.nodeNext=NULL;
    //printing the values using linked list
    for(i = 0,ii=nodeBegin; i<5; i++, ii = ii -> nodeNext)   
        printf("%lf\n", ii->key);
    return 0;
}
//success