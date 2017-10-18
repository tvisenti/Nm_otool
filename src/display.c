/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 13:21:09 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/18 13:26:34 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm_otool.h"

int				print_error(char *file, char *str)
{
	ft_putstr("ft_nm: ");
	ft_putstr(file);
	ft_putstr(str);
	return (0);
}

char			get_type(unsigned int type)
{
	char		c;

	c = '?';
	if ((type & ) == )
		c = '';
	else if ((type & ) == )
		c = '';
	else if ((type & ) == )
		c = '';
	else if ((type & ) == )
		c = '';
	if ((type & ) == )
		c = '';
}

void			display_output(unsigned int value, char *str, unsigned int type)
{
	char		c;

	c = get_type(type);
	if (value == 0)
		ft_printf("%16s U %s\n", " ", str);
	else
		ft_printf("00000001%08s T %s\n", ft_itoa_base(value, 16), str);
}

void			print_output(int nsyms, int symoff, int stroff, char *ptr)
{
	int				i;
	char			*stringtable;
	struct nlist_64	*array;

	i = -1;
	array = (void *)ptr + symoff;
	stringtable = (void *)ptr + stroff;
	array = tri_bulle(stringtable, array, nsyms);
	while (++i < nsyms)
		display_output(array[i].n_value, stringtable + array[i].n_un.n_strx, array[i].n_type);
}
