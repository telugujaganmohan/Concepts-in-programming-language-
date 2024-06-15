#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BIGINT_SIZE 309

typedef struct BIG_INT
{
	int *num;
	int signedBit;	//1 if negative, 0 if positive
	int length;
} BigInt;

BigInt* addBigInts(BigInt *b1, BigInt *b2);
BigInt* subtractBigInts(BigInt *b1, BigInt *b2);

void printBigInt(BigInt *b)
{
	int i;
	if(b->signedBit==1)
		printf("-");
	for(i = b->length-1; i>=0; i--)
		printf("%d", b->num[i]);
}

//CONVERTS INPUT STRING TO BIGINT DATA TYPE
BigInt stringToBigInt (char *s)
{
	BigInt b;
	int size = strlen(s);
	if(s[0] == '-')
	{
		b.signedBit = 1;
	}	
	else
		b.signedBit = 0;	
	b.length = size - b.signedBit;
	b.num = (int*)malloc(sizeof(int)*(b.length));
	int *i;
	i = b.num;
	size--;
	while(size>=b.signedBit)
	{
		*(i) = s[size]-48;
		i++;
		size--;
	}
	return b;
}

//COMPARES 2 BIGINT
//RETURNS 0 IF SAME
//		<0	IF B2>B1
//		>0 IF B1>B2
int compare(BigInt *b1,BigInt *b2)
{
    int i,retval;
    if(b1->length == b2->length)
    {
        i=(b1->length)-1;
        while(i>=0 && b1->num[i]==b2->num[i])
        {
            i--;
        }
        if(i<0)
        {
            retval=0;
        }
        else
        {
            retval=(b1->num[i])-(b2->num[i]);
        }
    }
    else
    {
        retval=(b1->length)-(b2->length);
    }
    return retval;
}

//ADDITION
BigInt* addBigInts(BigInt *b1, BigInt *b2)
{
	int n1 = b1->length;
	int n2 = b2->length;
	int carry;
	BigInt *sum = (BigInt*)malloc(sizeof(BigInt));
	if(n2>n1)
		sum->num=(int*)malloc(sizeof(int)*(n2+1));
	else
		sum->num=(int*)malloc(sizeof(int)*(n1+1));
	
	//IF BOTH THE NUMBERS ARE OF SAME SIGN
	if(b1->signedBit==b2->signedBit)
	{
		sum->signedBit = b1->signedBit;
		
		carry = 0;
		int i = 0, digit;
		while(i<n1 && i<n2)
		{
			digit = (b1->num[i]) + (b2->num[i]) + carry;
			carry = digit/10;
			digit = digit%10;
			sum->num[i] = digit;
			i++;
		}
		while(i<n1)
		{
			digit = (b1->num[i]) + carry;
			carry = digit/10;
			digit = digit%10;
			sum->num[i] = digit;
			i++;
		}
		while(i<n2)
		{
			digit = (b2->num[i]) + carry;
			carry = digit/10;
			digit = digit%10;
			sum->num[i] = digit;
			i++;
		}
		while(carry!=0)
		{
			sum->num[i] = (carry%10);
			carry/=10;
			i++;
		}
		sum->length = i;
	}
	//IF BOTH NUMBERS ARE OF DIFFERENT SIGN
	else
	{
		if(b1->signedBit==1)
		{
			b1->signedBit = 0;
			sum = subtractBigInts(b2, b1);
			b1->signedBit = 1;
		}
		else
		{
			b2->signedBit = 0;
			sum = subtractBigInts(b1, b2);
			b2->signedBit = 1;
		}
	}
	return sum;
}


BigInt* subtraction(BigInt *b1, BigInt *b2)
{
	BigInt *diff = (BigInt*)malloc(sizeof(BigInt));
	diff->num=(int*)malloc(sizeof(int)*(b1->length));
	int borrow = 0;
	int i = 0, digit;
	while(i<b2->length)
	{
		digit = (b1->num[i]) - (b2->num[i]) - borrow;
		if(digit<0)
		{
			borrow = 1;
			digit+=10;
		}
		else
		{
			borrow = 0;
		}
		diff->num[i]=digit;
		i++;
	}
	while(i<b1->length)
	{
		digit = (b1->num[i]) - borrow;
		if(digit<0)
		{
			borrow = 1;
			digit+=10;
		}
		else
		{
			borrow = 0;
		}
		diff->num[i]=digit;
		i++;
	}
	diff->length = i;
	return diff;
}

