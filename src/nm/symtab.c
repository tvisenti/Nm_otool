/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 09:53:30 by tvisenti          #+#    #+#             */
/*   Updated: 2017/11/06 17:54:31 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void		symtab_building_bis(t_symtab *symt,
	struct segment_command *seg, struct section *sect)
{
	uint32_t	i;

	i = 0;
	while (i < seg->nsects)
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
		if (check_range_addr(sect))
			return (print_error("file", "truncated or malformed object"));
		sect = (void *)sect + sizeof(*sect);
		symt->ns++;
		i++;
	}
}

void			symtab_building(t_symtab *symt,
	struct mach_header *header, struct load_command *lc)
{
	uint32_t				i;
	struct segment_command	*seg;
	struct section			*sect;

	i = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			seg = (struct segment_command *)lc;
			sect = (struct section *)((void *)seg + sizeof(*seg));
			symtab_building_bis(symt, seg, sect);
		}
		if (check_range_addr(lc))
			return (print_error("file", "truncated or malformed object"));
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

static void		symtab_building_bis_64(t_symtab *symt,
	struct segment_command_64 *seg, struct section_64 *sect)
{
	uint32_t	i;

	i = 0;
	while (i < seg->nsects)
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
		if (check_range_addr(sect))
			return (print_error("file", "truncated or malformed object"));
		sect = (void *)sect + sizeof(*sect);
		symt->ns++;
		i++;
	}
}

void			symtab_building_64(t_symtab *symt,
	struct mach_header_64 *header, struct load_command *lc)
{
	uint32_t					i;
	struct segment_command_64	*seg;
	struct section_64			*sect;

	i = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)lc;
			sect = (struct section_64 *)((void *)seg + sizeof(*seg));
			symtab_building_bis_64(symt, seg, sect);
		}
		if (check_range_addr(lc))
			return (print_error("file", "truncated or malformed object"));
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}
