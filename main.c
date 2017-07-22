#define DEBUG

#include "ft_filler.h"

typedef struct	s_filler
{
	size_t	map_w;
	size_t	map_h;
	size_t	fig_w;
	size_t	fig_h;
	size_t	put_x;
	size_t	put_y;
	char	**fig;
	char	**map;
	char	c;
}				t_filler;

void			struct_delete(t_filler	**ls)
{
	free(*ls);
	*ls = NULL;
}

void	debug_msg(char *str)
{
#ifdef DEBUG
	ft_putstr_fd("\033[01;31m", 2);
	ft_putendl_fd(str, 2);
	ft_putstr_fd("\033[0m", 2);
#else
	str = NULL;
#endif
}

void	debug_msg_nonl(char *str)
{
#ifdef DEBUG
	ft_putstr_fd("\033[01;31m", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\033[0m", 2);
#else
	str = NULL;
#endif
}

int				main(void)
{
	char		*line;
	t_filler	*ls;
	size_t		i;

	i = 0;
	ls = (t_filler *)ft_memalloc(sizeof(t_filler));
	if(get_next_line(0, &line))
	{
		// debug_msg((line + 10));
		if (line[10] == '2')
			ls->c = 'X';
		else
			ls->c = 'O';
		ft_strdel(&line);
	}
	else
		debug_msg("eror in first gnl read");
	debug_msg_nonl("player_letter="); debug_msg(&(ls->c));
	if(get_next_line(0, &line))
	{
		line = ft_strchr(line, ' ') + 1;
		ls->map_h = ft_atoi(line);
		line = ft_strchr(line, ' ') + 1;
		ls->map_w = ft_atoi(line);
		// ft_strdel(&line);
	}
	else
		debug_msg("eror in 2nd gnl read");
	debug_msg_nonl("map_width="); debug_msg(ft_itoa_u(ls->map_w));
	debug_msg_nonl("map_height="); debug_msg(ft_itoa_u(ls->map_h));
	while (i < 28 && get_next_line(0, &line))
	{
		debug_msg(line);
		ft_strdel(&line);
		i++;
	}
	struct_delete(&ls);
	return (0);
}
