/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 11:28:35 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/27 12:21:49 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../inc/libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(char) * len + 1);
	if (new == NULL || start > ft_strlen(s))
		return (NULL);
	while (i < start)
		i++;
	while (s[i] && j < len)
	{
		new[j] = ((char *)s)[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (new);
}
