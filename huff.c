#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"huff.h"


typedef struct _node
{
  int tracker;
  unsigned long val;
}table_node;

void printcheck(unsigned short hold);
void printheader(lnode * node,FILE * fptr);

lnode * organize(lnode * head,table_node * table[],long a[]);

void countchar(char * input, long  a[256]) // reads the number of char from input.
{

  FILE * src;
  src=fopen(input,"r");
  if(src== NULL)
{
printf("\n Check your input again please!!\n");
return ;
}
  fseek(src,0,SEEK_SET);
  int ch;
  int holder;
  ch = fgetc(src);
  holder = ch;
  while(ch!=EOF)
    {
      holder = ch;

      // printf("%c %d\n",holder,holder);
      a[holder]++;
      //  if(holder> 127)
      //	{
      //  printf("\nPrinting HERE");
      //  printf("\n %d : %ld",holder,a[holder]);
      //    }
    

      ch = fgetc(src);  
    }
	a[3]=1;

  fclose(src);

}

//*******************************


//************FUNCTION PART 2******
int compare(const int a,const int b)
{
  if (a>b) return 1;
  else if (a<b)return -1;
  else return 0;
}

int charcmp(const unsigned char a,const unsigned char b)
{
  if(a>b) return 1;
  else if (a<b) return -1;
  else return 0;
}

lnode *PQ_enqueue(lnode **pq, const int new1,const unsigned char cha,int (*cmp_fn)(const int,const int),int (*cmp_ch)(const unsigned char,const unsigned char))
{
  lnode *node = (lnode *)malloc(sizeof(lnode));
  if(node == NULL)
    {
      return NULL;
    }
  node->ptr = (int)new1;
  node->ch = cha;
  node->next = NULL;
  node->left = NULL;
  node->right = NULL;
  lnode wall;
  wall.next = *pq;
  lnode * cur = *pq;
  lnode * prev = &wall;
  while(cur!=NULL)
    {
      if((cmp_fn(cur->ptr,new1)>0)&&(cmp_ch(cur->ch,cha)<=0))
	break;
      else
	{
	  prev = cur;
	  cur = cur->next;
	}
    }
  prev->next=node;
  node->next = cur;
  *pq = wall.next;
  return node;
}


/*void printlist(lnode * head,char * out)
  {
  FILE * fptr;
  fptr = fopen(out,"w");
  lnode * cur;
  cur = head;
  while(cur != NULL)
  {
  fprintf(fptr,"%c:%d",cur->ch,cur->ptr);
  fprintf(fptr,"->");
  cur = cur->next;
  }
  fprintf(fptr,"NULL");
  fputc('\n',fptr);
  fclose(fptr);
  }*/

lnode * takelist(long a[])
{
  lnode * head = NULL;
  int i;
  for(i=0;i<256;i++)
    {
      if(a[i]!=0)
	{
	  unsigned char ch = (unsigned char)i;
	  PQ_enqueue(&head,a[i],ch,&compare,&charcmp);
	}
    }
  //PQ_enqueue(&head,1,3,&compare,&charcmp);
  //  printlist(head,output);
  return head;
}

//**************************

//************FUNCTION PART 3*****************

lnode * enqueue(lnode ** pq,lnode * node,int (*cmp_fn)(const int,const int))
{
 
  lnode wall;
  wall.next = *pq;
  lnode * cur = *pq;
  lnode * prev = &wall;
  while(cur!=NULL)
    {
      if((cmp_fn(cur->ptr,node->ptr)>0))
	break;
      else
	{
	  prev = cur;
	  cur = cur->next;
	}
    }
  prev->next=node;
  node->next = cur;
  *pq = wall.next;
  return node;
}
/*
  void display(char * out,int a[],char ch,int i)
  {
 
  FILE * fptr;
  fptr = fopen(out,"a+");
  fprintf(fptr,"%c:",ch);
  // printf("\n %c: ",ch);
  int k=0;char hold;

  for(k=0;(k<i);k++)
  {
 
  hold = a[k] + '0';
  // printf(" %d ",a[k]);
  fputc(hold,fptr);
  //      fprintf(fptr,"%d",a[k]);
  k++;
  }
  // }
  fputc('\n',fptr);
  // printf("\n");
  fclose(fptr);
  }*/



