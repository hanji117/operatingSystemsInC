
#include <stdio.h>

int main()
{
  int a[20],i,n,result=1;  // assumption: count can't exceed 20                                              
  printf("Enter number of numbers to calculate LCM(less than 20):");
  scanf("%d",&n);
  printf("Enter %d  numbers to calculate their LCM :",n);
  for(i=0;i<n;i++)
    scanf("%d",&a[i]);
  for(i=0;i<n;i++)
    result=lcm(result,a[i]);
  printf("LCM of given numbers = %d\n",result);
  return 0;
}

void lcmPreparation()
{
  int a[20];//assumption: count can't exceed 20
  int i = 1;
  int n =1;
  int result = 1;

}

int lcm(int a,int b)
{

  int gcd=gcd_two_numbers(a,b);
  return (a*b)/gcd;
}

int gcd_two_numbers(int a,int b)
{
  int temp;
  if(a > b)
    {
      temp=a;
      a=b;
      b=temp;
    }
  if(b%a==0)
    return a;
  else
    return gcd_two_numbers(b%a,a);
}

