/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 15:13:31 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/25 17:13:56 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm_otool.h"

static void		symtab_building_bis(t_symtab *symt,
	struct segment_command *seg, struct section *sect)
{
	int			i;

	i = -1;
	while (++i < seg->nsects)
	{
		if (ft_strcmp(sect->sectname, SECT_TEXT) == 0 &&
		ft_strcmp(sect->segname, SEG_TEXT) == 0)
			symt->text = symt->ns;
		else if (ft_strcmp(sect->sectname, SECT_DATA) == 0 &&
		ft_strcmp(sect->segname, SEG_DATA) == 0)
			symt->data = symt->ns;
		else if (ft_strcmp(sect->sectname, SECT_BSS) == 0 &&
		ft_strcmp(sect->segname, SEG_DATA) == 0)
			symt->bss = symt->ns;
		sect = (void *)sect + sizeof(*sect);
		symt->ns++;
	}
}

void			symtab_building(t_symtab *symt,
	struct mach_header *header, struct load_command *lc)
{
	int						i;
	struct segment_command	*seg;
	struct section			*sect;

	i = -1;
	while (++i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			seg = (struct segment_command *)lc;
			sect = (struct section *)((void *)seg + sizeof(*seg));
			symtab_building_bis(symt, seg, sect);
		}
		lc = (void *)lc + lc->cmdsize;
	}
}

static void    sort_duplicate_strx_by_value(struct nlist *array, char *stringtable, struct load_command *lc, uint32_t size)
{
    uint64_t        tmp_value;
    int                sorted;
    int                increment;

    sorted = 0;
    tmp_value = 0;
    increment = 0;
    while (!sorted)
    {
        sorted = 1;
        increment = 0;
        while (increment < size - 1)
        {
            if (ft_strcmp(stringtable + array[increment].n_un.n_strx, stringtable + array[increment + 1].n_un.n_strx) == 0)
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
	int					i;
	struct load_command	*lc;
	char				*stringtable;
	struct nlist		*array;
	t_symtab			symt;

	symt = init_symtab(symt);
	i = -1;
	lc = (void *)ptr + sizeof(*header);
	array = (void *)ptr + sym->symoff;
	stringtable = (void *)ptr + sym->stroff;
	array = bubble_sort(stringtable, array, sym->nsyms);
	sort_duplicate_strx_by_value(array, stringtable, lc, sym->nsyms);
	symtab_building(&symt, header, lc);
	while (++i < sym->nsyms)
		display_output(array[i], stringtable + array[i].n_un.n_strx, &symt);
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
