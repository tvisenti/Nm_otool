/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:44:03 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/31 17:46:47 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int				check_range_addr(void *ptr)
{
	if (ptr <= (g_buff_addr + g_buff_size))
		return (0);
	return (1);
}

t_symtab		init_symtab(void)
{
	t_symtab	symt;

	symt.data = 0;
	symt.bss = 0;
	symt.text = 0;
	symt.ns = 1;
	return (symt);
}

void			ft_nm(void *ptr, char *file)
{
	unsigned int	magic_number;
	struct ar_hdr	*ar;

	ar = (void*)ptr;
	magic_number = *(unsigned int *)ptr;
	set_architecture(magic_number);
	if (!ft_strncmp(ptr, ARMAG, SARMAG))
		handle_lib(ptr, file);
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		handle_fat(ptr, file);
	else if (magic_number == MH_MAGIC_64)
		handle_64(ptr);
	else if (magic_number == MH_MAGIC)
		handle_32(ptr);
	else
		print_error(file, "The file was not recognized as a valid object file");
}

void			loop_arg(char *av)
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
	ft_nm(ptr, av);
	if (munmap(ptr, buf.st_size) < 0)
		return (print_error(av, "Error with munmap"));
}

int				main(int ac, char **av)
{
	int		i;
	char	*str;

	i = 1;
	str = NULL;
	if (ac == 1)
		loop_arg("a.out");
	else if (ft_strchr(av[1], '-'))
	{
		check_bonus(av[1]);
		i = g_bonus_nm != 0 ? i++ : i;
	}
	while (i < ac)
	{
		if (((ac == 3 && g_bonus_nm == 0) || ac > 3) &&
		(av[i][ft_strlen(av[i]) - 1] != 'a'))
			ft_printf("\n%s:\n", av[i]);
		str = av[i];
		loop_arg(str);
		i++;
	}
	return (0);
}
