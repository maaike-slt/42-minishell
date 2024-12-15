#include <stdio.h>

int	main(int argc, char **argv)
{
	size_t	i;

	i = 0;
	while (i < argc)
	{
		printf("argv[%zu] = %s\n", i, argv[i]);
		i++;
	}
	return (0);
}
