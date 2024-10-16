




#include "minishell.h"

bool	do_put_in_string(t_values *v, char *var, int *i, int size_name_var)
{
	char *expand;
	int	index;

	if (check_var_exist(v, var, &index) == false)
	{
		if (put_in_string(&v->cmd_str, "", i, size_name_var) == false)
			return (false);
		return (true);
	}
	expand = get_expand(v->env[index]);
	if (put_in_string(&v->cmd_str, expand, i, size_name_var) == false)				// i is manipulated here
	{
		free(expand);
		return (false);
	}
	free(expand);
	return (true);
}
