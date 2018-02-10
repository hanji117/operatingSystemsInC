/*
#include<stdio.h>
#include<curses.h>//similar to conio.h

// programming under DOS uses #include <conio.h>, clrscr(), getch. Remove for C
void main()
{
  int a,b,c,l,g,p,i;
  //  clrscr();
  printf("Enter a b c: ");
  scanf("%d%d%d",&a,&b,&c);
  i=1;
  while(i<=a)
    {
      if(a%i==0&&b%i==0&&c%i==0)
	g=i;
      i++;
    }
  i=1;
  p=a*b*c;
  while(c<=p)
    {
      if(i%a==0&&i%b==0&&i%c==0)
	{
	  l=i;
	  break;
	}
      i++;
    }
  printf("GCD: %d\nLCM: %d",g,l);
  //getch();
}
*/


 /*
// C++ program to find LCM of n elements
//#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
 
// Utility function to find GCD of 'a' and 'b'
int gcd(int a, int b)
{
  if (b==0)
    return a;
  return gcd(b, a%b);
}
 
// Returns LCM of array elements
ll findlcm(int arr[], int n)
{
  // Initialize result
  ll ans = arr[0];
 
  // ans contains LCM of arr[0],..arr[i]
  // after i'th iteration,
  for (int i=1; i<n; i++)
    ans = ( ((arr[i]*ans)) /
	    (gcd(arr[i], ans)) );
 
  return ans;
}
 
// Driver Code
int main()
{
  int arr[] = {2, 7, 3, 9, 4};
  int n = sizeof(arr)/sizeof(arr[0]);
  printf("%lld\n", findlcm(arr, n));
  return 0;
}
*/

/*
multiply all the integers and divide it by their gcd.
if Arr[] contains all the numbers for which LCM is to be found 
then
*/
 
/*
int a[1...n];
int lcm=1;

for(int i=1 ; i<n ; i++){
  lcm *= arr[i]*arr[i-1]/gcd(arr[i],arr[i-1] );
 }
printf("LCM = %d ",lcm );

int gcd (int  a ,int b)
{
  if(a%b==0)
    return b;
  return gcd ( b , a%b );
}
*/
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

int lcm(int a,int b)
{
  int gcd=gcd_two_numbers(a,b);
  return (a*b)/gcd;
}

int gcd_two_numbers(int a,int b)
{
  int temp;
  if(a>b)
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
