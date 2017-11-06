/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 10:44:41 by tvisenti          #+#    #+#             */
/*   Updated: 2017/11/06 17:59:39 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void			set_architecture(unsigned int magic_number)
{
	g_big_endian = 0;
	if (magic_number == MH_CIGAM_64 || magic_number == MH_CIGAM
		|| magic_number == FAT_CIGAM)
		g_big_endian = 1;
}

void			print_error(char *av, char *str)
{
	ft_printf("ft_otool: %s: %s\n", av, str);
	return ;
}

int				ft_otool(char *ptr, char *file, int display)
{
	unsigned int	magic_number;
	struct ar_hdr	*ar;

	ar = (void*)ptr;
	magic_number = *(unsigned int *)ptr;
	set_architecture(magic_number);
	if (magic_number == MH_MAGIC_64)
		handle_64(ptr, file, display);
	else if (magic_number == MH_MAGIC)
		handle_32(ptr, file, display);
	else if (!ft_strncmp(ptr, ARMAG, SARMAG))
		handle_lib(ptr, file);
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		handle_fat(ptr, file);
	else
		print_error(file, "The file was not recognized as a valid object file");
	return (0);
}

void			loop_arg_otool(char *av)
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
	g_buff_addr = ptr;
	g_buff_size = buf.st_size;
	ft_otool(ptr, av, 1);
	if (munmap(ptr, buf.st_size) < 0)
		return (print_error(av, "Error with munmap"));
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
