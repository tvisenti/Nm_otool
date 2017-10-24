/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 12:25:22 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/24 18:40:03 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int		ft_atoi(const char *str)
{
	int		i;
	int		compt;
	int		min;

	i = 0;
	compt = 0;
	min = 0;
	if (str == NULL)
		return (0);
	while (str[i] == ' ' || (str[i] >= 8 && str[i] <= 14))
		i++;
	if (str[i] == '-')
	{
		i++;
		min++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		compt = compt * 10;
		compt = compt + str[i] - '0';
		i++;
	}
	if (min > 0)
		return (-compt);
	return (compt);
}
