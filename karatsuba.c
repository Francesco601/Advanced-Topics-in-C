// C program that implements the Karatsuba algoritm
// for super-fast multiplication by taking advantage of
// bit manipulation. It is also a classsic divide and conquer
// algorith with time complexity O(n^log base2 3) = O(n^1.59)
// Can be further improved using FFT (Fast Fourier Transform)

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>


char *a1;
char *b1;
char *karatsuba(char *a,char *b,int k);
char *split_at(char *x,int start,int end);
char *combine(char *a,char *b);
char *strrev(char *s);
char *difference(char *a,char *b);
void printanswer(char *a, int x);

int main(void)
{
	char *a=malloc(sizeof(char *)*1000);
	char *b=malloc(sizeof(char *)*1000);
	int i=0;
	char *a1;
	char *b1;
	char *x;
	char *kma;
	
	printf("Please enter the First Operand:\t");
	scanf("%s", a);
	printf("Please enter the Second Operand:");
	scanf("%s", b);
	long k=strlen(a);
	long o=strlen(b);
	a1=(char *)malloc(sizeof(char *)*(k+1));
	strcpy(a1,a);
	free(a);
	b1=(char *)malloc(sizeof(char *)*(o+1));
	strcpy(b1,b);
	free(b);
	x=(char *)malloc(sizeof(char *)*(k+o));
	if(k>o)
		{
			kma=(char *)malloc(sizeof(char *)*(k-o+1));
			for(i=0;i<(k-o);i++)
			    kma[i]='0';

			kma[i]='\0';
			strcat(kma,b1);
			strcpy(b1,kma);
			free(kma);
			x=karatsuba(a1,b1,k);
		}
	else if(k<o)
		{
			kma=(char *)malloc(sizeof(char *)*(o-k));
			for(i=0;i<(o-k);i++)
		           kma[i]='0';
			kma[i]='\0';
			strcat(kma,a1);
			strcpy(a1,kma);
			free(kma);
			x=karatsuba(a1,b1,o);
		}
	else if(k==o)
		{
			x=karatsuba(a1,b1,o);
		}
	printanswer(x,strlen(x));	
	free(x);
	free(a1);
	free(b1);
}
	
char * karatsuba(char *a,char *b,int k)
{
	char *s;
	int len;
	char *s1;
	int odd=0;
	int n=k;
	int x;
	int i;
	int jk;
	
	if(k==1)
		{
			int z=(a[0]-'0')*(b[0]-'0');
			s=(char *)malloc(sizeof(char *)*3);
			sprintf(s, "%d", z);
			len=strlen(s);
			s1=(char *)malloc(sizeof(char *)*(len+1));
			strcpy(s1,s);
			free(s);
			return s1;
		}
	if(strlen(a)<strlen(b))
		{
			x=strlen(b)-strlen(a);
			char *che=malloc(sizeof(char *)*(x+1));
			for(i=0;i<=x;i++)
				che[i]='0';
			che[i]='\0';
			strcat(che,a);
			strcpy(a,che);
			free(che);
		}
	if(strlen(a)>strlen(b))
		{
			x=strlen(a)-strlen(b);
			char *che=malloc(sizeof(char *)*(x+1));
			for(i=0;i<=x;i++)
				che[i]='0';
			che[i]='\0';
			strcat(che,b);
			strcpy(b,che);
			free(che);
		}
	if(k%2==1)
		{
		    odd=1;
		    n=n+1;
		}
		if(strlen(a)>strlen(b))
			jk=strlen(a);
		else
			jk=strlen(b);
		char *ax=malloc(sizeof(char *)*(2+jk));
		char *bx=malloc(sizeof(char *)*(2+jk));
		if (odd)
			{
			strcpy(ax,"0");
			strcpy(bx,"0");
			strcat(ax,a);
			strcat(bx,b);
			strcpy(a,ax);
			strcpy(b,bx);
			
			}
		else
			{
			strcpy(ax,a);
			strcpy(bx,b);
			}
	char * p1;
	p1=(char *)malloc(sizeof(char *)*2*k);
	char * p2;
	p2=(char *)malloc(sizeof(char *)*2*k);
	char * p3;
	p3=(char *)malloc(sizeof(char *)*2*k);
	
	int m=n/2;
	
	char * a1;
	a1=(char *)malloc(sizeof(char *)*2*k);
	a1=split_at(ax,0, m);
	char * a2;
	a2=(char *)malloc(sizeof(char *)*2*k);
	a2=split_at(ax,m,n);
	char * b1;
	b1=(char *)malloc(sizeof(char *)*2*k);
	b1=split_at(bx,0, m);
	char * b2;
	b2=(char *)malloc(sizeof(char *)*2*k);
	b2=split_at(bx,m,n);
	free(ax);
	free(bx);
	p1 = karatsuba(a1, b1, m);
	char *uh;
	uh=(char *)malloc(sizeof(char *)*2*k);
	strcpy(uh,p1);
	p2 = karatsuba(a2, b2, m);
	int x1;
	x1=strlen(combine(a1,a2));
	if(strlen(combine(b1,b2))>strlen(combine(a1,a2)))
		x1=strlen(combine(b1,b2));
	p3 = karatsuba(combine(a1,a2), combine(b1,b2), x1);
	char *kma;
	kma=(char *)malloc(sizeof(char *)*2*k);
	for(i=0;i<n;i++)
		kma[i]='0';
		kma[i]='\0';
	strcat(p1,kma);
	char *res;
	res=(char *)malloc(sizeof(char *)*2*k);
	res=combine(p1,p2);
	char *q;
	q=(char *)malloc(sizeof(char *)*2*k);
	q=combine(uh,p2);
	q=difference(p3,q);
	for(i=0;i<m;i++)
		kma[i]='0';
		kma[i]='\0';
	strcat(q,kma);
	char *sur;
	sur=(char *)malloc(sizeof(char *)*2*k);
	sur=combine(q,res);
	
	free(p1);
	free(p2);
	free(p3);
	
	free(a1);
	free(a2);
	free(b1);
	free(b2);
	free(uh);
	free(kma);
	free(res);
	free(q);
	return sur;
}
char * split_at(char * x,int start,int end)
	{
		char *a;
		a=(char *)malloc(sizeof(char)*(end-start+1));
		int i;
		for(i=0;i<(end-start);i++)
			a[i]=x[i+start];
		a[i]='\0';
		return a;
	
	}	

