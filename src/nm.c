/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:44:03 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/17 11:16:00 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm_otool.h"
#include <stdio.h>

void			print_output(int nsyms, int symoff, int stroff, char *ptr)
{
	int				i;
	char			*stringtable;
	struct nlist_64	*array;

	i = -1;
	array = (void *)ptr + symoff;
	stringtable = (void *)ptr + stroff;
	while (++i < nsyms)
	{
		printf("%s\n", stringtable + array[i].n_un.n_strx);
	}
}

void			handle_64(char *ptr)
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
			print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}

void			nm(char *ptr)
{
	int	magic_number;

	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64)
	{
		handle_64(ptr);
	}
}

int				print_error(char *str)
{
	ft_putstr(str);
	return (0);
}

int				loop_arg(char *av)
{
	struct stat	buf;
	int			fd;
	char		*ptr;

	if ((fd = open(av, O_RDONLY)) < 0)
		return (print_error("Error with open\n"));
	if (fstat(fd, &buf) < 0)
		return (print_error("Error with fstat\n"));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
	== MAP_FAILED)
		return (print_error("Error with mmap\n"));
	nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
		return (print_error("Error with munmap\n"));
	return (1);
}

int				main(int ac, char **av)
{
	int		i;
	char	*str;

	i = 1;
	str = NULL;
	if (ac < 2)
	{
		ft_putstr("Merci de rentrer au moins 1 fichier\n");
		return (EXIT_FAILURE);
	}
	while (av[i])
	{
		str = av[i];
		loop_arg(str);
		i++;
	}
	return (0);
}
