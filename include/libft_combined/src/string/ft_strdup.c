/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:22:17 by lannur-s          #+#    #+#             */
/*   Updated: 2023/05/16 15:24:42 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new;
	size_t	len;

	if (!s)
	{
		return (NULL);
	}
	len = ft_strlen(s) + 1;
	new = malloc(sizeof(char) * len);
	if (!new)
		return (NULL);
	if (ft_strlcpy(new, s, len) >= len)
	{
		free(new);
		return (NULL);
	}
	return (new);
}
