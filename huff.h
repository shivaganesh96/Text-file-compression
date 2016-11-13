
#include<stdio.h>
void countchar(char * a,  long c[]);



typedef struct _lnode {
int ptr;
unsigned char ch;
struct _lnode * next;
struct _lnode * left;
struct _lnode * right;
} lnode;


lnode * takelist(long a[]);

int compare(const int a,const int b);
int charcmp(const unsigned char a,const unsigned char b);
lnode *PQ_enqueue(lnode **pq, const int new1,const unsigned char cha,int (*cmp_fn)(const int,const int),int (*cmp_ch)(const unsigned char,const unsigned char));


lnode * enqueue(lnode ** pq,lnode * node,int (*cmp_fn)(const int,const int));




void convert(FILE * rptr,FILE * fptr);
 
