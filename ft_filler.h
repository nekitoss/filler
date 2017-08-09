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

#endif
