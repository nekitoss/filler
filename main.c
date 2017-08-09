#include "ft_filler.h"

int			check_read(t_filler *ls, char *str, ssize_t len)
{
	int res;

	res = get_next_line(0, &LINE);
	if (res > 0 && ft_strnequ(LINE, str, len))
	{
		//ft_strdel(&LINE);
		return (1);
	}
	ls->ok = 0;
	return (0);
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
		//ft_strdel(&LINE);
	}
	renew_fig_array(ls);
}

void			calculate_distance(t_filler *ls, int e_x, int e_y)
{
	int		x;
	int		y;
	int		d;

	y = 0;
	while (y < ls->map_h)
	{
		x = 0;
		while (x < ls->map_w)
		{
			if ((ls->map)[y][x] == ls->c)
				(ls->matr)[y][x] = MY;
			else if ((ls->map)[y][x] == ls->e)
				(ls->matr)[y][x] = ENEMY;
			else
			{
				d = ABS((x - e_x)) + ABS((y - e_y));
				if (d < (ls->matr)[y][x])
					(ls->matr)[y][x] = d;
			}
			x++;
		}
		y++;
	}
}

void			make_distance_matrix(t_filler *ls)
{
	char		*pos;
	ssize_t		y;

	y = 0;
	while (y < ls->map_h)
	{
		pos = ft_strchr((ls->map)[y], ls->e);
		while (pos)
		{
			calculate_distance(ls, pos - (ls->map)[y], y);
			pos = ft_strchr(++pos, ls->e);
		}
		y++;
	}
}

void			distance_matrix_reset(t_filler *ls)
{
	ssize_t		y;
	ssize_t		x;

	ls->put_y = -1;
	ls->put_x = -1;
	ls->put_dist = SSIZE_MAX;
	y = 0;
	while (y < ls->map_h)
	{
		x = 0;
		while (x < ls->map_w)
		{
			(ls->matr)[y][x] = INT_MAX;
			x++;
		}
		y++;
	}
}

void			first_read_map(t_filler *ls)
{
	ssize_t		i;

	i = 0;
	check_read(ls, "    0", 5);
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
		//ft_strdel(&LINE);
	}
	if (get_next_line(0, &LINE) > 0 && ft_strnequ(LINE, "Plateau ", 8))
	{
		LINE = ft_strsub_d(&LINE, ft_strchr(LINE, ' ')
				- LINE + 1, ft_strlen(LINE));
		ls->map_h = ft_atoi(LINE);
		LINE = ft_strsub_d(&LINE, ft_strchr(LINE, ' ') - LINE, ft_strlen(LINE));
		ls->map_w = ft_atoi(LINE);
		//ft_strdel(&LINE);
	}
	first_read_map(ls);
}

void			read_map(t_filler *ls)
{
	ssize_t		i;
	char		*tmp;

	i = 0;
	check_read(ls, "Plateau ", 8);
	check_read(ls, "    0", 5);
	while (ls->ok && i < ls->map_h && get_next_line(0, &LINE) > 0)
	{
		tmp = ls->map[i] - SHIFT;
		//ft_strdel(&tmp);
		(ls->map)[i] = LINE + SHIFT;
		i++;
	}
	read_piece(ls);
	distance_matrix_reset(ls);
	make_distance_matrix(ls);
}

int				try_to_put_piece(t_filler *ls, ssize_t y, ssize_t x)
{
	ssize_t f_x;
	ssize_t f_y;

	ls->is_overlap = 0;
	f_x = 0;
	while (f_x < ls->fig_w)
	{
		f_y = 0;
		while (f_y < ls->fig_h)
		{
			if ((ls->fig)[f_y][f_x] == '*')
			{
				if (!(ls->is_overlap) && (ls->map)[y + f_y][x + f_x] == ls->c)
				{
					ls->is_overlap = 1;
				}
				else if (!((ls->map)[y + f_y][x + f_x] == '.'))
					return (0);
			}
			f_y++;
		}
		f_x++;
	}
	return (((ls->is_overlap && f_x == ls->fig_w && f_y == ls->fig_h) ? 1 : 0));
}

void				compare_distance(t_filler *ls, ssize_t new_y, ssize_t new_x)
{
	ssize_t f_x;
	ssize_t f_y;
	ssize_t temp_dist;

	temp_dist = 0;
	f_x = 0;
	while (f_x < ls->fig_w)
	{
		f_y = 0;
		while (f_y < ls->fig_h)
		{
			if ((ls->fig)[f_y][f_x] == '*')
				temp_dist += (ls->matr)[(f_y + new_y)][(f_x + new_x)];
			f_y++;
		}
		f_x++;
	}
	if (temp_dist < ls->put_dist)
	{
		ls->put_x = new_x;
		ls->put_y = new_y;
		ls->put_dist = temp_dist;
	}
}

int				find_place_depending_on_min(t_filler *ls)
{
	ssize_t		y;
	ssize_t		x;

	y = 0;
	while (y < ls->map_h - ls->fig_h + 1)
	{
		x = 0;
		while (x < ls->map_w - ls->fig_w + 1)
		{
			if (try_to_put_piece(ls, y, x))
			{
				compare_distance(ls, y, x);
			}
			x++;
		}
		y++;
	}
	return ((ls->put_x >= 0 ? 1 : 0));
}

void			do_answer(t_filler *ls)
{
	ft_putnbr_u(ls->put_y);
	ft_putchar(' ');
	ft_putnbr_u(ls->put_x);
	ft_putchar('\n');
}

int				main(void)
{
	t_filler	*ls;

	ls = (t_filler *)ft_memalloc(sizeof(t_filler));
	ls->put_dist = SSIZE_MAX;
	read_header(ls);
	find_place_depending_on_min(ls);
	do_answer(ls);
	while (1)
	{
		read_map(ls);
		find_place_depending_on_min(ls);
		do_answer(ls);
	}
	return (0);
}
