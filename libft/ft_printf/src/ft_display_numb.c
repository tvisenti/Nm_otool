/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_numb.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/30 15:41:52 by tvisenti          #+#    #+#             */
/*   Updated: 2016/06/08 08:25:23 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

/*
**		 Precision > strlen(arg) : mets des '0'
*/

void	pf_ft_precision_without_width(t_flag *f)
{
	int	len;
	int	prec;

	prec = f->fla[0];
	len = pf_ft_strlen(f->arg);
	pf_ft_space_plus_sharp(f);
	while (prec > len-- && len > 0)
		prec--;
	if (f->fla[0] > f->fla[1] + pf_ft_strlen(f->arg))
	{
		while (++len < prec)
			pf_ft_buf('0', f);
	}
}

/*
** 		Calcul et insere dans g_buf le bon nombre de '0' ou ' '
*/

void	pf_ft_precision_numb(t_flag *f, int len_zero)
{
	int	len;

	len = pf_ft_strlen(f->arg);
	if (f->fla[5] == 1 || f->fla[6] == 1 || f->sign == '-' || (f->fla[2] == 1 &&
		f->fla[0] <= len && (f->spe == 'o' || f->spe == 'O')))
		len_zero--;
	if (f->fla[2] == 1 && (f->spe == 'x' || f->spe == 'X' || f->spe == 'p'))
		len_zero = len_zero - 2;
	while (f->fla[0] > len++)
		len_zero--;
	if (f->fla[0] < f->fla[1] + pf_ft_strlen(f->arg))
	{
		while (len_zero-- > 0)
		{
			if (f->fla[3] == 1 && f->fla[0] == 0)
				pf_ft_buf('0', f);
			else
				pf_ft_buf(' ', f);
		}
	}
}

/*
** 			Traite le flag '0' et mets l'arg dans le g_buf en fonction
*/

void	pf_ft_zero_numb(t_flag *f)
{
	int		i;
	int		len;
	int		len_zero;

	i = -1;
	len = pf_ft_strlen(f->arg);
	len_zero = f->fla[1] - len;
	if (f->fla[3] == 1)
	{
		pf_ft_space_plus_sharp(f);
		pf_ft_precision_numb(f, len_zero);
	}
	else
	{
		pf_ft_precision_numb(f, len_zero);
		pf_ft_space_plus_sharp(f);
	}
	while (f->fla[0] > len++)
		pf_ft_buf('0', f);
	while (f->arg[++i] != '\0')
		pf_ft_buf(f->arg[i], f);
}

/*
** 			Traite le flag '-' et mets l'arg dans le g_buf
*/

void	pf_ft_minus_numb(t_flag *f)
{
	int		i;
	int		len;
	int		len_zero;

	i = -1;
	len_zero = f->fla[1] - pf_ft_strlen(f->arg);
	len = pf_ft_strlen(f->arg);
	f->fla[3] = 0;
	pf_ft_space_plus_sharp(f);
	while (f->fla[0] > len++)
		pf_ft_buf('0', f);
	while (f->arg[++i] != '\0')
		pf_ft_buf(f->arg[i], f);
	pf_ft_precision_numb(f, len_zero);
}

/*
** 		Dispatche en fonction de la width du moins et du 0, si aucun flag
**		mets dans le g_buff
*/

void	pf_ft_width_numb(t_flag *f)
{
	int	i;
	int	len;

	i = -1;
	len = pf_ft_strlen(f->arg);
	if (len < f->fla[1])
	{
		if (f->fla[4] == 1)
			pf_ft_minus_numb(f);
		else
			pf_ft_zero_numb(f);
	}
	else
	{
		pf_ft_space_plus_sharp(f);
		while (f->fla[0] > len++)
			pf_ft_buf('0', f);
		while (f->arg[++i] != '\0')
			pf_ft_buf(f->arg[i], f);
	}
}
