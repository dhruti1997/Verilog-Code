/*
Description : Decimal to Binary Conversion using concept of stack
*/
#include <stdio.h>

//methods
int push(int);
int pop();

void main()
{
    int num,q,top=-1,a[100],i,flag=0;   //variables used

    printf("Enter a number :\n");
    scanf("%d",&num);
    int push(int q)     //storing the remainder
    {

           top++;
           a[top]=q;
           return a[top];
    }

    int pop()       //to return the stored value in reverse order
    {   int y;

        y= a[top];
        top--;

        return y;
    }
   while(num>0)
    {
        q=num%2;
        push(q);
        num=num/2;
        flag++;
        push(q);
    }

    printf("\nBinary version of the given decimal number is: \t");
    for(i=0;i<flag;i++)
    {
        pop();
        printf("%d",pop());     //printing the reverse order of the pushed values
    }
    printf("\n");
}

