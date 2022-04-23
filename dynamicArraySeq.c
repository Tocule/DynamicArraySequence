#include<stdio.h>
#include<stdlib.h>


/*
 * ************* Maximum Points: 10 ***************** 
 *
 * ********** PENALTY: -15 (negative 15) ************** 
 *  In following cases you will get penalty
 *  (a) Not submitted, 
 *  (b) Copied, 
 *  (c) Late submission
 *  (d) Submission is not as per the instructions
 *
 * ***************** Instructions *******************
 * (1) Implement ALL methods without any changes in input arguments. You are
 *     NOT allowed to add or remove any arguments of method.
 * (2) DO NOT CHANGE any names of structure, functions or arguments etc.
 * (3) You can add helper methods. Add comments to describe its purpose.
 * (4) You can make assumptions if something is not clear. Make sure you write 
 *     your assumptions wherever required as comments. If you make assumptions but 
 *     HAVE NOT mentioned then it may lead to loss of points.
 * (5) While submitting the code DO NOT KEEP any code in main method. Also DO 
 *     NOT CHANGE filename while submitting the code.
*/


/* README
   This implementation of integer sequence uses dynamic array.
   Here we have empty space before and after the sequence.
   We dont need to initiate a new array every time. We can use empty
   slots for new insertions. 
*/

typedef struct Item 
{
  int k;
}Item;

typedef struct DynamicArraySeq 
{
  Item *items; // Array of items
  int s;       // Start Index of sequence
  int e;       // End Index of sequence
  int size;    // Total size of Array
} DynamicArraySeq;

/****Helper Functions*****/
void print(DynamicArraySeq *p)                                  //This function is used to print dynamic array//
{
   printf("Your printed elements are: ");
   for(int i=p->s;i<=p->e;i++)
   {
        printf("%d ",(p->items+i)->k);
   }
   printf("\n");
}  

// Read 'len' number of items and create DynamicArraySeq from it.
// Return address of the sequence.

DynamicArraySeq *build(int len) 
{
   if(len>0)
   {	   
      DynamicArraySeq *p;
      p=(DynamicArraySeq *)malloc(sizeof(DynamicArraySeq));
      p->size=2*len;
      p->items=(Item *)malloc(p->size*sizeof(Item));
      if(p->size==2)
      {
	 p->s=0;                                //For Size>4 I have used starting index to be 3 so that the array will have some blank space
      }                                         //in front as well as in the end    
      if(p->size==4)
      {
 	 p->s=1;                               //for Size=2 or Size=4 I have used suitable starting index
      }	
      p->s=3;
      p->e=p->s+(len-1);
      printf("Enter the elements\n");
      for(int i=p->s;i<=p->e;i++)
      {
         scanf("%d",&(p->items+i)->k);
      }	
      return(p);
   }
   else
   {
      printf("Invalid length\n");                   //Makes sure that length entered is greater than zero
   }
}


// Replace 'i'th item of the sequence with new item 'x'.
void set_at(int i, Item x, DynamicArraySeq *s)
{
   int j=(s->e-s->s)+1;	
   if(i<=0 || i>j)
   {
      printf("Invalid position\n");
   }
   else
   {   
     i--;                                     //In this function as well all functions to be followed it is assumed that user will
     int j=(s->s)+i;                          //enter positions as 1,2,3...n I will convert them to 0,1,2,3.. appropriately, for better 
     (s->items+j)->k=x.k;                     //user experience
   }
}


// Return i th item
Item get_at(int i, DynamicArraySeq s)     //For this and length function it is assumed that while calling the function,it is passed like this 
{                                         //Ex DynamicArraySeq *variablename	
   int j=(s.e-s.s)+1;                     //Item m= get_at(i,*variablename)   pass by value    
   if(i<=0 || i>j)
   {
      printf("Invalid position\n");
   }
   else
   {
      i--;
      j=(s.s)+i;
      Item d;
      d.k=(s.items+j)->k;
      return(d);
   }    

}

// Return Length of sequence 
int length(DynamicArraySeq s)
{
    int j=(s.e-s.s)+1;
    return(j);  
}

