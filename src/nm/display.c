/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 13:21:09 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/30 11:24:03 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/*
** 1 / p = Don't sort; display in symbol-table order.
** 2 / r = Sort in reverse order.
** 3 / u = Display only undefined symbols.
** 4 / U = Don't display undefined symbols.
** 5 / j = Just display the symbol names (no value or type).
*/

void			display_output(struct nlist elem, char *str, t_symtab *symt)
{
	char		c;

	c = get_type(elem.n_type, elem.n_sect, elem.n_value, symt);
	if (ft_strcmp("radr://5614542", str) == 0)
		return ;
	if (g_bonus_nm == 5)
		ft_printf("%s\n", str);
	else if (g_bonus_nm != 4 && elem.n_value == 0 && (c == 'U' || c == 'u'))
	{
		if (g_bonus_nm == 3)
			ft_printf("%s\n", str);
		else if (ft_strcmp("__mh_execute_header", str) == 0)
			ft_printf("%08llx %c %s\n", elem.n_value, c, str);
		else
			ft_printf("%8c %c %s\n", ' ', c, str);
	}
	else if (g_bonus_nm != 3 && c != 'U' && c != 'u')
		ft_printf("%08llx %c %s\n", elem.n_value, c, str);
}

void			display_output_64(struct nlist_64 elem, char *str,
	t_symtab *symt)
{
	char		c;

	c = get_type(elem.n_type, elem.n_sect, elem.n_value, symt);
	if (ft_strcmp("radr://5614542", str) == 0)
		return ;
	if (g_bonus_nm == 5)
		ft_printf("%s\n", str);
	else if (g_bonus_nm != 4 && elem.n_value == 0 && (c == 'U' || c == 'u'))
	{
		if (g_bonus_nm == 3)
			ft_printf("%s\n", str);
		else if (ft_strcmp("__mh_execute_header", str) == 0)
			ft_printf("%016llx %c %s\n", elem.n_value, c, str);
		else
			ft_printf("%16c %c %s\n", ' ', c, str);
	}
	else if (g_bonus_nm != 3 && c != 'U' && c != 'u')
		ft_printf("%016llx %c %s\n", elem.n_value, c, str);
}

void			display_loop(struct nlist *array, char *stringtable,
	t_symtab symt, struct symtab_command *sym)
{
	long long	i;

	i = -1;
	if (g_bonus_nm == 2)
	{
		i = sym->nsyms;
		while (--i >= 0)
			display_output(array[i], stringtable + array[i].n_un.n_strx, &symt);
	}
	else
	{
		while (++i < sym->nsyms)
			display_output(array[i], stringtable + array[i].n_un.n_strx, &symt);
	}
}

void			display_loop_64(struct nlist_64 *array, char *stringtable,
	t_symtab symt, struct symtab_command *sym)
{
	long long	i;

	i = -1;
	if (g_bonus_nm == 2)
	{
		i = sym->nsyms;
		while (--i >= 0)
			display_output_64(array[i], stringtable + array[i].n_un.n_strx,
				&symt);
	}
	else
	{
		while (++i < sym->nsyms)
			display_output_64(array[i], stringtable + array[i].n_un.n_strx,
				&symt);
	}
}
