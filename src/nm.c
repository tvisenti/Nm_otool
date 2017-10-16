/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:44:03 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/16 17:56:27 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/nm_otool.h"
#include <stdio.h>

void			handle_64(char *ptr)
{
	
}

void			nm(char *ptr)
{
	int			magic_number;

	magic_number = *(int *) ptr;
	if (magic_number == MH_MAGIC_64)
	{
		handle_64(ptr);
	}
}

int				loop_arg(char *av)
{
	struct stat	buf;
	int			fd;
	char		*ptr;

	if ((fd = open(av, O_RDONLY)) < 0)
	{
		ft_putstr("Error with open\n");
		return (0);
	}
	if (fstat(fd, &buf) < 0)
	{
		ft_putstr("Error with fstat\n");
		return (0);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		ft_putstr("Error with mmap\n");
		return (0);
	}
	nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
	{
		ft_putstr("Error with munmap\n");
		return (0);
	}
	return (1);
}

int				main(int ac, char **av)
{
	int			i;
	char		*str;

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
