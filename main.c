#define DEBUG

#include "ft_filler.h"
#define LINE (ls->line)
#define SHIFT 4

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
	char	*line;
	int		header_ok;
	int		ok;
}				t_filler;

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

void			error_msg(char *str, t_filler *ls)
{
	ft_putstr_fd("\033[01;31m", 2);
	ft_putstr_fd("EROR: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("\033[0m", 2);
	ls->ok = 0;
}

void			struct_delete(t_filler	**ls)
{
	free(*ls);
	*ls = NULL;
}

int			check_read(t_filler *ls, char *str, size_t len)
{
	int res;

	res = get_next_line(0, &LINE);
	if (res > 0 && ft_strnequ(LINE, str, len))
	{
		ft_strdel(&LINE);
		return (1);
	}
	ls->ok = 0;
	return (0);
}

void			renew_fig_array(t_filler *ls)
{debug_msg("renew_fig_array");
	size_t i;

	i = 0;
	if (ls->ok)
	{
		ft_arrdel((void ***)&(ls->fig));
		ls->fig = (char **)ft_newarr(ls->fig_h);
		while (i < ls->fig_h && get_next_line(0, &LINE) > 0)
		{
			(ls->fig)[i] = LINE;
			debug_msg((ls->fig)[i]);
			i++;
		}
		if (i != ls->fig_h)
			error_msg("while reading piece!", ls);
	}
}

void			read_piece(t_filler *ls)
{debug_msg("read_piece");
	if(ls->ok && get_next_line(0, &LINE) >0 && ft_strnequ(LINE, "Piece ", 6))
	{
		LINE = ft_strsub_d(&LINE, ft_strchr(LINE, ' ') - LINE + 1, ft_strlen(LINE));
		ls->fig_h = ft_atoi(LINE);
		LINE = ft_strsub_d(&LINE, ft_strchr(LINE, ' ') - LINE, ft_strlen(LINE));
		ls->fig_w = ft_atoi(LINE);
		ft_strdel(&LINE);
	}
	else
		error_msg("while reading piece info line!", ls);
	debug_msg_nonl("fig_width="); debug_msg(ft_itoa_u(ls->fig_w));
	debug_msg_nonl("fig_height="); debug_msg(ft_itoa_u(ls->fig_h));
	renew_fig_array(ls);
}

void			first_read_map(t_filler *ls)
{debug_msg("first_read_map");
	size_t		i;

	i = 0;
	check_read(ls, "    0", 5);
	ls->map = (char **)ft_newarr(ls->map_h);
	while (i < ls->map_h && get_next_line(0, &LINE))
	{
		(ls->map)[i] = LINE + SHIFT;
		// debug_msg(LINE);
		debug_msg((ls->map)[i]);
		i++;
	}
	read_piece(ls);
}

void			read_header(t_filler *ls)
{debug_msg("read_header");
	ls->ok = 1;
	if(get_next_line(0, &LINE) > 0 && ft_strnequ(LINE, "$$$ exec p", 10))
	{
		if (LINE[10] == '2')
			ls->c = 'X';
		else
			ls->c = 'O';
		ft_strdel(&LINE);
	}
	else
		error_msg("while reading first line!", ls);
	debug_msg_nonl("player_letter="); debug_msg(&(ls->c));
	if(get_next_line(0, &LINE) > 0 && ft_strnequ(LINE, "Plateau ", 8))
	{
		LINE = ft_strsub_d(&LINE, ft_strchr(LINE, ' ') - LINE + 1, ft_strlen(LINE));
		ls->map_h = ft_atoi(LINE);
		LINE = ft_strsub_d(&LINE, ft_strchr(LINE, ' ') - LINE, ft_strlen(LINE));
		ls->map_w = ft_atoi(LINE);
		ft_strdel(&LINE);
	}
	else
		error_msg("while reading 2nd line!", ls);
	debug_msg_nonl("map_width="); debug_msg(ft_itoa_u(ls->map_w));
	debug_msg_nonl("map_height="); debug_msg(ft_itoa_u(ls->map_h));
	first_read_map(ls);
}

void			read_map(t_filler *ls)
{debug_msg("read_map");
	size_t		i;

	i = 0;
	check_read(ls, "Plateau ", 8);
	check_read(ls, "    0", 5);
	while (ls->ok && i < ls->map_h && get_next_line(0, &LINE) > 0)
	{
		free(ls->map[i] - SHIFT);
		(ls->map)[i] = LINE + SHIFT;
		// debug_msg(LINE);
		debug_msg((ls->map)[i]);
		i++;
	}
	read_piece(ls);
}

int				main(void)
{
	t_filler	*ls;

	ls = (t_filler *)ft_memalloc(sizeof(t_filler));
	read_header(ls);
	debug_msg("first_print answer");
		write(1, "8 2\n", 4);
		sleep(1);
	while(ls->ok)
	{
		read_map(ls);
		debug_msg("print answer");
		write(1, "8 2\n", 4);
		sleep(1);
	}
	struct_delete(&ls);
	error_msg("##EXITING##", ls);
	return (0);
}
