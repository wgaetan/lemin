/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lemin.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: wgaetan <wgaetan@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/28 15:34:13 by wgaetan      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/31 09:36:41 by wgaetan     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct				s_tables
{
	int						*x_coor;
	int						*y_coor;
	short					**tunnels;
	char					**names;
}							t_tables;

typedef struct				s_paths
{
	short					*path;
	short					len;
	struct s_paths			*next;
}							t_paths;

typedef struct				s_input_buffer
{
	char					*line;
	int						line_type;
	int						pos;
	struct s_input_buffer	*prev;
	struct s_input_buffer	*next;
}							t_input_buffer;

typedef struct				s_parse_data
{
	t_input_buffer			*input_buffer;
	int						first_room_line;
	int						first_tunnel_line;
	int						line_number;
	int						line_error;
}							t_parse_data;

typedef struct				s_bit_fields
{
	unsigned int			**paths;
	short					*len;
	int						*id;
	int						size;
}							t_bit_fields;

typedef struct				s_path_set
{
	int						*paths_id;
	short					*paths_len;
	unsigned int			*to_avoid;
	int						solving_turns;
	int						size;
	int						count;
}							t_path_set;

typedef struct				s_ant
{
	short					path;
	int						turn;
	int						id;
	struct s_ant			*next;
}							t_ant;

typedef struct				s_stock
{
	t_parse_data			parse_data;
	t_tables				tables;
	t_path_set				solving_set;
	t_path_set				tmp_set;
	t_bit_fields			bit_fields;
	t_ant					*ant;
	t_paths					*paths;
	int						*send_tab;
	short					*path;
	short					*passed;
	short					mode;
	short					limit_step;
	int						ants_number;
	int						rooms_number;
	int						paths_number;
}							t_stock;

t_stock						*get_stock(void);

t_paths						*find_shortest_path(t_paths *paths);
t_paths						*get_path_by_id(int id);
t_paths						*last_in_path(t_paths *paths);
t_paths						*new_path(short *tab, short len);

unsigned int				*create_bit_field(int size);
unsigned int				*path_to_bit_field(t_paths *path);
int							available_path(t_stock *stock, t_path_set *set,
		int *d);
int							get_line_type(char *str);
int							maximum_path_number(void);

short						get_room_id_by_name(char *name);

void						add_bufer_line(t_input_buffer **head,
												t_input_buffer *line);
void						add_path(t_paths **head, t_paths *new_path);
void						add_room(t_input_buffer *buff, char *cmd);
void						add_to_path_set(t_path_set *set, int id);
void						add_tunnel(t_input_buffer *buff);
void						best_path_loop(t_stock *stock, t_path_set *set,
		int milestone);
void						check_data(void);
void						copy_bit_field(void);
void						copy_set(t_path_set *dest, t_path_set *src);
void						del_common_path(t_paths **head, t_paths *path);
void						explore(short room, short step, t_stock *stock);
void						explore_all(short room, short step, t_stock *stock);
void						explore_reduced(short room, short step,
		t_stock *stock);
void						explore_unique(short room, short step,
		t_stock *stock);
void						extract_data(void);
void						fill_input_buffer(void);
void						find_solving_set(void);
void						get_params(int argc, char **argv);
void						init_bit_fields(void);
void						init_parse_data(t_parse_data *parse_data);
void						init_path_set(t_path_set *set, int size);
void						invalid_parsing(void);
void						parse(void);
void						printbits(unsigned int to_print);
void						print_path_set(t_path_set *set);
void						remove_last_from_path_set(t_path_set *set);
void						send_ants(void);
void						set_bit(int i, unsigned int **tab);
void						simulate_solve(int ants, t_path_set *set);
void						start_end_direct();
void						solve(void);
void						unset_bit(int i, unsigned int **tab);
void						write_ants(void);

#endif