void print_tree(lnode * t,long a[],int i,table_node * table[])
{

   
  if(t->left == NULL && t->right == NULL)
    {int l = 0;
      table[t->ch] = (table_node *)malloc(sizeof(table_node));
      table[t->ch]->val = 0x00;
      table[t->ch]->tracker = i;
      //fprintf(fptr,"%c:",t->ch);
  // printf("%c : ",t->ch);
      for(l=0;l<i;l++)
	{
  // printf("%ld",a[l]);
	  if(a[l]==1)
	    {
              table[t->ch]->val = table[t->ch]->val << 1;
	      table[t->ch]->val = table[t->ch]->val | 0x01;
	      
	      
	    }
	  else if(a[l]==0)
	    {
	      
	      table[t->ch]->val = table[t->ch]->val <<1;
	    }
	}
// printf("\n");
      //  table[t->ch]->val = val<<(16-tracker);
      return;
    }
  a[i]=0;
  print_tree(t->left,a,i+1,table);
  a[i]=1;
  print_tree(t->right,a,i+1,table);
  // a[i] = 9;
  return ;

}




lnode * organize(lnode * head,table_node * table[],long a[])
{ 
  lnode * t;
  t = head;
 
  // if(ptr == NULL)return NULL;
  
  while(t->next != NULL)
    {
      lnode * new;
      new = malloc(sizeof(lnode));
      if(new == NULL)
	{
	  // return NULL;
	}
      new->left = t;
      new->right = t->next;
      new->ptr = t->ptr + t->next->ptr;
      new->next = NULL;
      t = t->next->next;
      enqueue(&t,new,&compare);
    }
  head = t;
  //  printf("\n final: %d left: %d right: %d\n",t->ptr,t->left->ptr,t->right->ptr);
  //int a[t->ptr] ;
  print_tree(t,a,0,table);
  
  return(head);
}


//***************************************PART 5 ***






