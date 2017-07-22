#define DEBUG

#include "ft_filler.h"
#define LINE (ls->line)

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

void			renew_fig_array(t_filler *ls)
{
	size_t i;

	i = 0;
	ft_arrdel((void ***)&(ls->fig));
	while (i < ls->map_h && get_next_line(0, &LINE))
	{

	}
}

void			read_header(t_filler *ls)
{
	if(get_next_line(0, &LINE) && ft_strnequ(LINE, "$$$ exec p", 10))
	{
		if (LINE[10] == '2')
			ls->c = 'X';
		else
			ls->c = 'O';
		ft_strdel(&LINE);
	}
	else
		error_msg("while reading first line!");
	debug_msg_nonl("player_letter="); debug_msg(&(ls->c));
	if(get_next_line(0, &LINE) && ft_strnequ(LINE, "Plateau ", 8))
	{
		LINE = ft_strsub_d(&LINE, ft_strchr(LINE, ' ') - LINE + 1, ft_strlen(LINE));
		ls->map_h = ft_atoi(LINE);
		LINE = ft_strsub_d(&LINE, ft_strchr(LINE, ' ') - LINE, ft_strlen(LINE));
		ls->map_w = ft_atoi(LINE);
		ft_strdel(&LINE);
	}
	else
		error_msg("while reading 2nd line!");
	debug_msg_nonl("map_width="); debug_msg(ft_itoa_u(ls->map_w));
	debug_msg_nonl("map_height="); debug_msg(ft_itoa_u(ls->map_h));
}

void			read_piece(t_filler *ls)
{
	if(get_next_line(0, &LINE) && ft_strnequ(LINE, "Piece ", 6))
	{
		LINE = ft_strsub_d(&LINE, ft_strchr(LINE, ' ') - LINE + 1, ft_strlen(LINE));
		ls->fig_h = ft_atoi(LINE);
		LINE = ft_strsub_d(&LINE, ft_strchr(LINE, ' ') - LINE, ft_strlen(LINE));
		ls->fig_w = ft_atoi(LINE);
		ft_strdel(&LINE);
	}
	else
		error_msg("while reading piece info line!");
	debug_msg_nonl("fig_width="); debug_msg(ft_itoa_u(ls->fig_w));
	debug_msg_nonl("fig_height="); debug_msg(ft_itoa_u(ls->fig_h));
	renew_fig_array(ls);
}

int				main(void)
{
	t_filler	*ls;
	size_t		i;

	i = 0;
	ls = (t_filler *)ft_memalloc(sizeof(t_filler));
	read_header(ls);
	get_next_line(0, &LINE);

	while (i < ls->map_h && get_next_line(0, &LINE))
	{
		debug_msg(LINE);
		ft_strdel(&LINE);
		i++;
	}
	read_piece(ls);
	struct_delete(&ls);
	error_msg("exiting");
	return (0);
}
