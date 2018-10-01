/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_map_handler3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhilenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 16:01:45 by rkhilenk          #+#    #+#             */
/*   Updated: 2018/09/21 16:01:47 by rkhilenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			kostyl_len(t_cor *cor)
{
	int i;

	i = 0;
	while (cor->winner->prog_name[i] != '\0' && i < 120)
		i++;
	return (i);
}

void		gg_wp(t_cor *cor)
{
	int inp;

	breakdown(cor);
	refresh_vizu(cor);
	werase(cor->vizu->win1);
	win_art_sword(cor, 10);
	win_art_sword(cor, 144);
	win_art_winner(cor);
	mvwprintw(cor->vizu->win1, 20, 70 + ((48 - kostyl_len(cor))
	/ 2), "--> %s <--", cor->winner->prog_name);
	mvwprintw(cor->vizu->win1, 22, 88, "%s", "Press Space to exit");
	wrefresh(cor->vizu->win1);
	wrefresh(cor->vizu->win2);
	while (1)
	{
		inp = getchar();
		if (inp == 32 || inp == 27)
			return ;
	}
}

static void	v_speed_test2(t_cor *cor)
{
	if (cor->vizu->speed == 100000)
		mvwprintw(cor->vizu->win2, 30 + ((cor->vizu->end_of_prs - 1) * 4),
		2, "speed : >      ", cor->vizu->speed);
	else if (cor->vizu->speed == 50000)
		mvwprintw(cor->vizu->win2, 30 + ((cor->vizu->end_of_prs - 1) * 4),
		2, "speed : >>     ", cor->vizu->speed);
	else if (cor->vizu->speed == 20000)
		mvwprintw(cor->vizu->win2, 30 + ((cor->vizu->end_of_prs - 1) * 4),
		2, "speed : >>>    ", cor->vizu->speed);
	else if (cor->vizu->speed == 10000)
		mvwprintw(cor->vizu->win2, 30 + ((cor->vizu->end_of_prs - 1) * 4),
		2, "speed : >>>>   ", cor->vizu->speed);
	else if (cor->vizu->speed == 1000)
		mvwprintw(cor->vizu->win2, 30 + ((cor->vizu->end_of_prs - 1) * 4),
		2, "speed : max    ", cor->vizu->speed);
	else if (cor->vizu->speed == 500000)
		mvwprintw(cor->vizu->win2, 30 + ((cor->vizu->end_of_prs - 1) * 4),
		2, "speed : min    ", cor->vizu->speed);
}

void		v_speed_test(t_cor *cor, char t)
{
	if (t == '=' && cor->vizu->speed == 500000)
		cor->vizu->speed = 100000;
	else if (t == '=' && cor->vizu->speed == 100000)
		cor->vizu->speed = 50000;
	else if (t == '=' && cor->vizu->speed == 50000)
		cor->vizu->speed = 20000;
	else if (t == '=' && cor->vizu->speed == 20000)
		cor->vizu->speed = 10000;
	else if (t == '=' && cor->vizu->speed == 10000)
		cor->vizu->speed = 1000;
	if (t == '-' && cor->vizu->speed == 1000)
		cor->vizu->speed = 10000;
	else if (t == '-' && cor->vizu->speed == 10000)
		cor->vizu->speed = 20000;
	else if (t == '-' && cor->vizu->speed == 20000)
		cor->vizu->speed = 50000;
	else if (t == '-' && cor->vizu->speed == 50000)
		cor->vizu->speed = 100000;
	else if (t == '-' && cor->vizu->speed == 100000)
		cor->vizu->speed = 500000;
	v_speed_test2(cor);
}

void		refresher(t_cor *cor)
{
	int i;

	i = -1;
	while (++i < 4096)
	{
		if (cor->vizu->map[i].life_time > 0 && (cor->pause == 0
		|| cor->cycles < cor->start_from))
			cor->vizu->map[i].life_time--;
		if (cor->vizu->map[i].life_scream > 0 && (cor->pause == 0
		|| cor->cycles < cor->start_from))
		{
			cor->vizu->map[i].life_scream--;
		}
	}
}