// insert 'x' at i th position in sequence s (REMEBER ith ITEM OF SEQUENCE NOT ARRAY).
void insert_at(int i, Item x, DynamicArraySeq *s) 
{
  int element=x.k;
  int j,position;
  j=(s->e-s->s)+1;
  int c,d,m,l;
  
  if(i>j+1 || i<=0)
  {
     printf("Error: Out of bounds.Size of Array is %d\n",j);
  }
  else if(i==1 || i==j)
  {
    printf("Make use of insert_first/insert_last functions\n");
  }
  else
  {	  
  if(s->s==0)
  {
      i--;	  
      j++;
      int sequence[j];
      for(c=0;c<i;c++)
      {
	 sequence[c]=(s->items+c)->k;
      }
      sequence[c]=element;
      for(c=i+1;c<j;c++)
      {
	 l=c-1;
         sequence[c]=(s->items+l)->k;
      }
      s->size=2*j;
      s->items=(Item *)malloc(s->size*sizeof(Item));
      s->s=3;
      d=s->s;
      s->e=s->s+(j-1);
      for(c=0;c<j;c++)
      {
	 (s->items+d)->k=sequence[c];
         d++;
      }
  }
  else
  {
      i--;
      position=(s->s)+i;
      for(c=s->s;c<position;c++)
      {
	 d=c-1;
         (s->items+d)->k=(s->items+c)->k;
      }
      c--;
      (s->items+c)->k=element;
      s->s=(s->s)-1;
  }
  }          

}

// removes the ith element of the sequence and returns deleted item.
// if empty part of array is bigger in size compare to sequence length then
// move sequence to smaller size array.
Item delete_at(int i, DynamicArraySeq *s) 
{
   int j=(s->e-s->s)+1;
   int position;
   Item deleted;
   int c,d;

  if(i>j+1 || i<=0)
  {
     printf("Error: Out of bounds.Size of Array is %d\n",j);
  }
  else if(i==1 || i==j)
  {
    printf("Make use of delete_first/delete_last functions\n");
  }
  else
  {
    i--;
    position=(s->s)+i;
    deleted.k=(s->items+position)->k;
    for(c=position+1;c<=s->e;c++)
    {
	d=c-1;
        (s->items+d)->k=(s->items+c)->k;
    }
    (s->e)--;
  }
  return(deleted);
        
}

// insert item 'x' at the start of the sequence.
void insert_first(Item x, DynamicArraySeq *s)
{
   int element=x.k;
   int j=(s->e-s->s)+1;
   int c,d,m;

   if(s->s==0)
   {
	int sequence[j];
        d=s->s;
        for(c=0;c<j;c++)
	{
	  sequence[c]=(s->items+d)->k;
          d++;
        }
        j++;
        s->size=2*j;
        s->items=(Item *)malloc(s->size*sizeof(Item));
        s->s=3;
        s->e=(s->s)+(j-1);
        (s->items+3)->k=element;
        m=0;
        for(c=4;c<=s->e;c++)
	{
	   (s->items+c)->k=sequence[m];
           m++;
        }
   }
   else
   {
	m=(s->s)-1;
	(s->items+m)->k=element;
	(s->s)--;
   }

}

// insert item 'x' at the end of the sequence.
void insert_last(Item x, DynamicArraySeq *s) 
{
   int element=x.k;
   int j=(s->e-s->s)+1;
   int c,d,m;
   int length=s->size-1;
   if(s->e==length)
   {
       int sequence[j];
       d=s->s;
       for(c=0;c<j;c++)
       {
	  sequence[c]=(s->items+d)->k;
          d++;
       }
       j++;
       s->size=2*j;
       s->items=(Item *)malloc(s->size*sizeof(Item));
       s->s=3;
       s->e=(s->s)+(j-1);
       j--;
       for(c=0;c<j;c++)
       {
	  (s->items+d)->k=sequence[c];
	  d++;
       }
       d=s->e;
       (s->items+d)->k=element;
   }
   else 
   {
      (s->e)++;
      d=(s->e);
      (s->items+d)->k=element;
   }      
         
}

// delete first item of sequence and returns deleted item.
Item delete_first(DynamicArraySeq *s) 
{
  Item b;
  int first=s->s;
  b.k=(s->items+first)->k;
  (s->s)++;
  return(b);
}

// delete last item of sequence and returns deleted item.
Item delete_last(DynamicArraySeq *s) 
{
  Item b;
  int last=s->e;
  b.k=(s->items+last)->k;
  (s->e)--;
  return(b); 
}

int main(void) 
{
}
