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

void			error_msg(char *str)
{
	ft_putstr_fd("\033[01;31m", 2);
	ft_putstr_fd("EROR: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("\033[0m", 2);
	while(1);
}

void			struct_delete(t_filler	**ls)
{
	free(*ls);
	*ls = NULL;
}

// void			renew_array

void			read_header(t_filler *ls)
{
	char		*line;

	if(get_next_line(0, &line) && ft_strnequ(line, "$$$ exec p", 10))
	{
		if (line[10] == '2')
			ls->c = 'X';
		else
			ls->c = 'O';
		ft_strdel(&line);
	}
	else
		error_msg("while reading first line!");
	debug_msg_nonl("player_letter="); debug_msg(&(ls->c));
	if(get_next_line(0, &line) && ft_strnequ(line, "Plateau ", 8))
	{
		line = ft_strsub_d(&line, ft_strchr(line, ' ') - line + 1, ft_strlen(line));
		ls->map_h = ft_atoi(line);
		line = ft_strsub_d(&line, ft_strchr(line, ' ') - line, ft_strlen(line));
		ls->map_w = ft_atoi(line);
		ft_strdel(&line);
	}
	else
		error_msg("while reading 2nd line!");
	debug_msg_nonl("map_width="); debug_msg(ft_itoa_u(ls->map_w));
	debug_msg_nonl("map_height="); debug_msg(ft_itoa_u(ls->map_h));
}

void			read_piece(t_filler *ls)
{
	char		*line;

	if(get_next_line(0, &line) && ft_strnequ(line, "Piece ", 6))
	{
		line = ft_strsub_d(&line, ft_strchr(line, ' ') - line + 1, ft_strlen(line));
		ls->fig_h = ft_atoi(line);
		line = ft_strsub_d(&line, ft_strchr(line, ' ') - line, ft_strlen(line));
		ls->fig_w = ft_atoi(line);
		ft_strdel(&line);
	}
	else
		error_msg("while reading piece info line!");
	debug_msg_nonl("fig_width="); debug_msg(ft_itoa_u(ls->fig_w));
	debug_msg_nonl("fig_height="); debug_msg(ft_itoa_u(ls->fig_h));
	renew_array(ls);
}

int				main(void)
{
	char		*line;
	t_filler	*ls;
	size_t		i;

	i = 0;
	ls = (t_filler *)ft_memalloc(sizeof(t_filler));
	read_header(ls);
	get_next_line(0, &line);

	while (i < ls->map_h && get_next_line(0, &line))
	{
		debug_msg(line);
		ft_strdel(&line);
		i++;
	}
	read_piece(ls);
	struct_delete(&ls);
	error_msg("exiting");
	return (0);
}
