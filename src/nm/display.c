/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 13:21:09 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/26 11:11:51 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

char			type_n_sect(unsigned int n_sect, t_symtab *symt)
{
	if (n_sect == symt->text)
		return ('T');
	if (n_sect == symt->data)
		return ('D');
	if (n_sect == symt->bss)
		return ('B');
	return ('S');
}

char			get_type(uint32_t type, uint32_t n_sect, int value,
	t_symtab *symt)
{
	char		c;

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
		c = type_n_sect(n_sect, symt);
	else
		c = (c == N_INDR ? 'I' : '?');
	if (!(type & N_EXT))
		c = ft_tolower(c);
	return (c);
}

void			display_output(struct nlist elem, char *str, t_symtab *symt)
{
	char		c;

	c = get_type(elem.n_type, elem.n_sect, elem.n_value, symt);
	if (ft_strcmp("radr://5614542", str) == 0)
		return ;
	if (elem.n_value == 0 && (c == 'U' || c == 'u'))
	{
		if (ft_strcmp("__mh_execute_header", str) == 0)
			ft_printf("%08llx %c %s\n", elem.n_value, c, str);
		else
			ft_printf("%8c %c %s\n", ' ', c, str);
	}
	else
		ft_printf("%08llx %c %s\n", elem.n_value, c, str);
}

void			display_output_64(struct nlist_64 elem, char *str,
	t_symtab *symt)
{
	char		c;

	c = get_type(elem.n_type, elem.n_sect, elem.n_value, symt);
	if (ft_strcmp("radr://5614542", str) == 0)
		return ;
	if (elem.n_value == 0 && (c == 'U' || c == 'u'))
	{
		if (ft_strcmp("__mh_execute_header", str) == 0)
			ft_printf("%016llx %c %s\n", elem.n_value, c, str);
		else
			ft_printf("%16c %c %s\n", ' ', c, str);
	}
	else
		ft_printf("%016llx %c %s\n", elem.n_value, c, str);
}
