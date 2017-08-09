#ifndef FT_FILLER_H
# define FT_FILLER_H

# include "libft/libft.h"
# define LINE (ls->line)
# define SHIFT 4
# define MY -1
# define ENEMY -2

typedef struct	s_filler
{
	ssize_t	map_w;
	ssize_t	map_h;
	ssize_t	fig_w;
	ssize_t	fig_h;
	ssize_t	put_x;
	ssize_t	put_y;
	ssize_t put_dist;
	char	**fig;
	char	**map;
	char	c;
	char	e;
	char	*line;
	int		ok;
	int		is_overlap;
	int		reverse;
	int		**matr;
}				t_filler;

void			renew_fig_array(t_filler *ls);
void			read_piece(t_filler *ls);
void			calculate_distance(t_filler *ls, int e_x, int e_y);
void			make_distance_matrix(t_filler *ls);
void			distance_matrix_reset(t_filler *ls);
void			first_read_map(t_filler *ls);
void			read_header(t_filler *ls);
void			read_map(t_filler *ls);
int				try_to_put_piece(t_filler *ls, ssize_t y, ssize_t x);
void			compare_distance(t_filler *ls, ssize_t new_y, ssize_t new_x);
int				find_place_depending_on_min(t_filler *ls);
void			do_answer(t_filler *ls);

#endif
