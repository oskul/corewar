/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vibondar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 20:44:23 by vibondar          #+#    #+#             */
/*   Updated: 2018/09/20 20:44:25 by vibondar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void						add_player(t_cor *cor, t_player *player, int k)
{
	t_process	*tmp;
	t_process	*new;

	tmp = cor->process;
	if (!tmp)
	{
		cor->process = player_b(cor, player, k);
		draw_palyer_info(cor, cor->process, k);
		return ;
	}
	new = player_b(cor, player, k);
	new->next = cor->process;
	cor->process = new;
	draw_palyer_info(cor, new, k);
}

void						add_players(t_cor *cor)
{
	int k;

	k = 0;
	cor->def_num = 1;
	while (cor->def_num < 5)
	{
		while (k < cor->p_num)
		{
			if (cor->def_num == cor->player[k].num)
			{
				add_player(cor, cor->player, k);
				break ;
			}
			k++;
		}
		k = 0;
		cor->def_num++;
	}
}

void						data_to_arena(t_cor *cor, int pos,
	t_process *proc, unsigned int size)
{
	unsigned int i;

	i = 0;
	while (i < size)
	{
		cor->arena[pos + i] = proc->player->code[i];
		if (cor->visu == 1)
		{
			cor->vizu->map[pos + i].comm = proc->player->code[i];
			cor->vizu->map[pos + i].player = proc->player->num * (-1);
		}
		i++;
	}
	if (cor->visu == 1)
		cor->vizu->map[pos].type = 1;
}

inline static void			to_norm(t_cor *cor, t_process *tmp, int pos)
{
	data_to_arena(cor, pos, tmp, tmp->player->prog_size);
	if (cor->visu == 0)
		ft_printf("* Player %d, weighing %d bytes, \"%s\" \
(\"%s\") !\n", tmp->player->num * (-1),
tmp->player->prog_size, tmp->player->prog_name,
tmp->player->comment);
	tmp->pc = pos;
}

void						game_init(t_cor *cor)
{
	int			pos;
	int			num_pl;
	t_process	*tmp;

	pos = 0;
	num_pl = -1;
	tmp = cor->process;
	if (cor->visu == 0)
		ft_putstr("Introducing contestants...\n");
	while (num_pl > -5)
	{
		tmp = cor->process;
		while (tmp)
		{
			if (num_pl == tmp->player->num)
			{
				to_norm(cor, tmp, pos);
				pos += MEM_SIZE / cor->p_num;
			}
			tmp = tmp->next;
		}
		num_pl--;
	}
}
