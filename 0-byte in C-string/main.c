// Micro-exp.: "0-byte in C-string"
// The exp. shows, how are C-strings placed in memory (including 0-byte)
// In the first place the experiment had to show if there has to be more than one 0-byte in the end of the C-string

#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
	char* str = "C-string";

	// Prints the string itself and it's chars in unsigned decimal format memory addresses of its
	printf("\"%s\"\n", str);
	for (int i = 0; i < strlen(str) + 10; ++i)
	{
		// Example: " 0. 00000076341FFE57   67"
		printf("%2i. %p %4hhu\n", i, str + i, str[i]);
	}
}

// Just another way to do the same thing

/*
int main(int argc, char** argv)
{
	char str[] = "C-string";

	char* c = &str[0]; 
	// De-facto it is the same thing as "char* c = str;",
	// cause the "str"-variable (formally, array)
	// technically is a pointer to the first member of the array

	printf("\"%s\"\n", str);

	for (int i = 0; i < strlen(str) + 10; ++i, ++c)
	{
		printf("%2i. %p %4hhu\n", i, str + i, *(str + i));
		// As the "str"-variable is technically a pointer, "(str + i)" is a pointer
		// to the i-th memory cell after "str" memory cell (pointer to i-th element in array),
		// so *(str + i) is dereference of this pointer: so it's just another form of str[i]
	}
}
*/