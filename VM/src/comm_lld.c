/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comm_lld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vibondar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 20:41:39 by vibondar          #+#    #+#             */
/*   Updated: 2018/09/20 20:41:40 by vibondar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

inline static int			arg_read(t_cor *cor, t_process *process)
{
	int	s;

	s = 2;
	if (process->arg1 == 1)
		process->codage = 0;
	if (process->arg2 != 1)
		process->codage = 0;
	process->arg_type[0] = process->arg1;
	process->arg_type[1] = process->arg2;
	process->arg_type[2] = process->arg3;
	s = arg_handler(cor, process, &process->arg1, s);
	s = arg_handler(cor, process, &process->arg2, s);
	return (s);
}

inline static void			lld_a_arg(t_cor *cor, t_process *process)
{
	if (process->codage == 1 && process->arg2 > 0 && process->arg2 < 17)
	{
		process->registr[process->arg2 - 1] = process->arg1;
		if (cor->visu == 0 && cor->dump == 0 && cor->s == 0 &&
			(cor->mon == cor->cycles || cor->log == 1))
		{
			ft_printf("P% 5d | lld %d r%d\n",
				process->count_num,
				get_reg(process, process->arg2 - 1), process->arg2);
		}
		if (process->registr[process->arg2 - 1] == 0)
			process->carry = 1;
		else
			process->carry = 0;
	}
}

void						comm_lld(t_cor *cor, t_process *process)
{
	int	sk;

	if (process->delay < 0)
		process->delay = 9;
	else if (process->delay > 0)
		process->delay--;
	if (process->delay == 0)
	{
		process->label = 4;
		codage_identify(process, get_char(cor, process->pc + 1));
		process->codage = 1;
		sk = arg_read(cor, process);
		lld_a_arg(cor, process);
		set_proc_pos(cor, process, sk);
		process->delay = -1;
		process->codage = 1;
		process->command = -1;
	}
}
