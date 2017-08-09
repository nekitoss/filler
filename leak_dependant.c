#include "ft_filler.h"

void			read_piece(t_filler *ls)
{
	ls->fig_h = 0;
	ls->fig_w = 0;
	if (ls->ok && get_next_line(0, &LINE) > 0 && ft_strnequ(LINE, "Piece ", 6))
	{
		LINE = ft_strsub_d(&LINE, ft_strchr(LINE, ' ')
				- LINE + 1, ft_strlen(LINE));
		ls->fig_h = ft_atoi(LINE);
		LINE = ft_strsub_d(&LINE, ft_strchr(LINE, ' ') - LINE, ft_strlen(LINE));
		ls->fig_w = ft_atoi(LINE);
	}
	renew_fig_array(ls);
}

void			read_header(t_filler *ls)
{
	ls->ok = 1;
	if (get_next_line(0, &LINE) > 0 && ft_strnequ(LINE, "$$$ exec p", 10))
	{
		if (LINE[10] == '2')
		{
			ls->c = 'X';
			ls->e = 'O';
		}
		else
		{
			ls->c = 'O';
			ls->e = 'X';
		}
	}
	if (get_next_line(0, &LINE) > 0 && ft_strnequ(LINE, "Plateau ", 8))
	{
		LINE = ft_strsub_d(&LINE, ft_strchr(LINE, ' ')
				- LINE + 1, ft_strlen(LINE));
		ls->map_h = ft_atoi(LINE);
		LINE = ft_strsub_d(&LINE, ft_strchr(LINE, ' ') - LINE, ft_strlen(LINE));
		ls->map_w = ft_atoi(LINE);
	}
	first_read_map(ls);
}

void			read_map(t_filler *ls)
{
	ssize_t		i;
	char		*tmp;

	i = 0;
	get_next_line(0, &LINE);
	get_next_line(0, &LINE);
	while (ls->ok && i < ls->map_h && get_next_line(0, &LINE) > 0)
	{
		tmp = ls->map[i] - SHIFT;
		(ls->map)[i] = LINE + SHIFT;
		i++;
	}
	read_piece(ls);
	distance_matrix_reset(ls);
	make_distance_matrix(ls);
}

void			first_read_map(t_filler *ls)
{
	ssize_t		i;

	i = 0;
	get_next_line(0, &LINE);
	ls->map = (char **)ft_newarr(ls->map_h);
	ls->matr = (int **)ft_newarr(ls->map_h);
	while (i < ls->map_h && get_next_line(0, &LINE))
	{
		(ls->map)[i] = LINE + SHIFT;
		(ls->matr)[i] = malloc(ls->map_w * sizeof(int));
		i++;
	}
	read_piece(ls);
	distance_matrix_reset(ls);
	make_distance_matrix(ls);
}

void			renew_fig_array(t_filler *ls)
{
	ssize_t i;

	i = 0;
	if (ls->ok)
	{
		ft_arrdel((void ***)&(ls->fig));
		ls->fig = (char **)ft_newarr(ls->fig_h);
		while (i < ls->fig_h && get_next_line(0, &LINE) > 0)
		{
			(ls->fig)[i] = LINE;
			i++;
		}
	}
}
