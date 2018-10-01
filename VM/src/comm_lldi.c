/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comm_lldi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vibondar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 20:41:47 by vibondar          #+#    #+#             */
/*   Updated: 2018/09/20 20:41:48 by vibondar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	arg_read(t_cor *cor, t_process *process)
{
	int s;

	s = 2;
	if (process->arg1 == 0)
		process->codage = 0;
	if (process->arg2 == 3 || process->arg2 == 0)
		process->codage = 0;
	if (process->arg3 != 1)
		process->codage = 0;
	process->arg_type[0] = process->arg1;
	process->arg_type[1] = process->arg2;
	process->arg_type[2] = process->arg3;
	s = arg_handler(cor, process, &process->arg1, s);
	s = arg_handler(cor, process, &process->arg2, s);
	s = arg_handler(cor, process, &process->arg3, s);
	return (s);
}

static int	arg_val_hendler(t_process *process)
{
	if (process->arg_type[0] == 1)
	{
		if (process->arg1 <= 0 || process->arg1 > 16)
			return (0);
		process->arg1 = get_reg(process, process->arg1 - 1);
	}
	if (process->arg_type[1] == 1)
	{
		if (process->arg2 <= 0 || process->arg2 > 16)
			return (0);
		process->arg2 = get_reg(process, process->arg2 - 1);
	}
	return (1);
}

void		lldi_a_arg(t_cor *cor, t_process *process)
{
	process->registr[process->arg3 - 1] = get_int(cor,
		(((process->arg1 + process->arg2)) + process->pc));
	if (cor->visu == 0 && cor->dump == 0 && cor->s == 0 &&
		(cor->mon == cor->cycles || cor->log == 1))
	{
		ft_printf("P% 5d | lldi %d %d r%d\n       \
| -> load from %d + %d = %d (with pc %d)\n",
			process->count_num, process->arg1, process->arg2,
			process->arg3, process->arg1,
			process->arg2, process->arg1 + process->arg2,
			process->pc + (process->arg1 + process->arg2));
	}
}

void		comm_lldi(t_cor *cor, t_process *process)
{
	int sk;

	if (process->delay < 0)
		process->delay = 49;
	else if (process->delay > 0)
		process->delay--;
	if (process->delay == 0)
	{
		process->label = 2;
		codage_identify(process, get_char(cor, process->pc + 1));
		process->codage = 1;
		sk = arg_read(cor, process);
		if (process->codage == 1 && process->arg3 > 0 && process->arg3 < 17)
		{
			if (arg_val_hendler(process))
				lldi_a_arg(cor, process);
			if (process->registr[process->arg3 - 1] == 0)
				process->carry = 1;
			else
				process->carry = 0;
		}
		set_proc_pos(cor, process, sk);
		process->delay = -1;
		process->command = -1;
	}
}
