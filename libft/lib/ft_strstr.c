/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 14:39:34 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/24 18:39:05 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static char		*ft_resostr(const char *s1, const char *s2)
{
	int			i;
	int			cnt;
	char		*tmp;

	i = 0;
	cnt = 0;
	while (s1[i] != 0)
	{
		while (s1[i] == s2[cnt])
		{
			i++;
			cnt++;
			if (s2[cnt] == 0)
			{
				tmp = (char *)&s1[i - cnt];
				return (tmp);
			}
		}
		cnt = 0;
		i++;
	}
	return (NULL);
}

char			*ft_strstr(const char *s1, const char *s2)
{
	char	*tmp;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (*s2 == '\0')
		tmp = (char *)s1;
	else
		tmp = ft_resostr(s1, s2);
	return (tmp);
}
