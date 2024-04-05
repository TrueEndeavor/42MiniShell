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
#if DEBUG
printf("++++++++++++value_to_set = %s\n", value_to_set);
#endif
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
	#if DEBUG
	printf("@@@@@@@@@@@@@@within single quote=%c\n", (*expanded)[*i]);	
	#endif
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
				#if DEBUG
				printf("*expanded.............=%s\n",*expanded);
				#endif
				(*i) = (*i) + strlen(ft_itoa(core->exit_code)) - 1;
				#if DEBUG
				printf("*currently at.............=%s\n",*expanded+(*i));
				printf("core->exit_code=%d\n", core->exit_code);
				#endif
			}
			else
			{
				var_name = extract_variable_name(*expanded+(*i));
				var_value = get_env(core, var_name+1);
				#if DEBUG
				printf("++++++++++++value_to_set = %s\n", var_value);				
				#endif
				if (var_value)
				{
					int old_str_len = strlen(var_name);
					if (var_value != NULL)
					{
						replace_expanded_string(&(*expanded), i, old_str_len, var_value);
						#if DEBUG
						printf("*expanded.............=%s\n",*expanded);
						#endif
						(*i) = (*i) + strlen(var_value) - 1;
						#if DEBUG
						printf("*currently at.............=%s\n",*expanded+(*i));
						#endif
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
		#if DEBUG
		printf("*once again currently at.............=%s\n",*expanded+(*i));
		#endif
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
	#if DEBUG
	printf("*str= %s, i=%d\n", *str, i);
	#endif

	if (i < len)
	{
		ft_strlcpy(result, *str, i + 1);
		#if DEBUG
		printf("*result....= %s..and its length=%ld\n", result, strlen(result));
		printf("(*str + i + 1)= %s\n", (*str + i + 1));
		#endif
		ft_strlcpy(result + i, (*str + i + 1), (len - i +  1));
	}
	if (i == len)
		ft_strlcpy(result, *str, i);
	#if DEBUG
	printf("*result....again= %s and its length=%ld\n", result, strlen(result));
	#endif
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
		#if DEBUG
		printf("char----------on start of loop =%c\n", expanded[i]);
		#endif
		if (expanded[i] == '\'')
		{
			#if DEBUG
			printf("------------i=%d\n", i);
			printf("within single quote----------expanded =%c\n", expanded[i]);
			printf("first erase\n");
			#endif
			erase_char(&expanded, i);
			
			within_single_quote(&i, &expanded);
			#if DEBUG
			printf("second erase\n");
			#endif
			erase_char(&expanded, i);
			if (expanded[i] == '\0')
				break;
		}
		else if (expanded[i] == '\"')
		{
			#if DEBUG
			printf("first erase\n");
			#endif
			erase_char(&expanded, i);
			within_double_quote(&i, &expanded, core);
			#if DEBUG
			printf("second erase\n");
			#endif
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
					#if DEBUG
					printf("*expanded.............=%s\n",expanded);
					#endif
					i = i + strlen(ft_itoa(core->exit_code)) - 1;
					#if DEBUG
					printf("*currently at.............=%s\n",expanded+i);
					printf("core->exit_code=%d\n", core->exit_code);
					#endif
				}
				else if ((expanded)[i + 1] != '\'' && \
							(expanded)[i + 1] != '\"' )
				{
					var_name = extract_variable_name(expanded+i);
					var_value = get_env(core, var_name+1);
					#if DEBUG
					printf("++++++++++++value_to_set = %s\n", var_value);				
					#endif
					int old_str_len = strlen(var_name);
					if (var_value)
					{
						if (var_value != NULL)
						{
							replace_expanded_string(&expanded, &i, old_str_len, var_value);
							#if DEBUG
							printf("*expanded.............=%s\n",expanded);
							#endif
							i = i + strlen(var_value) - 1;
							#if DEBUG
							printf("*currently at.............=%s\n",expanded+i);
							#endif
						}
					}
					else
					{
						i++;
						erase_chars(&expanded, &i, old_str_len);
						//i = i + old_str_len;
					}
				}
			}
		}
		i++;
	}
	#if DEBUG
	printf("<In expand function >after expansion = %s\n",expanded);
	#endif
	*token_string = expanded;
}