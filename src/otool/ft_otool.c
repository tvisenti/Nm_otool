/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 10:44:41 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/27 14:08:54 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int				print_error(char *av, char *str)
{
	ft_printf("ft_otool: %s: %s\n", av, str);
	return (0);
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
		handle_fat(ptr, magic_number, file);
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

	i = 0;
	if (ac > 1)
	{
		if (ft_strcmp(av[1], "-d") == 0)
		{
			g_bonus_otool = 1;
			i++;
		}
		else
			g_bonus_otool = 0;
		while (av[++i])
			loop_arg_otool(av[i]);
	}
	else
		print_error("[-d]", "<file .o / .a>");
	return (0);
}
