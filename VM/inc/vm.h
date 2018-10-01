/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vibondar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 20:47:39 by vibondar          #+#    #+#             */
/*   Updated: 2018/09/20 20:47:41 by vibondar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE
# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3
# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)
# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','
# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"
# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"
# define COMMENT_CHAR_2			';'
# define REG_NUM				16
# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10
# define T_REG					1
# define T_DIR					2
# define T_IND					3
# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3
# define ABS(x) (((x)<0) ? -(x) : (x))
# include <curses.h>
# include <fcntl.h>
# include <stddef.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "libft.h"
# include "ft_printf.h"

struct s_process;
struct s_cor;
typedef struct			s_player
{
	int					all_cur;
	int					live_curr;
	int					last_live;
	int					live_summ;
	char				*file_path;
	unsigned char		prog_name[PROG_NAME_LENGTH + 1];
	unsigned char		comment[COMMENT_LENGTH + 1];
	unsigned char		*code;
	int					num;
	unsigned int		magic;
	unsigned int		prog_size;
}						t_player;

typedef struct			s_process
{
	int					count_num;
	int					live;
	unsigned int		registr[16];
	int					pc;
	int					carry;
	int					delay;
	int					arg1;
	int					arg2;
	int					arg3;
	int					arg_type[3];
	int					label;
	int					codage;
	int					command;
	int					ind_loc;
	t_player			*player;
	struct s_process	*next;
}						t_process;

typedef struct			s_map
{
	unsigned char		comm;
	int					type;
	int					car_player;
	int					player;
	int					life_time;
	int					life_scream;
}						t_map;

typedef struct			s_vizu
{
	WINDOW				*win1;
	WINDOW				*win2;
	int					end_of_prs;
	t_map				*map;
	int					speed;
	char				key;
	int					brakedown[4];
	int					last_brakedown[4];
}						t_vizu;

typedef struct			s_cor
{
	unsigned char		arena[MEM_SIZE + 1];
	int					alive_cur;
	int					proc_num;
	int					cycles;
	int					code_summ;
	int					start;
	int					visu;
	int					dump;
	int					mon;
	int					pause;
	int					stealth;
	int					a;
	int					s;
	int					log;
	int					start_from;
	int					curr_pl;
	int					p_num;
	int					flag_p_num;
	int					def_num;
	int					live_check;
	int					curr_cycle_t_d;
	int					curr_chechs;
	WINDOW				*win1;
	WINDOW				*win2;
	t_process			*process;
	t_player			player[4];
	t_player			*winner;
	void				(*instruct[17]) (struct s_cor *cor, t_process *process);
	t_vizu				*vizu;
}						t_cor;

char					get_char(t_cor *cor, int loc);
short					get_short(t_cor *cor, int loc);
void					wasted_live1(t_cor *cor);
void					end_game(t_cor *cor);
void					max_ch(t_cor *cor);
void					max_live(t_cor *cor);
void					del_first(t_cor *cor);
t_process				*player_b(t_cor *cor, t_player *player, int k);
int						manage_flags(t_cor *cor, char **argv, int i);
int						val_int(t_cor *cor, char *flag, char *value);
int						get_int(t_cor *cor, int loc);
int						t_dir(t_cor *cor, t_process *process,
	int *arg, int loc);
int						t_reg(t_cor *cor, int *arg, int loc);
int						t_ind(t_cor *cor, int *arg, int loc);
int						get_reg(t_process *process, unsigned char reg);
int						arg_handler(t_cor *cor,
	t_process *process, int *arg, int s);
int						simple_flag(int i, int *flag);
int						flag_force(t_cor *cor, char **argv, int i);
void					manage_files(t_cor *cor, char *argv);
void					validate_players(t_cor *cor);
void					bot_comment(t_cor *cor, int fd, int i);
void					bot_code(t_cor *cor, int fd, int i);
void					print_map(t_cor *cor);
void					ft_error(t_cor *cor, char *error);
void					flag_output(t_cor *cor);
void					process_activity(t_cor *cor);
void					set_proc_pos(t_cor *cor, t_process *process, int shift);
void					to_map(t_cor *cor);
void					usadge(char *name);
void					init_comand_function(t_cor *cor);
void					load_from_reg(t_cor *cor,
	t_process *process, int loc, int r_num);
void					codage_identify(t_process *process, unsigned char args);
void					comm_live(t_cor *cor, t_process *process);
void					comm_ld(t_cor *cor, t_process *process);
void					comm_and_or_xor(t_cor *cor, t_process *process);
void					comm_zjmp(t_cor *cor, t_process *process);
void					comm_ldi(t_cor *cor, t_process *process);
void					comm_sti(t_cor *cor, t_process *process);
void					comm_fork(t_cor *cor, t_process *process);
void					comm_lld(t_cor *cor, t_process *process);
void					comm_lldi(t_cor *cor, t_process *process);
void					comm_lfork(t_cor *cor, t_process *process);
void					comm_aff(t_cor *cor, t_process *process);
void					comm_st(t_cor *cor, t_process *process);
void					comm_add(t_cor *cor, t_process *process);
void					comm_sub(t_cor *cor, t_process *process);
void					comm_next(t_cor *cor, t_process *process);
void					add_proc(t_cor *cor, t_process *process, int loc);
void					live_cheker(t_cor *cor);
void					game_init(t_cor *cor);
void					add_players(t_cor *cor);
void					game(t_cor *cor);
void					init_window(t_cor *cor);
void					draw_palyer_info(t_cor *cor, t_process *proc, int k);
void					draw_info(t_cor *cor);
void					init_map(t_cor *cor);
void					refresh_map(t_cor *cor);
void					refresh_vizu(t_cor *cor);
void					initital_draw(t_cor *cor);
void					v_speed_test(t_cor *cor, char t);
void					breakdown(t_cor *cor);
void					gg_wp(t_cor *cor);
void					refresher(t_cor *cor);
void					win_art_winner(t_cor *cor);
void					win_art_sword(t_cor *cor, int y);
void					break_printer(t_cor *cor, int array[4], int line);
void					refresh_map2(t_cor *cor, int i);
void					refresh_map(t_cor *cor);
#endif
