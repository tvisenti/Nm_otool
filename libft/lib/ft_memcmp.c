/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 11:15:06 by tvisenti          #+#    #+#             */
/*   Updated: 2015/12/06 13:27:46 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int			ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*save_s1;
	char	*save_s2;

	save_s1 = (char *)s1;
	save_s2 = (char *)s2;
	while (n != 0 && (unsigned char)*save_s1 == (unsigned char)*save_s2)
	{
		n--;
		save_s1++;
		save_s2++;
	}
	if (n == 0)
		return (0);
	else
		return ((unsigned char)*save_s1 - (unsigned char)*save_s2);
}
