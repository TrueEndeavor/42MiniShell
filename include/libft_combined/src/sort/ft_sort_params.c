/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:30:06 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/22 17:32:26 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* bubble sort like */
void	ft_sort_params(int count, char **param)
{
	int		i;
	int		j;
	char	*tmp;

	i = 1;
	while (i < count - 1)
	{
		j = 1;
		while (j < count - i)
		{
			if (ft_strcmp(param[j], param[j + 1]) > 0)
			{
				tmp = param[j + 1];
				param[j + 1] = param[j];
				param[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
