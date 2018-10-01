/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_cheker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vibondar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 20:44:56 by vibondar          #+#    #+#             */
/*   Updated: 2018/09/20 20:44:58 by vibondar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				wasted_live(t_cor *cor)
{
	t_process *tmp;

	tmp = cor->process;
	while (tmp)
	{
		tmp->live = 0;
		tmp = tmp->next;
	}
}

void				search_and_delete(t_cor *cor)
{
	static t_process	*prev = NULL;
	t_process			*tmp;

	tmp = cor->process;
	while (tmp)
	{
		if (tmp->live == 0)
		{
			if (cor->visu == 1)
				cor->vizu->map[tmp->pc].type = 0;
			prev->next = tmp->next;
			free(tmp);
			tmp = prev->next;
			cor->alive_cur--;
			continue;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void				del_in_start(t_cor *cor)
{
	t_process *tmp;

	tmp = cor->process;
	while (tmp)
	{
		tmp = cor->process;
		if (tmp->live == 1)
			break ;
		del_first(cor);
	}
}

void				cycle_end(t_cor *cor)
{
	cor->cycles++;
	cor->alive_cur = 0;
	if (cor->visu == 1)
	{
		cor->vizu->key = getch();
		v_speed_test(cor, cor->vizu->key);
		breakdown(cor);
		refresher(cor);
		if (cor->vizu->key == 32 && cor->pause == 1)
			cor->pause = 0;
		else if (cor->vizu->key == 32 && cor->pause == 0)
			cor->pause = 1;
		if (cor->cycles > cor->start_from)
			refresh_vizu(cor);
	}
	wasted_live1(cor);
	end_game(cor);
}

void				live_cheker(t_cor *cor)
{
	if (cor->live_check == cor->curr_cycle_t_d)
	{
		max_live(cor);
		del_in_start(cor);
		search_and_delete(cor);
		wasted_live(cor);
		if (!cor->process)
			end_game(cor);
		max_ch(cor);
		cor->live_check = 1;
		if (cor->curr_cycle_t_d < 0)
		{
			cor->cycles++;
			if (cor->visu == 0 && cor->dump == 0 && cor->s == 0 &&
				(cor->mon == cor->cycles || cor->log == 1))
				ft_printf("It is now cycle %d\n", cor->cycles);
			process_activity(cor);
			flag_output(cor);
			if (cor->cycles == cor->mon && cor->log == 0 && cor->visu == 0)
				exit(0);
			cycle_end(cor);
		}
	}
	else
		cor->live_check++;
}
