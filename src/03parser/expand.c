/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:58:05 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/28 08:58:05 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_variable_name(char *str)
{
	char	*end;

	if (str != NULL)
	{
		end = str + 1;
		while (*end != '\0' && (isalnum(*end) || *end == '_') && (*end != '$' || !ft_iswhitespace(*end)))
		{
			end++;
		}
		size_t length = end - str;
		char *substring = malloc((length + 1) * sizeof(char));
		if (substring != NULL) 
		{
			ft_strlcpy(substring, str, length + 1);
			substring[length] = '\0';
		}
		return substring;
	} else {
		return NULL;
	}
}
void replace_expanded_string(char **original, int *i, int old_str_len, char *value_to_set)
{
	char *new_expanded;
	int	new_str_len;

	new_str_len = strlen(*original) - old_str_len + strlen(value_to_set);
	new_expanded = calloc(new_str_len, sizeof(char));
	if (!new_expanded)
		return ;

printf("++++++++++++value_to_set = %s\n", value_to_set);
	ft_strlcpy(new_expanded, *original, (*i + 1));
	ft_strlcpy((new_expanded+(*i)), value_to_set, strlen(value_to_set) + 1);
	ft_strlcpy((new_expanded+(*i)+(strlen(value_to_set))), (*original)+(*i + old_str_len), (strlen(*original) + 1));	
	*original = new_expanded;
}

void    within_single_quote(int *i, char **expanded)
{
	while ((*expanded)[*i] != '\0')
	{
		if ((*expanded)[*i] == '\'')
		{
			break ;
		}
	printf("@@@@@@@@@@@@@@within single quote=%c\n", (*expanded)[*i]);	
		(*i)++;
	}
}

void    within_double_quote(int *i, char **expanded, t_core_struct *core)
{
	char *var_name;
	char *var_value;
	
	while ((*expanded)[*i] != '\0')
	{
		if ((*expanded)[*i] == '\"')
		{
			break ;
		}
		else if ((*expanded)[*i] == '$')
		{
			if ((*expanded)[*i + 1] == '?')
			{
				replace_expanded_string(&(*expanded), i, 2, ft_itoa(core->exit_code));
				printf("*expanded.............=%s\n",*expanded);
				(*i) = (*i) + strlen(ft_itoa(core->exit_code)) - 1;
				printf("*currently at.............=%s\n",*expanded+(*i));
				printf("core->exit_code=%d\n", core->exit_code);
			}
			else
			{
				var_name = extract_variable_name(*expanded+(*i));
				var_value = get_env(core, var_name+1);
printf("++++++++++++value_to_set = %s\n", var_value);				
				if (var_value)
				{
					int old_str_len = strlen(var_name);
					if (var_value != NULL)
					{
						replace_expanded_string(&(*expanded), i, old_str_len, var_value);
						printf("*expanded.............=%s\n",*expanded);
						(*i) = (*i) + strlen(var_value) - 1;
						printf("*currently at.............=%s\n",*expanded+(*i));
					}
					else
						(*i) = (*i)	 + old_str_len;
					//dprintf(1, "after replacing, var_count is set on this char\n");
				// skip number of i, if not replaced
				// len of var_name
				// if replaced
				// len of var_value
				}
			}
		}
		(*i)++;
		printf("*once again currently at.............=%s\n",*expanded+(*i));
	}
}

void erase_char(char **str, int i)
{
	int	len;
	char	*result;
	if (!str || !(*str) || i < 0)
		return ;

	len = strlen(*str);
	if (i > len)
		return ;
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return ;
	printf("*str= %s, i=%d\n", *str, i);

	if (i < len)
	{
		ft_strlcpy(result, *str, i + 1);
		printf("*result....= %s..and its length=%ld\n", result, strlen(result));
		printf("(*str + i + 1)= %s\n", (*str + i + 1));
		ft_strlcpy(result + i, (*str + i + 1), (len - i +  1));
	}
	if (i == len)
		ft_strlcpy(result, *str, i);
	printf("*result....again= %s and its length=%ld\n", result, strlen(result));
	result[len] = '\0';
	free(*str);
	*str = result;
}

void erase_chars(char **str, int *i, int n)
{
    int len;
    char *result;
    if (!str || !(*str) || *i < 0 || n <= 0)
        return;

    len = strlen(*str);
    if (*i >= len)
        return;

    if (*i + n > len)
        n = len - (*i); // Adjust n if it exceeds the length of the string

    result = ft_calloc(len - n + 1, sizeof(char)); // Allocate memory for the result string
    if (!result)
        return;

    // Copy the portion of the string before the characters to be removed
    ft_strlcpy(result, *str, (*i) + 1);

    // Copy the portion of the string after the characters to be removed
    ft_strlcpy(result + (*i), (*str + (*i) + n), (len - (*i) - n + 1));

    // Update the pointer to the new string
    free(*str);
    *str = result;
}

void	expand_variables(char **token_string, t_core_struct *core)
{
	char	*expanded;
	char	*var_name;
	char	*var_value;
	int	i;

	i = 0;
	expanded = calloc(strlen(*token_string) + 1, sizeof(char));
	if (!expanded)
		return ;
	expanded = ft_strdup(*token_string);

	while (expanded[i] != '\0')
	{
		printf("char----------on start of loop =%c\n", expanded[i]);
		if (expanded[i] == '\'')
		{
			printf("------------i=%d\n", i);
			printf("within single quote----------expanded =%c\n", expanded[i]);
			printf("first erase\n");
			erase_char(&expanded, i);
			
			within_single_quote(&i, &expanded);
			printf("second erase\n");
			erase_char(&expanded, i);
			if (expanded[i] == '\0')
				break;
		}
		else if (expanded[i] == '\"')
		{
			printf("first erase\n");
			erase_char(&expanded, i);
			within_double_quote(&i, &expanded, core);
			printf("second erase\n");
			erase_char(&expanded, i);
			if (expanded[i] == '\0')
				break ;
		}
		else
		{
			if ((expanded)[i] == '$')
			{
				//erase_char(&expanded, i);
				if ((expanded)[i + 1] == '?')
				{
					replace_expanded_string(&expanded, &i, 2, ft_itoa(core->exit_code));
					printf("*expanded.............=%s\n",expanded);
					i = i + strlen(ft_itoa(core->exit_code)) - 1;
					printf("*currently at.............=%s\n",expanded+i);
					printf("core->exit_code=%d\n", core->exit_code);
				}
				else if ((expanded)[i + 1] != '\'' && \
							(expanded)[i + 1] != '\"' )
				{
					var_name = extract_variable_name(expanded+i);
					var_value = get_env(core, var_name+1);
	printf("++++++++++++value_to_set = %s\n", var_value);				
					int old_str_len = strlen(var_name);
					if (var_value)
					{
						if (var_value != NULL)
						{
							replace_expanded_string(&expanded, &i, old_str_len, var_value);
							printf("*expanded.............=%s\n",expanded);
							i = i + strlen(var_value) - 1;
							printf("*currently at.............=%s\n",expanded+i);
						}
					}
					else
					{
						printf("segcoucou\n");
						erase_chars(&expanded, &i, old_str_len);
						//i = i + old_str_len;
					}
				}
			}
		}
		i++;
	}
	printf("<In expand function >after expansion = %s\n",expanded);
	*token_string = expanded;
}