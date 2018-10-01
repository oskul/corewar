/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comm_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vibondar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 20:40:28 by vibondar          #+#    #+#             */
/*   Updated: 2018/09/20 20:40:30 by vibondar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	arg_read(t_cor *cor, t_process *process)
{
	int s;

	s = 2;
	codage_identify(process, get_char(cor, process->pc + 1));
	process->codage = 1;
	if (process->arg1 != 1 || process->arg3 != 1 || process->arg2 != 1)
		process->codage = 0;
	s = arg_handler(cor, process, &process->arg1, s);
	s = arg_handler(cor, process, &process->arg2, s);
	s = arg_handler(cor, process, &process->arg3, s);
	return (s);
}

static void	reg_reg_reg(t_cor *cor, t_process *process)
{
	int tmp;

	tmp = get_reg(process, process->arg1 - 1) +
	get_reg(process, process->arg2 - 1);
	process->registr[process->arg3 - 1] = tmp;
	if (cor->visu == 0 && cor->dump == 0 && cor->s == 0 &&
		(cor->mon == cor->cycles || cor->log == 1))
		ft_printf("P% 5d | add r%d r%d r%d\n", process->count_num,
	process->arg1, process->arg2, process->arg3);
}

void		comm_add(t_cor *cor, t_process *process)
{
	int sk;

	if (process->delay < 0)
		process->delay = 9;
	else if (process->delay > 0)
		process->delay--;
	if (process->delay == 0)
	{
		process->label = 4;
		sk = arg_read(cor, process);
		if (process->codage == 1 && process->arg1 > 0 && process->arg2 > 0 &&
			process->arg3 > 0 &&
			process->arg1 < 17 && process->arg2 < 17 && process->arg3 < 17)
		{
			reg_reg_reg(cor, process);
			if (process->registr[process->arg3 - 1] == 0)
				process->carry = 1;
			else
				process->carry = 0;
		}
		set_proc_pos(cor, process, sk);
		process->delay = -1;
		process->codage = 1;
		process->command = -1;
	}
}
