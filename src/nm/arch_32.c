/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 15:13:31 by tvisenti          #+#    #+#             */
/*   Updated: 2017/11/01 10:02:44 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int		compare_strx(char *stringtable, struct nlist *array,
	uint32_t increment)
{
	if (ft_strcmp(stringtable + array[increment].n_un.n_strx,
		stringtable + array[increment + 1].n_un.n_strx) == 0 &&
		array[increment].n_value != 0 && array[increment + 1].n_value != 0)
		return (1);
	return (0);
}

static void		sort_duplicate_strx_by_value(struct nlist *array,
	char *stringtable, uint32_t size)
{
	uint32_t		tmp_value;
	int				sorted;
	uint32_t		increment;

	sorted = 0;
	tmp_value = 0;
	while (!sorted)
	{
		sorted = 1;
		increment = 0;
		while (increment < size - 1)
		{
			if (compare_strx(stringtable, array, increment))
			{
				if (array[increment].n_value > array[increment + 1].n_value)
				{
					tmp_value = array[increment + 1].n_value;
					array[increment + 1].n_value = array[increment].n_value;
					array[increment].n_value = tmp_value;
					sorted = 0;
				}
			}
			++increment;
		}
	}
}

void			print_output(struct symtab_command *sym,
	struct mach_header *header, char *ptr)
{
	uint32_t			i;
	struct load_command	*lc;
	char				*stringtable;
	struct nlist		*array;
	t_symtab			symt;

	symt = init_symtab();
	i = 0;
	lc = (void *)ptr + sizeof(*header);
	array = (void *)ptr + sym->symoff;
	stringtable = (void *)ptr + sym->stroff;
	if (check_range_addr(array) || check_range_addr(stringtable) ||
	check_range_addr(lc))
		return (print_error("file", "truncated or malformed object"));
	if (g_bonus_nm == 1)
		array = fill_array(array, sym->nsyms);
	else
		array = bubble_sort(stringtable, array, sym->nsyms);
	sort_duplicate_strx_by_value(array, stringtable, sym->nsyms);
	symtab_building(&symt, header, lc);
	display_loop(array, stringtable, symt, sym);
}

void			handle_32(char *ptr)
{
	int						i;
	int						ncmds;
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	i = -1;
	header = (struct mach_header *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	while (++i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			print_output(sym, header, ptr);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}
