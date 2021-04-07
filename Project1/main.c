
#include <stdio.h>
void main()
{
	int x = 77;
	char num_string[4];
	itoa(x, num_string, 16);
	printf("%s\n", num_string);
	strcpy(num_string,"aaa");
	printf("%s\n",num_string);
	printf("Hello from C using VS\n");
}
