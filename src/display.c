/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 13:21:09 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/18 14:29:15 by tvisenti         ###   ########.fr       */
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

char			type_n_sect(unsigned int n_sect)
{
	if (n_sect == 1)
		return ('T');
	if (n_sect == 2)
		return ('D');
	if (n_sect == 3)
		return ('B');
	return ('S');
}

char			get_type(uint32_t type, uint32_t n_sect, int addr)
{
	char car;

	car = '?';
	if ((type & N_TYPE) == N_UNDF)
	{
		if (addr)
			car = 'C';
		else
			car = 'U';
	}
	else if ((type & N_TYPE) == N_ABS)
		car = 'A';
	else if ((type & N_TYPE) == N_SECT)
		car = type_n_sect(n_sect);
	else if ((type & N_TYPE) == N_PBUD)
		car = 'U';
	else if ((type & N_TYPE) == N_INDR)
		car = 'I';
	if (!(type & N_EXT) && car != '?')
		car = ft_tolower(car);
	return (car);
}

void			display_output(unsigned int value, char *str, unsigned int type, uint32_t n_sect)
{
	char		c;

	c = get_type(type, n_sect, value);
	if (value == 0)
		ft_printf("%16s %c %s\n", " ", c, str);
	else
		ft_printf("00000001%08s %c %s\n", ft_itoa_base(value, 16), c, str);
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
		display_output(array[i].n_value, stringtable + array[i].n_un.n_strx,
			array[i].n_type, array[i].n_sect);
}
