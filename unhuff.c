#include<stdio.h>
#include<stdlib.h>
#include"huff.h"
#include<string.h>
#include<time.h>
#include <sys/time.h>

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 1000000
#endif
//************************************************************************************************
lnode *make_tree(FILE *input)
{
  lnode * head = NULL;
  int count=0;
  unsigned char ch,hold,temp;
  ch = fgetc(input);
  do
    {

      int temp1 = (ch>>(7-count))%2;
 
      

      if((temp1) == 1) //pushing into stack!!
	{
	  ch = ch<<(1+count);
	  hold =fgetc(input);
	  temp = hold>>(7-count);
	  ch = ch|temp;
	
	  lnode * node = (lnode*)malloc(sizeof(lnode));
	  node->next = head;
	  head = node;

	  head->ch = ch;

	  ch = hold;
	  //updating counter!!
	  if(count == 7)
	    {
	      count = 0;
	   
	      ch = fgetc(input);
	    }
	  else
	    {
	      count++;
	    }
	}
      else if(temp1 == 0 && head->next==NULL)
        break;
      else                                             //making tree!!
	{

	 // printf("%d",temp1);
	  lnode * parent = (lnode*)malloc(sizeof(lnode));
      
	  parent->right = head;
	  lnode * p = head->next;
	  head = p;
	  parent->left = head;
	  parent->next = head->next;
	  head = parent;
	  //updating counter;
	  if(count == 7)
	    {
	      count = 0;
	      ch = fgetc(input);
	    }
	  else
	    {
	      count++;
	    }
	}
    }while(1);

  return head;
}

//***********************************************************************************************
void destroystuff(lnode * head)
{

  if(head== NULL)
    {
      return;
    }
  destroystuff(head->left);
  destroystuff(head->right);
  free(head);
}
//*************************************************************************************************
void decompress_body(FILE * input,FILE * output,lnode * head)
{

  unsigned char ch ,temp;
  int count=0;
  unsigned char mask = 0x01;

  ch = fgetc(input);

  lnode * tree;
  tree = head;
  while(ch!=EOF)
    {
      count =0;
      while(count!=8)
	{ 
	  temp = (ch>>(7-count)) & mask;

	  if(temp == 1)
	    { 
	      tree = tree->right;
	    }
	  else
	    { 
	      tree = tree->left;
	    }
	  if(tree->right == NULL && tree->left==NULL)
	    {
	   
	      if(tree->ch == 3)
		{
		  return;
		}
	      fputc(tree->ch,output);
	      tree = head;
	    }

	  count++;
	}
    
		ch =fgetc(input);
		

    }
  return;
}
//***************************************
//FOR DEBUGGING PURPOSES ONLLY!!!!
// void printcheck(unsigned short hold)
// {
// unsigned short mask = 0x01;
// int count = 15;
// while(count >= 0)
// {
// unsigned short temp = hold>>count;
// temp = temp & mask;
// if(temp == 1)
// {
// printf("1");
// }
// else
// {
// printf("0");
// }
// count--;
// }
// printf("\n");
// }
//***********************************************************************************************
int main(int argc,char **argv){
 
  FILE * input = fopen(argv[1],"rb");
if(input == NULL)
{
printf("\n Check your input again please!!\n");
return 0;
}
   char * string = (char*)malloc(sizeof(argv[1])+6);
   strcpy(string,argv[1]);
   string = strcat(string,".unhuff");

  FILE * output= fopen(string,"w");
 
  lnode * head = make_tree(input);
  lnode * temp = head;
  
  decompress_body(input,output,temp);
     


   fclose(input);
   fclose(output);
   destroystuff(head); 
  return 0 ;

}
