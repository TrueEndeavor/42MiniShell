/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 08:12:02 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/01 08:12:02 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*initialize_string(char **value)
{
	*value = ft_calloc(1, sizeof(char));
	if (!*value)
		return (NULL);
	(*value)[0] = '\0';
	return (*value);
}
char *read_string(t_lexer_T **lexer)
{
    char *value;
    bool quote_flag;

    quote_flag = false;
    initialize_string(&value);
    while (ft_isprint((*lexer)->c) &&
           (!quote_flag || ((*lexer)->c == '\'' || (*lexer)->c == '\"')))
    {
		#if DEBUG
		printf("quote flag =%d, lexer->c = %c$\n", quote_flag, (*lexer)->c);
		#endif
        if ((*lexer)->c == '\'' || (*lexer)->c == '\"')
            quote_flag = !quote_flag;
		else if (!quote_flag && (*lexer)->c == '\0')
            break;
        extend_string(&value, (*lexer)->c);
        lexer_advance(*lexer);
    }
    return (value);
}

bool	is_special_char(t_lexer_T *lexer)
{
	if (lexer->c == '|' || lexer->c == '<'
		|| lexer->c == '>' || lexer->c == '\0')
		return (true);
	return (false);
}

void	escape_quotes(t_lexer_T *lexer)
{
	char	quote;

	quote = 0;
	while (lexer->c && !(quote == 0 && isspace(lexer->c)))
	{
		if (lexer->c == '\'' || lexer->c == '\"')
		{
			if (quote == 0)
				quote = lexer->c;
			else if (quote == lexer->c)
				quote = 0;
		}
		if (is_special_char(lexer) && quote == 0)
			break ;
		lexer_advance(lexer);
	}
}

/**
 * Parses alphabets (word) from the shell command and creates a corresponding 
 * token
 *
 * This function is responsible for recognizing and creating a token for 
 * alphabets (word)
 * It iterates through the characters that form the identifier until
 * a non-alphabetic character is encountered
 *
 * @param lexer The lexer to parse with
 *
 * @return A token representing the parsed identifier
 */
t_token_T	*lexer_parse_word(t_lexer_T *lexer)
{
	t_token_T	*ret_token;
	char		*value;
	size_t	start;
	ssize_t	len;

	ret_token = NULL;
	/*if ((lexer->c) == '$' && (lexer_peek(lexer, 1) == '?'))
	{
		lexer_advance(lexer);
		lexer_advance(lexer);
		return (init_token(ft_strdup("$?"), T_EXITCODE));
	}*/
	start = lexer->i;
	escape_quotes(lexer);
	len = lexer->i - start;
	value = malloc(sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	ft_strlcpy(value, lexer->src + start, len + 1);
	//value = read_string(&lexer);
	#if DEBUG
	printf("............value =%s$\n", value);
	#endif
	if (!is_nested_quotes(value))
	{
		return (NULL);
	}
	ret_token = init_token(value, T_WORD);
	return (ret_token);
}
