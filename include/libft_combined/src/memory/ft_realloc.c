/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:39:58 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/07 17:39:58 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *ptr, size_t size)
{
	char	*new_ptr;

	new_ptr = ft_calloc(size + 1, sizeof(char));
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		ft_strlcpy(new_ptr, ptr, size + 1);
		free(ptr);
	}
	return (new_ptr);
}
