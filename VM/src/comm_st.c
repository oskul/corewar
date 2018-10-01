/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comm_st.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vibondar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 20:42:05 by vibondar          #+#    #+#             */
/*   Updated: 2018/09/20 20:42:06 by vibondar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int			arg_read(t_cor *cor, t_process *process)
{
	int s;

	s = 2;
	if (process->arg1 != 1 || process->arg2 == 2)
		process->codage = 0;
	process->arg_type[0] = process->arg1;
	process->arg_type[1] = process->arg2;
	process->arg_type[2] = process->arg3;
	s = arg_handler(cor, process, &process->arg1, s);
	s = arg_handler(cor, process, &process->arg2, s);
	return (s);
}

static void			st_a_arg(t_cor *cor, t_process *process)
{
	if (process->arg_type[1] == 3)
	{
		if (process->arg1 > 0 && process->arg1 < 17)
		{
			if (cor->visu == 0 && cor->dump == 0 && cor->s == 0 &&
				(cor->mon == cor->cycles || cor->log == 1))
				ft_printf("P% 5d | st r%d %d\n", process->count_num,
					process->arg1, process->ind_loc);
			load_from_reg(cor, process, process->pc +
				(process->ind_loc % IDX_MOD), process->arg1 - 1);
		}
	}
	else
	{
		if (process->arg1 > 0 && process->arg2 > 0 &&
			process->arg1 < 17 && process->arg2 < 16)
		{
			if (cor->visu == 0 && cor->dump == 0 && cor->s == 0 &&
				(cor->mon == cor->cycles || cor->log == 1))
				ft_printf("P% 5d | st r%d %d\n", process->count_num,
					process->arg1, process->arg2);
			process->registr[process->arg2 - 1] =
			process->registr[process->arg1 - 1];
		}
	}
}

void				comm_st(t_cor *cor, t_process *process)
{
	int sk;

	if (process->delay < 0)
		process->delay = 4;
	else if (process->delay > 0)
		process->delay--;
	if (process->delay == 0)
	{
		process->label = 4;
		codage_identify(process, get_char(cor, process->pc + 1));
		process->codage = 1;
		process->ind_loc = -1;
		sk = arg_read(cor, process);
		if (process->codage == 1)
			st_a_arg(cor, process);
		set_proc_pos(cor, process, sk);
		process->delay = -1;
		process->command = -1;
	}
}
