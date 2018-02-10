//=========================================================          
//HW#: HW 6 Page Replacement Algorithm                               
//Your name: Edgar Cruz                                
//Complier:  gcc                                                     
//File type: page replacement implementation file                           
//
//I found the code online. I made some changes. fifo already 
//worked. Optimal didn't work but I got it to work. lru doesn't display 
//the correct number of page faults.
//=========================================================  
#include<stdio.h>

int n,pg[40],fr[10];
void fifo();
void optimal();
void lru();
void main()
{
  int i,ch;
  printf("\nEnter total number of pages:");
  scanf("%d",&n);
  printf("\nEnter sequence:");
  for(i=0;i<n;i++) //accepting sequence                                                                                    
    scanf("%d",&pg[i]);
do
  {
    printf("\n\tMENU\n");
    printf("\n1)FIFO");
    printf("\n2)OPTIMAL");
    printf("\n3)LRU");
    printf("\n4)Exit");
    printf("\nEnter your choice:");
    scanf("%d",&ch);
    switch(ch)
      {
      case 1: fifo();
        break;

      case 2: optimal();
        break;

      case 3: lru();
        break;

      }
  }while(ch!=4);
 getchar();
}

void fifo()
{
  int i,f,r,s,count,flag,num,psize;
  f=0;
  r=0;
  s=0;
  flag=0;
  count=0;
  printf("\nEnter size of page frame:");
  scanf("%d",&psize);
  for(i=0;i<psize;i++)
    {
      fr[i]=-1;
    }
  while(s<n)
    {
      flag=0;
      num=pg[s];
      for(i=0;i<psize;i++)
        {
	  if(num==fr[i])
            {
              s++;
              flag=1;
              break;
            }
        }
      if(flag==0)
        {
          if(r<psize)
            {
              fr[r]=pg[s];
              r++;
              s++;
              count++;
            }
          else
            {
              if(f<psize)
                {
                  fr[f]=pg[s];
		  s++;
                  f++;
                  count++;
                }
              else
                f=0;
            }
        }
      printf("\n");
      for(i=0;i<psize;i++)
        {
          printf("%d\t",fr[i]);
        }
    }
  printf("\nPage Faults=%d",count);
  getchar();
}
void optimal()
{
  int f,max,found=0,lg[3],index,k,l,flag1=0,flag2=0,pf=0,frsize=3,i,j;

  printf("\nEnter frame size:");
  scanf("%d",&f);
  int fr[f];
  for(i=0;i<f;i++)
    {
      fr[i]=-1;
    }
  for(j=0;j<20;j++)
    {
      flag1=0;
      flag2=0;
      for(i=0;i<f;i++)
        {
          if(fr[i]==pg[j])
            {
              flag1=1;
              flag2=1;
              break;
            }
	}
      if(flag1==0)
        {
          for(i=0;i<f;i++)
            {
              if(fr[i]==-1)
                {
                  fr[i]=pg[j];
                  flag2=1;
                  break;
                }
            }
        }

      if(flag2==0)
        {
          for(i=0;i<f;i++)
            lg[i]=0;
          for(i=0;i<frsize;i++)
            {
              for(k=j+1;k<20;k++)
		{
                  if(fr[i]==pg[k])
                    {
                      lg[i]=k-j;
                      break;
                    }
                }
            }
          found=0;
          for(i=0;i<f;i++)
            {
              if(lg[i]==0)
                {

                  index=i;
                  found=1;
                  break;
                }
            }
	  if(found==0)
            {
              max=lg[0];
              index=0;
              for(i=1;i<f;i++)
                {
                  if(max<lg[i])
                    {
                      max=lg[i];
                      index=i;
                    }
                }
            }
          fr[index]=pg[j];
          pf++;
	}

      //display                                                                                                            
      printf("\n");
      for(int x=0;x<f;x++)
	{
          printf("%d\t",fr[x]);
	}
    }
  printf("\nTotal number of faults=%d",pf + f);//pf page fault, f frame size                                               
  getchar();
}

void lru()
{
  int count[10],i,j,k,fault,f,flag,temp,current,c,dist,max,m,cnt,p,x;
  fault=0;
  dist=0;
  k=0;
  printf("\nEnter frame size:");
  scanf("%d",&f);
  //initilizing distance and frame array                                                                                   
  for(i=0;i<f;i++)
    {
      count[i]=0;
      fr[i]=-1;
    }
  for(i=0;i<n;i++)
    {
      flag=0;
      temp=pg[i];
      for(j=0;j<f;j++)
        {
          if(temp==fr[j])
            {
              flag=1;
              break;
            }
        }
      if((flag==0)&&(k<f))
        {
          fault++;
          fr[k]=temp;
          k++;
        }
      else if((flag==0)&&(k==f))
        {
          fault++;
          for(cnt=0;cnt<f;cnt++)
            {
              current=fr[cnt];
              for(c=i;c>0;c--)
                {
                  if(current!=pg[c])
                    count[cnt]++;
                  else
                    break;
                }
            }
          max=0;
          for(m=0;m<f;m++)
            {
              if(count[m]>max)
                {
                  max=count[m];
                  p=m;
                }
            }
          fr[p]=temp;
        }
      printf("\n");
      for(x=0;x<f;x++)
        {
          printf("%d\t",fr[x]);
        }
    }
  printf("\nTotal number of faults=%d",fault);
  getchar();
}


