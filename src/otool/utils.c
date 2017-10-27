/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 14:50:27 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/26 16:02:42 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int			search_lst(t_offlist *lst, uint32_t off)
{
	t_offlist	*cur;

	cur = lst;
	while (cur)
	{
		if (cur->off == off)
			return (1);
		cur = cur->next;
	}
	return (0);
}
