#include "unistd.h"
#include <stdio.h>

void	change(size_t *i)
{
	*i = 84;
}

int main(void)
{
	size_t	i;

	i = 42;
	printf("i: %zu\n", i);
	printf("addr: %p\n", &i);
	change(&i);
	printf("i: %zu\n", i);
	printf("addr: %p\n", &i);
}
