#include "ft_filler.h"

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

void			compare_distance(t_filler *ls, ssize_t new_y, ssize_t new_x)
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
