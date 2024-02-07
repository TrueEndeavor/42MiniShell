/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_manipulation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:48:48 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/07 19:10:46 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef enum TOKEN_TYPE_ENUM
{
	WORD,
	NAME,
	ASSIGNMENT_WORD,
	IO_NUMBER,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	HEREDOC,
	APPEND_OUT,
	LINEBREAK
}	t_Token_Type;

typedef struct TOKEN_STRUCT
{
	char				*value;
	t_Token_Type		type;
	struct TOKEN_STRUCT	*next;
}	t_Token;


void	print_linked_list(t_Token *head)
{
	t_Token	*current;

	printf("Current contents of the linked list: \n");
	current = head;
	while (current != NULL)
	{
		printf("Value: %s, Type: %d\n", current->value, current->type);
		current = current->next;
	}
}

void	peek_next(t_Token *head)
{
	if (head == NULL || head->next == NULL)
	{
		printf("No next element available.\n");
	}
	else
	{
		printf("Next element in the linked list: Value: %s, Type: %d\n",\
			head->next->value, head->next->type);
	}
}

void	insert(t_Token **head, char *value, t_Token_Type type)
{
	t_Token	*new;
	t_Token	*current;

	new = (t_Token *)malloc(sizeof(t_Token));
	new->value = value;
	new->type = type;
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new;
	}
}

void	free_linked_list(t_Token *head)
{
	t_Token	*current;
	t_Token	*temp;

	current = head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
}

int	main(void)
{
	t_Token	*head;

	head = NULL;
	insert(&head, "hello", WORD);
	insert(&head, "=", ASSIGNMENT_WORD);
	insert(&head, "world", WORD);
	print_linked_list(head);
	peek_next(head);
	free_linked_list(head);
	return (0);
}
