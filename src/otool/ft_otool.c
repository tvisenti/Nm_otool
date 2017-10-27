/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 10:44:41 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/27 12:23:22 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

t_symtab		init_symtab(void)
{
	t_symtab	symt;

	symt.data = 0;
	symt.bss = 0;
	symt.text = 0;
	symt.ns = 1;
	return (symt);
}

int				print_error(char *av, char *str)
{
	ft_printf("ft_otool: %s: %s\n", av, str);
	exit(1);
}

int				ft_otool(char *ptr, char *file, int display)
{
	unsigned int	magic_number;
	struct ar_hdr	*ar;

	ar = (void*)ptr;
	magic_number = *(unsigned int *)ptr;
	if (magic_number == MH_MAGIC_64)
		handle_64(ptr, file, display);
	else if (magic_number == MH_MAGIC)
		handle_32(ptr, file, display);
	else if (!ft_strncmp(ptr, ARMAG, SARMAG))
		handle_lib(ptr, file);
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		handle_fat(ptr, magic_number);
	else
		print_error(file, "The file was not recognized as a valid object file");
	return (0);
}

int				loop_arg_otool(char *av)
{
	struct stat	buf;
	int			fd;
	void		*ptr;

	if ((fd = open(av, O_RDONLY)) < 0)
		return (print_error(av, "No such file or directory"));
	if (fstat(fd, &buf) < 0)
		return (print_error(av, "Error with fstat"));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
	== MAP_FAILED)
		return (print_error(av, "Is a directory"));
	ft_otool(ptr, av, 1);
	if (munmap(ptr, buf.st_size) < 0)
		return (print_error(av, "Error with munmap"));
	return (1);
}

int				main(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac > 2)
	{
		if (ft_strcmp(av[1], "-t") == 0)
		{
			while (av[++i])
				loop_arg_otool(av[i]);
		}
	}
	else
		print_error("av", "-t and argument are missing");
	return (0);
}
