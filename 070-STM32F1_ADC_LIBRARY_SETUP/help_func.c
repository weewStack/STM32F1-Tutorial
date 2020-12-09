#include "help_func.h"

void str_empty(char str[])
{
	int i = 0;
	while(str[i] != '\0')
	{
		str[i] = '\0';
		i++;
	}
	
}
void str_empty_len(char str[],char len)
{
	int i = 0;
	for(i=0;i<len;i++)
	{
		str[i] = '\0';
	}
	
}
/*
1- get the len of a string
*/

int len_str(char str[])
{
int len = 0;
	while(str[len] != '\0')
	{len++;}
	return (len);
}
/*

2- find a string on a string
*/
int find_str(char str1[], char str2[])
{
	int match = 0;
	/*
	1- First loop going through all the chars of STR2
	2- Nested loop inside the first to go through the STR1
	*/
	
	int STRlen = len_str(str1);
	int i = 0;
	int j = 0;
	int test = 0;
	
	while((str2[i + STRlen-1] != '\0' | str2[i + STRlen] != '\0') & (match ==0))
	{
	for(j=0; j<= STRlen;j++)
		{
			if(str1[j] == str2[i+j])
			{
				test ++;
				if(test == STRlen+1)
				{
					match =1 ;
				}
			}
		}
	test = 0;
	i++;
	}



	return match;
}


/*

3- finding an exact string match 
*/

int find_strL(char str1[], char str2[])
{
int result = 0;
	if((len_str( str1) == len_str(str2)) & find_str(str1,str2))
	{
		result = 1;
	}
	return result;
}

/*

4- Concatenate 2 strings


*/

void Concatstr(char str1[], char str2[])
{
	int i = 0;
	int j = 0;
	while(str1[i] != '\0')
	{i++;}
	while(str2[j]!= '\0')
	{
		str1[i+j]= str2[j];
		j++;
	}
}

/*
5- Convert integer to string
*/

void int2char(int num, char str[])
{
char lstr[30];
int cnt = 0;
int div = 10;
int j = 0;
int neg = 0;
	
	if(num<0)
	{
		num=-num;
		neg = 1;
	}

while( num >= div)
{
	lstr[cnt] = num % div + 0x30;
	num /= 10;
	cnt++;
}

	lstr[cnt] = num + 0x30;

	if(neg)
	{
		cnt++;
		lstr[cnt] = '-';
	}
for(j= cnt ; j >=0;j--)
{
	str[cnt-j] = lstr[j];
}

}

/*

6- Conver string to unsigned interger

*/

int char2int(char str[])
{
	int result = 0;
	int stop = 0;
	int Strlen = len_str(str);
	int j = 0;
	char check[1];
	
	for(j=0; j<= Strlen; j++)
	{
		check[0] = str[j];
		if(find_str(check, "0123456789") == 0)
		{
			stop = 1;
			break;
		}
	}
	if(stop == 0)
	{
		for(j=0; j<= Strlen;j++)
		{
			result = result *10 + (str[j] -0x30);
		}
	}
	
	return result;
}

