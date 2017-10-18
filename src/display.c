/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 13:21:09 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/18 16:58:24 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm_otool.h"

int				print_error(char *file, char *str)
{
	ft_printf("ft_nm: %s: %s.\n", file, str);
	return (0);
}

char			type_n_sect(unsigned int n_sect)
{
	ft_printf("n_sect: %d\n", n_sect);
	if (n_sect == 1)
		return ('T');
	if (n_sect == 10)
		return ('D');
	if (n_sect == 3)
		return ('B');
	return ('S');
}

char			get_type(uint32_t type, uint32_t n_sect, int value)
{
	char c;

	c = type;
	if (c & N_STAB)
		return ('-');
	c = c & N_TYPE;
	if (c == N_UNDF && value != 0)
		c = 'C';
	else if ((c == N_UNDF && value == 0) || c == N_PBUD)
		c = 'U';
	else if (c == N_ABS)
		c = 'A';
	else if (c == N_SECT)
		c = type_n_sect(n_sect);
	else
		c = (c == N_INDR ? 'I' : '?');
	if (!(type & N_EXT))
		c = ft_tolower(c);
	return (c);
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