//SUBTRACTION
BigInt* subtractBigInts(BigInt *b1, BigInt *b2)
{
	int n1 = b1->length;
	int n2 = b2->length;
	int borrow;
	BigInt *diff = (BigInt*)malloc(sizeof(BigInt));
	if(n2>n1)
		diff->num=(int*)malloc(sizeof(int)*n2);
	else
		diff->num=(int*)malloc(sizeof(int)*n1);
	
	//if the signed bits are not eqaul
	if(b1->signedBit != b2->signedBit)
	{
		if(b2->signedBit==1)
		{
			b2->signedBit=0;
			diff = addBigInts(b1, b2);
			b2->signedBit=1;
			diff->signedBit=0; 
		}	
		else
		{
			b2->signedBit=1;
			diff = addBigInts(b1, b2);
			b2->signedBit=0;
			diff->signedBit=1; 
		}
	}
	else
	{
		if(compare(b1, b2)>0)	//magnitude of b1>b2
		{
			diff = subtraction(b1, b2);	//subtraction of magnitudes
			diff->signedBit = b1->signedBit;	//b1-b2------gets sign of b1
		}
		else
		{
			diff = subtraction(b2, b1);
			if(b1->signedBit==0)		//b1-b2 and b1<b2 ---> diff has opp sign of b1
				diff->signedBit=1;
			else
				diff->signedBit=0;
		}	
	}
	return diff;
}

//MULTIPLICATION
BigInt* multBigInts(BigInt *b1, BigInt *b2)
{
	BigInt *mult = (BigInt*)malloc(sizeof(BigInt));
	mult->length = b1->length+b2->length;
	mult->num=(int*)malloc(sizeof(int)*(mult->length));
	int i, j, carry, prod;
	
	for(i=0; i<mult->length; i++)//initialising 
		mult->num[i]=0;
		
	for(i=0; i<b1->length; i++)
	{
		carry = 0;
		for(j=0; j<b2->length; j++)
		{
			prod = (b1->num[i] * b2->num[j]) + carry;
			carry = prod/10;
			mult->num[i+j]+=(prod%10);
			if(mult->num[i+j]>9)
			{
				mult->num[i+j+1]+=1;
				(mult->num[i+j])%=10;
			}
		}
		while(carry!=0)
		{
			mult->num[i+j]+=(carry%10);
			if(mult->num[i+j]>9)
			{
				mult->num[i+j+1]+=1;
				(mult->num[i+j])%=10;
			}
			carry/=10;
			j++;
		}
	}
	
	if(b1->signedBit==b2->signedBit)
		mult->signedBit=0;
	else
		mult->signedBit=1;
	
	i=mult->length-1;
	while(mult->num[i]==0)
	{
		i--;
		(mult->length)--;
	}
	if(mult->length==0)	//if input in 0, product is 0
	{
		mult->signedBit=0; //if mult by negative number, - sign comes
		mult->length=1;
	}
		
	return mult;
}

int main()
{
	BigInt num1, num2;
	char *n1, *n2;
	n1 = (char*)malloc(sizeof(char)*BIGINT_SIZE);//DYNAMIC ALLOCATION OF THE STRINGS
	n2 = (char*)malloc(sizeof(char)*BIGINT_SIZE);
	
	printf("Enter number 1 : ");
	scanf("%s", n1);
	printf("Enter number 2 : ");
	scanf("%s", n2);
	
	num1 = stringToBigInt(n1);	//CONVERTING STRING TO BIG INT
	num2 = stringToBigInt(n2);
	
	BigInt *ans = addBigInts(&num1, &num2);
	printf("SUM OF 2 NUMBERS : ");
	printBigInt(ans);
	
	ans = subtractBigInts(&num1, &num2);
	printf("\nDIFFERENCE OF 2 NUMBERS : ");
	printBigInt(ans);
	
	ans = multBigInts(&num1, &num2);
	printf("\nPRODUCT OF 2 NUMBERS : ");
	printBigInt(ans);
	
	return 0;
}