void convert(FILE * rptr,FILE * fptr)
{
 
  int count = 0;
	
  unsigned char temp = 0x00;
  int ch;
  unsigned char final = 0x00;
  unsigned char leftover = 0x00; 
  int check2 = 0;
 

 
  while((ch = fgetc(rptr)) != EOF)
    { 
      if(check2==0)
	{
	  if(ch == '1' ) //if indicator 1
	    {
	      unsigned char k = 1;
	  		
	      final = final|(k<<(7-count));
	      check2 = 1;count ++;
	      if (count == 8)
	    	{ 	
				
		  fputc(final,fptr);
      //printf("%x\n",final);

		  final = 0x00;count = 0;
	    	}
	    }

	  else if(ch == '0' ) //if indicator 0
	    {
	      final = final | 0x00; 
	      count ++;

	      if (count == 8)
	    	{ 
				
		  fputc(final,fptr);
      //printf("%x\n",final);
			
		  final = 0x00;count = 0;
	    	}
	
	    }
	}

      else if(check2 == 1) //if character
	{
	  		
			
	  temp = ch >> (count);
		
		


		
	  final = final | temp;
		
		

		
	  leftover = ch << (8-count);
		
		


	  check2 = 0;
	  fputc(final,fptr);  
    //printf("%x\n",final);

	  final = 0x00; 
	  final =final|leftover; 

	  leftover =0x00;

	
	}
    }
  if(count!=0)
    {
      final= final|0x00;
      fputc(final,fptr);
      //printf("%x\n",final );
    }
}
//***********************************************************************
void convert_body(FILE * fptr,FILE * out,table_node * table[])
{
  /*
    1111111110000000 count = 9 leftover = 1
    0000000010101010 tracker = 8

  */
  unsigned char ch;
  unsigned long hold=0x00;
  int leftover = 0;
  ch=fgetc(fptr);
  int count = 0;
  while(!feof(fptr))
    {
       // printf("fcghfufjghj\n");
      if(count+table[ch]->tracker <= 32) // when lesser than or equal to 16 bits are filled in the short int
	{
	  hold = hold | ((table[ch]->val)<<(32-count-table[ch]->tracker));
	  count += table[ch]->tracker;
	}
      else//when there are more than 16 bits.
	{
	  leftover = count + table[ch]->tracker - 32;
	  hold = hold | ((table[ch]->val)>>leftover); //<- check this line. 
	  count = 32;
	}
      if(count == 32)
	{
   // printcheck(hold);
    // printf("%hu\n",hold);
    // printf("%x\n",hold);
    unsigned char badu  = hold>>24;
    fputc(badu,out);
badu = (hold & 0x00ff0000)>>16;
fputc(badu,out);
badu = (hold & 0x0000ff00)>>8;
fputc(badu,out);
    badu = hold & 0x000000ff;
    fputc(badu,out);

    // printf("%x",hold);

//	  fprintf(out,"%x",hold);
  

      count = 0;
      hold = 0x00|(table[ch]->val<< (32 - leftover)); //<-have to add leftover bits here and then accept new character.
			count = leftover;      
			leftover = 0;
			
	}

      ch = fgetc(fptr);
}
  //MANUALY ADDING PSEUDO EOF
      // printf("%d\n",count );

  unsigned long end = table[3]->val;
  int t=2;
  while(t != 0)
    {
// printf ("entering");
      // printf("%d\n",count );
      if(count+table[3]->tracker <= 32)
	{
	  hold = hold | ((end)<<(32-count-table[3]->tracker));
   // printcheck(hold);
    // printf("%hu\n",hold);
    // printf("%x\n",hold);
    unsigned char badu  = hold>>24;
    fputc(badu,out);
badu = (hold & 0x00ff0000)>>16;
fputc(badu,out);
badu = (hold & 0x0000ff00)>>8;
fputc(badu,out);
    badu = hold & 0x000000ff;
    fputc(badu,out);

    
    end = 0;
	  t = 0;
	}
      else//when there are more than 16 bits.
	{
	  leftover = count + table[3]->tracker - 32;
	  hold = hold | ((end)>>leftover); 

			//printcheck(hold);
      // printf("%hu\n",hold);
      // printf("%x\n",hold);
       unsigned char badu  = hold>>24;
    fputc(badu,out);
badu = (hold & 0x00ff0000)>>16;
fputc(badu,out);
badu = (hold & 0x0000ff00)>>8;
fputc(badu,out);
    badu = hold & 0x000000ff;
    fputc(badu,out);

    // fprintf(out,"%x",hold);


	    count = 32;
      hold = 0x00|(end<< (32 - leftover)); //<-have to add leftover bits here and then accept new character.
      end = 0;
      t=0;
	}
      if(count == 32)
	{
		//printcheck(hold);
      
        unsigned char badu  = hold>>24;
    fputc(badu,out);
badu = (hold & 0x00ff0000)>>16;
fputc(badu,out);
badu = (hold & 0x0000ff00)>>8;
fputc(badu,out);
    badu = hold & 0x000000ff;
    fputc(badu,out);
	  
          count = 0;
	}

    }
}
//***********************************************
void printcheck(unsigned short hold)
{;

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
}



  //**********************************************************************8
  void printheader(lnode * node,FILE * fptr)
  {
    if(node->left == NULL && node->right==NULL)
      {
	fputc('1',fptr);
	fputc(node->ch,fptr);
	return;
      }

    printheader(node->left,fptr);
    printheader(node->right,fptr);
    fputc('0',fptr);
  }
//**************************************************************************
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
  //*********************************************************************
  int main(int argc, char ** argv)
  {

//  double cstart, cend;


    table_node * table[256];

    long a[256] = {0};
    lnode * head;
   // cstart = (double) clock();
    countchar(argv[1],a);
 
 char * string = (char*)malloc(sizeof(argv[1])+6);
strcpy(string,argv[1]);
string = strcat(string,".huff");

    head = takelist(a);

    head= organize(head,table,a);

    FILE * fptr1;
    fptr1 = fopen("lala.txt","w");
    lnode * temp = head;
    printheader(temp,fptr1);
    fputc('0',fptr1);
    fclose(fptr1);
    FILE * rptr = fopen("lala.txt","r");
    FILE * ptr = fopen(string,"wb");
    convert(rptr,ptr);
    fclose(rptr);
    //fclose(ptr);
   // FILE * output = fopen("output.txt","a");
    FILE * fptr = fopen(argv[1],"r");
    convert_body(fptr,ptr,table);
   /* cend = (double) clock();
        printf("\n");
        printf(" Elapsed Time (sec): %f\n", (cend - cstart)/CLOCKS_PER_SEC);*/
   // fclose(output);
    fclose(fptr);
    fclose(ptr);
    //remove("lala.txt");
    destroystuff(head);
    // free(head);
    return 1;

  }