char * combine(char * s1,char * s2) 
{

	int l1=strlen(s1);
	int l2=strlen(s2);
	int i;
	int x;
	if(l1>=l2)
		x=l1;
	else
		x=l2;
	int *num1=(int*)malloc(sizeof(int)*(l1+1));
	int *num2=(int*)malloc(sizeof(int)*(l2+1));
	int *sum=(int*)malloc(sizeof(int)*(x+2));
	char *res=(char*)malloc(sizeof(int)*(x+2));
	/* convert character to integer*/

	for (l1 = 0; s1[l1] != '\0'; l1++)
		num1[l1] = s1[l1] - '0';
	
	for (l2 = 0; s2[l2] != '\0'; l2++)
		num2[l2] = s2[l2] - '0';

	int carry = 0;
	int k = 0;
        i = l1 - 1;
	int j = l2 - 1;
	for (; i >= 0 && j >= 0; i--, j--, k++) 
	{
		sum[k] = (num1[i] + num2[j] + carry) % 10;
		carry = (num1[i] + num2[j] + carry) / 10;
	}
	if (l1 > l2) 
	{
	
		while (i >= 0)
		{
			sum[k++] = (num1[i] + carry) % 10;
			carry = (num1[i--] + carry) / 10;
		}

	}
	if (l1 < l2) 
	{
		while (j >= 0)
		{
		
		sum[k++] = (num2[j] + carry) % 10;
		carry = (num2[j--] + carry) / 10;
		}
	} 
	 
	if (carry > 0)
		{sum[k++] = carry;}
	
	int n=0;
	for (k--; k >= 0; k--)
	{
		n += sprintf (&res[n], "%d", sum[k]);
		
	}
	free(num1);
	free(num2);
	free(sum);
	return res;
	
}
char * difference(char * s1,char * s2) 
	{
	int i;
	int l1=strlen(s1);
	int l2=strlen(s2);
	l1--;
	l2--;
	if(l1<l2)
		return difference(s2,s1);
	else if(l1==l2 && strcmp(s1,s2)<0)
		return difference(s2,s1);
	int *num1=(int*)malloc(sizeof(int)*(l1+1));
	int *num2=(int*)malloc(sizeof(int)*(l2+1));
	int *diff=(int*)malloc(sizeof(int)*(l1+1));
	//char *res=(char*)malloc(sizeof(int)*(len+1));
	/* convert character to integer*/

	for (l1 = 0; s1[l1] != '\0'; l1++)
		num1[l1] = s1[l1] - '0';
	
	for (l2 = 0; s2[l2] != '\0'; l2++)
		num2[l2] = s2[l2] - '0';

	int k = 0;
	int borrow=0;
	int temp;
	i = l1 - 1;
	int j = l2 - 1;
	for (; i >= 0 && j >= 0; i--, j--, k++) 
	{
		temp=num1[i]-num2[j]-borrow;
		borrow=0;
		if(temp<0)
			{
			borrow=1;
			temp=temp+10;
			}
		diff[k] = temp;
		
	}
	for(;i>=0;i--,k++)
	{
		temp=num1[i]-borrow;
		borrow=0;
		if(temp<0)
			{borrow=1;
			temp=temp+10;
			}
		diff[k] = temp;
	}
	char *d;
	d=(char *)malloc(sizeof(char *)*(k+1));
	for(i=0;i<l1;i++)
		d[i]=diff[i]+'0';
		d[i]='\0';
	d=strrev(d);
	free(num1);
	free(num2);
	free(diff);
	return d;
	}
char *strrev(char *s){
                int i,n;
                char *reverse;
 
                for(i=0;s[i]!='\0';i++)
                ;
 
                reverse=malloc(i*sizeof(char));
                n=i-1;
                for(i=n;i>=0;i--)
                                reverse[n-i]=s[i];
                reverse[n+1]='\0';
                return reverse;
}
void printanswer(char *x, int n){
	int flag=0;
	int i=0;
	while(flag==0)
		{
			if(x[i]=='0' && flag==0 && i<n)
				{flag=0;i++;}
			else 
				flag=1;
		}
	if(flag==1)
		printf("The RESULT is:\t %s\n\n",x+i);
			
}
