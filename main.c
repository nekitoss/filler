#include "ft_filler.h"

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
