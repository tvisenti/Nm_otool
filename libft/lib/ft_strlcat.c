/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 15:23:25 by tvisenti          #+#    #+#             */
/*   Updated: 2015/12/07 16:30:44 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*pdst;
	char	*psrc;
	size_t	n;
	size_t	len;

	pdst = dst;
	psrc = (char *)src;
	n = size;
	while (*pdst != '\0' && n-- != 0)
		pdst++;
	len = pdst - dst;
	n = size - len;
	if (n == 0)
		return (len + ft_strlen(src));
	while (*psrc != '\0')
	{
		if (n != 1)
		{
			*pdst++ = *psrc;
			n--;
		}
		psrc++;
	}
	*pdst = '\0';
	return (len + (psrc - src));
}
