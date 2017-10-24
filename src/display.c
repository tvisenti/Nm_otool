/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 13:21:09 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/24 11:10:44 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm_otool.h"

int				is_executable_file(void)
{
	if (g_stat.st_mode & S_IXUSR)
		return (1);
	return (0);
}

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
	if (elem.n_value == 0 && c == 'U')
	{
		if (ft_strcmp("__mh_execute_header", str) == 0)
			ft_printf("%08c %c %s\n", '0', c, str);
		else
			ft_printf("%8c %c %s\n", ' ', c, str);
	}
	else if (is_executable_file())
		ft_printf("%08x %c %s\n", elem.n_value, c, str);
	else
		ft_printf("%08x %c %s\n", elem.n_value, c, str);
}

void			display_output_64(struct nlist_64 elem, char *str,
	t_symtab *symt)
{
	char		c;

	c = get_type(elem.n_type, elem.n_sect, elem.n_value, symt);
	if (elem.n_value == 0 && c == 'U')
	{
		if (ft_strcmp("__mh_execute_header", str) == 0)
			ft_printf("%08c%08c %c %s\n", '1', '0', c, str);
		else
			ft_printf("%16c %c %s\n", ' ', c, str);
	}
	else if (is_executable_file())
		ft_printf("%08c%08x %c %s\n", '1', elem.n_value, c, str);
	else
		ft_printf("%016x %c %s\n", elem.n_value, c, str);
}
