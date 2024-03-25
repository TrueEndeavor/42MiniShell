/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:13:38 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/25 19:13:20 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_variable(char *ret, char *var, int i)
{
	int	j;

	j = 0;
	if (var != NULL)
	{
		while ((var)[j] != '\0')
		{
			(ret)[i] = (var)[j];
			i++;
			j++;
		}
	}
	return ;
}

char	*get_name(char *str, int i)
{
	char		*ret;
	char		*copy;
	size_t		new_size;

	i++;
	ret = ft_calloc(1, sizeof(char));
	ret[0] = '\0';
	while (str[i] != '\0' && ((ft_isalnum(str[i])) || str[i] == '_'))
	{
		new_size = ft_strlen(ret) + 2;
		copy = ft_calloc(new_size, sizeof(char));
		ft_strlcpy(copy, ret, new_size);
		free(ret);
		ret = ft_calloc(new_size, sizeof(char));
		ft_strlcpy(ret, copy, new_size);
		ret[new_size - 2] = str[i];
		ret[new_size - 1] = '\0';
		free(copy);
		i++;
	}
	return (ret);
}

int	fill_values(char **str, char **name, char **var, t_core_struct *core)
{
	int	i;
	int	i_var;
	int	var_count;

	ft_initialize_tab(name, var);
	var_count = 0;
	i_var = 0;
	i = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '$')
		{
			name[i_var] = NULL;
			var[i_var] = NULL;
			name[i_var] = get_name(*str, i);
			i += (int)ft_strlen(name[i_var]);
			var[i_var] = dupl(get_env(core, name[i_var]));
			i_var++;
			var_count++;
		}
		i++;
	}
	return (var_count);
}

/* void	fill_string_old(char **str, char **name, char **var, char *ret)
{
	int	i;
	int	var_count;
	int	i_var;
	int flag;

	flag = 0;
	i = 0;
	var_count = 0;
	i_var = 0;
	while ((*str)[var_count] != '\0')
	{
	printf("(*str)[var_count]=%c\n", (*str)[var_count]);
		if ((*str)[var_count] == '\'')
		{
			if (flag == 0)
			{
				var_count++;
				flag = 1;
			}
			else if (flag == 1)
			{
				var_count++;
				flag = 0;
			}
		}
		else if ((*str)[var_count] == '\"')
		{
			if (flag == 0)
			{
				var_count++;
				flag = 2;
			}
			else if (flag == 2)
			{
				var_count++;
				flag = 0;
			}
		}
		else if ((*str)[var_count] == '$' && flag != 1)
		{
			copy_variable(ret, var[i_var], i);
			i += ft_slen(var[i_var]);
			var_count += (ft_slen(name[i_var]) + 1);
			i_var++;
		}
		ret[i] = (*str)[var_count];
		i++;
		var_count++;
	}
	ret[i] = '\0';
} */

/* void	fill_string(char **str, char **name, char **var, char *ret)
{
	int	i;
	int	var_count;
	int	i_var;
	int flag;

	flag = 0;
	i = 0;
	var_count = 0;
	i_var = 0;
	while ((*str)[var_count] != '\0')
	{
		if ((*str)[var_count] == '\'')
		{
			if (flag == 0)
			{
				flag = 1;
			}
			else if (flag == 1)
			{
				flag = 0;
			}
		}
		else if ((*str)[var_count] == '\"')
		{
			if (flag == 0)
			{
				flag = 2;
			}
			else if (flag == 2)
			{
				flag = 0;
			}
		}
		if ((flag != 1) && (*str)[var_count] == '$')
		{
			copy_variable(ret, var[i_var], i);
			i += ft_slen(var[i_var]);
			//printf("strlen after replace = %d\n",ft_slen(name[i_var]) + 1 );
			var_count += (ft_slen(name[i_var]) + 1);
			printf("after replace........(*str)[var_count]=%c\n", (*str)[var_count]);
			i_var++;
		}
		printf("flag = %d && char = %c\n", flag, (*str)[var_count]);
			
		if (!((flag == 2 || flag == 0) && ((*str)[var_count] == '\"')) || \
			!((flag == 1 || flag == 0) && ((*str)[var_count] == '\'')))
		{
				ret[i] = (*str)[var_count];
				printf("ret = %s\n", ret);
				i++;
		}
		if (((flag == 2) && ((*str)[var_count] == '\"')) || \
			((flag == 1) && ((*str)[var_count] == '\'')))
		{
			flag = 0;
		}
		var_count++;
	}
	ret[i] = '\0';
} */

void	fill_string(char **str, char **name, char **var, char *ret)
{
	int	i;
	int	var_count;
	int	i_var;
	int flag;
	bool singleQuoteOpen;
	bool doubleQuoteOpen;
	
	singleQuoteOpen = false;
	doubleQuoteOpen = false;
	flag = 0;
	i = 0;
	var_count = 0;
	i_var = 0;
	printf("(*str)=%s\n", (*str));		
	printf("(*ret)=%s\n", (ret));		
	while ((*str)[var_count] != '\0')
	{
		dprintf(1, "******start*****(*str)[var_count] = %c\n", (*str)[var_count]);
		if ((doubleQuoteOpen && ((*str)[var_count] == '\'')) || \
			(singleQuoteOpen && ((*str)[var_count] == '\'')))
		{
			var_count++;
		}
		else if ((*str)[var_count] == '\'')
		{
			dprintf(1, "' ' ' ' 'var_count = %d\n", var_count);
			dprintf(1, "' ' ' ' '(*str)[var_count] = %c\n", (*str)[var_count]);
			singleQuoteOpen = !singleQuoteOpen;
			ret[i] = (*str)[var_count];
            i++;
            continue ;
		}
		else if ((*str)[var_count] == '"')
		{
			var_count++;
			doubleQuoteOpen = !doubleQuoteOpen;	
			/* ret[i] = (*str)[var_count];
            i++; */
		}
		if (doubleQuoteOpen && (*str)[var_count] == '$')
		{
			dprintf(1, ">>>>>>>var[i_var] = %s\n", var[i_var]);
			dprintf(1, ">>>>>>>name[i_var] = %s\n", name[i_var]);
			copy_variable(ret, var[i_var], i);
			i += ft_slen(var[i_var]);
			dprintf(1, ">>>>>>>i = %d\n", i);
			var_count += (ft_slen(name[i_var]));
			dprintf(1, ">>>>>>>var_count = %d\n", var_count);
			dprintf(1, "after replace........(*str)[var_count]=%c\n", (*str)[var_count]);
			i_var++;
		}
		else
		{
			ret[i] = (*str)[var_count];
			i++;
			//var_count++;
		}
		if (doubleQuoteOpen || !singleQuoteOpen)
			var_count++;
	} 
	ret[i] = '\0';
}

char	*quote(char **s, t_core_struct *co, int var_c, int i)
{
	char	*ret;
	char	**name;
	char	**var;
	int		size;

	name = malloc(10 * sizeof(char *));
	var = malloc(10 * sizeof(char *));
	var_c = fill_values(s, name, var, co);
	if (var_c == -1)
		return (free_quotes(s, name, var));
	size = (int)ft_strlen(*s);
	i = 0;
	while (var_c != 0)
	{
		size += ft_slen(var[i]);
		size -= (ft_slen(name[i]) + 1);
		i++;
		var_c--;
	}
	ret = malloc ((size + 1) *(sizeof(char)));
	fill_string(s, name, var, ret);
	free_quotes(s, name, var);
	return (ret);
}
