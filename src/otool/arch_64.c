/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 15:13:31 by tvisenti          #+#    #+#             */
/*   Updated: 2017/11/06 17:58:39 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int		compare_strx_64(char *stringtable, struct nlist_64 *array,
	uint32_t increment)
{
	if (ft_strcmp(stringtable + array[increment].n_un.n_strx,
		stringtable + array[increment + 1].n_un.n_strx) == 0 &&
		(array[increment].n_value != 0 || array[increment + 1].n_value != 0))
		return (1);
	return (0);
}

static void		sort_duplicate_strx_by_value_64(struct nlist_64 *array,
	char *stringtable, uint32_t size)
{
	struct nlist_64	tmp_value;
	int				sorted;
	uint32_t		increment;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		increment = 0;
		while (increment < size - 1)
		{
			if (compare_strx_64(stringtable, array, increment))
			{
				if (array[increment].n_value > array[increment + 1].n_value)
				{
					tmp_value = array[increment + 1];
					array[increment + 1] = array[increment];
					array[increment] = tmp_value;
					sorted = 0;
				}
			}
			++increment;
		}
	}
}

void			print_output_64(struct symtab_command *sym,
	struct mach_header_64 *header, char *ptr)
{
	uint32_t			i;
	struct load_command	*lc;
	char				*stringtable;
	struct nlist_64		*array;

	i = 0;
	lc = (void *)ptr + sizeof(*header);
	array = (void *)ptr + sym->symoff;
	stringtable = (void *)ptr + sym->stroff;
	if (check_range_addr(array) || check_range_addr(stringtable) ||
	check_range_addr(lc))
		return (print_error("file", "truncated or malformed object"));
	array = bubble_sort_64(stringtable, array, sym->nsyms);
	sort_duplicate_strx_by_value_64(array, stringtable, sym->nsyms);
	symtab_building_64(header, lc);
}

void			handle_64(char *ptr, char *file, int display)
{
	int						i;
	int						ncmds;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	i = -1;
	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	while (++i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			if (display)
				ft_printf("%s:\n", file);
			print_output_64(sym, header, ptr);
			break ;
		}
		if (check_range_addr(lc))
			return (print_error("file", "truncated or malformed object"));
		lc = (void *)lc + lc->cmdsize;
	}
}
