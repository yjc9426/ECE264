
#include "answer01.h"

// NOTE: You are NOT to use the strings library on this assignment,
// as stated in the README.

// DO NOT BEGIN WORKING ON THIS FILE UNTIL YOU HAVE COMPLETELY AND
// THOROUGHLY READ THE README FILE!!!

int arraySum(int * array, int len)
{
     int sum = 0;
     int i;
     for (i=0; i < len; i++)
     {
  		sum += array[i];
     }
     return sum;
}

int arrayCountNegative(int * array, int len)
{
	int counter = 0;
	int i;
	for (i=0; i < len; i++)
	{
		if (array[i] < 0)
		{
			counter++;
		}
	}
    return counter;
}

int arrayIsIncreasing(int * array, int len)
{
	if (len == 0)
	{
		return 1;
	}
	else	
	{
		int i;
		for (i=0; i < len-1; i++)
		{
			if (array[i] <= array[i+1])
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	return 0;
}

int arrayIndexRFind(int needle, const int * haystack, int len)
{
	int i;
	int index = -1;
	for (i = 0; i < len; i++)
	{
		if (haystack[i] == needle)
		{
			index = i;
		}
	}
     return index;
}

int arrayFindSmallest(int * array, int len)
{
	if (len == 0)
	{
      	return 0;
	}
	else
	{
		int i;
		int small = array[0];
		for ( i = 0; i < (len - 1); i++)
		{
			if(small >= array[i+1])
			{
				small = array[i+1];
			}

		}
		int index = arrayIndexRFind(small, array, len);
	
		return index;
	}
}

size_t my_strlen(const char * str)
{
	size_t counter = 0;
	while(*str != '\0')
	{
		str++;
		counter++;
	}
     return counter;
}

char * my_strchr(const char * str, int ch)
{
	while(*str != '\0')
	{
		if(*str == ch)
		{
			return (char *) str;
		}
		str++;
	}
	if(*str == '\0' && ch == '\0')
	{
		return (char *) str;
	}
    	return NULL;
}

char * my_strstr(const char * haystack, const char * needle)
{
	if ( *needle == '\0')
	{
		return (char *) haystack;
	}	
	while(*haystack != '\0')
	{	
		char * temp;
		char * temp2;
		if(*haystack == *needle)
		{
			
			temp = (char*) haystack;
			temp2 = (char*) needle;
			while(*temp != '\0' && *temp2 != '\0')
			{
				if(*temp == *temp2)
				{
					temp2++;
					temp++;
					if( (*temp2) == '\0' )
					{
						return (char*)haystack;
					}
				}
				else
				{
					break;
				}
			}
		}

		haystack++;

	}
	return NULL;
}

char * my_strcpy(char * dest, const char * src)
{
	while(*src != '\0' )
	{
		*dest = *src;
		dest++;
		src++;
	}
    	return dest;
}

char * my_strcat(char * dest, const char * src)
{
	while(*dest != '\0')
	{
		dest++;
	}
	while(*src != '\0')
	{
		*dest = *src;
		src++;
		dest++;
	}
    return dest;
}

int my_isspace(int ch)
{
	if(ch == ' ' || ch == '\f' || ch == '\n' || ch == '\r' || ch == '\t' || ch == '\v')
	{
		return 1;
	}

    return 0;
}

int my_atoi(const char * str)
{
	int ret = 0;
	int minus = 1;
	while ( my_isspace(*str) == 1)
	{
		str++;
	}
	if ( *str == '-')
	{
		minus = -1;
		str++;
	}
	
	while ( *str >= '0' && *str <= '9')
	{
		ret *= 10;
		ret += *str - '0';
		str++;
	}
	
	ret *= minus;
   	return ret;
}

