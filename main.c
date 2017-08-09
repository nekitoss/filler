// #define DEBUG
// #define ERRRORING

#include "ft_filler.h"
#define LINE (ls->line)
#define SHIFT 4
#define MY -1
#define ENEMY -2
#define MIN_X min[2]
#define MIN_Y min[1]

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
#ifdef ERRRORING
	ft_putstr_fd("\033[01;31m", 2);
	ft_putstr_fd("ERROR: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("\033[0m", 2);
	ls->ok = 0;
#else
	str = NULL;
	ls->ok = 1;
#endif
}

void			struct_delete(t_filler	**ls)
{
	free(*ls);
	*ls = NULL;
}

int			check_read(t_filler *ls, char *str, ssize_t len)
{
	int res;

	res = get_next_line(0, &LINE);
	if (res > 0 && ft_strnequ(LINE, str, len))
	{
		//ft_strdel(&LINE);
		return (1);
	}
	else
		error_msg(LINE, ls);
	ls->ok = 0;
	return (0);
}

void			renew_fig_array(t_filler *ls)
{debug_msg("renew_fig_array");
	ssize_t i;

	i = 0;
	if (ls->ok)
	{
		ft_arrdel((void ***)&(ls->fig));
		ls->fig = (char **)ft_newarr(ls->fig_h);
		while (i < ls->fig_h && get_next_line(0, &LINE) > 0)
		{debug_msg_nonl("RENEW=");debug_msg(LINE);
			(ls->fig)[i] = LINE;
			// debug_msg((ls->fig)[i]);
			i++;
		}
		if (i != ls->fig_h)
			error_msg("while reading piece!", ls);
	}
}

void			read_piece(t_filler *ls)
{debug_msg("read_piece");
	ls->fig_h = 0;
	ls->fig_w = 0;
	int res = get_next_line(0, &LINE);
// debug_msg_nonl("READ_PIECE=");debug_msg(LINE);
	if(ls->ok &&  res> 0 && ft_strnequ(LINE, "Piece ", 6))
	{
		// debug_msg(LINE);
		LINE = ft_strsub_d(&LINE, ft_strchr(LINE, ' ') - LINE + 1, ft_strlen(LINE));
		ls->fig_h = ft_atoi(LINE);
		LINE = ft_strsub_d(&LINE, ft_strchr(LINE, ' ') - LINE, ft_strlen(LINE));
		ls->fig_w = ft_atoi(LINE);
		//ft_strdel(&LINE);
	}
	else
	{
		error_msg(LINE, ls);
		error_msg("while reading piece info line!", ls);
	}
	debug_msg_nonl("fig_width="); debug_msg(ft_itoa_u(ls->fig_w));
	debug_msg_nonl("fig_height="); debug_msg(ft_itoa_u(ls->fig_h));
	renew_fig_array(ls);
}

void prnt_matrix(t_filler *ls)
{debug_msg("prnt_matrix");
	int		x;
	int		y;

	y = 0;
	while (y < ls->map_h)
	{
		x = 0;
		while (x < ls->map_w)
		{
			debug_msg_nonl(ft_itoa((ls->matr)[y][x]));
			debug_msg_nonl(" ");
			x++;
		}
		debug_msg("");
		y++;
	}
}

void			calculate_distance(t_filler *ls, int e_x, int e_y)
{debug_msg("calculate_distance");
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
{debug_msg("make_distance_matrix");
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
	prnt_matrix(ls);
}

void			distance_matrix_reset(t_filler *ls)
{debug_msg("distance_matrix_reset");
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
{debug_msg("first_read_map");
	ssize_t		i;

	i = 0;
	check_read(ls, "    0", 5);
	ls->map = (char **)ft_newarr(ls->map_h);
	ls->matr = (int **)ft_newarr(ls->map_h);
	while (i < ls->map_h && get_next_line(0, &LINE))
	{
		(ls->map)[i] = LINE + SHIFT;
		(ls->matr)[i] = malloc(ls->map_w * sizeof(int));
		// debug_msg(LINE);
		debug_msg((ls->map)[i]);
		i++;
	}
	read_piece(ls);
	distance_matrix_reset(ls);
	make_distance_matrix(ls);
}

void			read_header(t_filler *ls)
{debug_msg("read_header");
	ls->ok = 1;
	if(get_next_line(0, &LINE) > 0 && ft_strnequ(LINE, "$$$ exec p", 10))
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
	else
		error_msg("while reading first line!", ls);
	debug_msg_nonl("player_letter="); debug_msg(&(ls->c));
	if(get_next_line(0, &LINE) > 0 && ft_strnequ(LINE, "Plateau ", 8))
	{
		LINE = ft_strsub_d(&LINE, ft_strchr(LINE, ' ') - LINE + 1, ft_strlen(LINE));
		ls->map_h = ft_atoi(LINE);
		LINE = ft_strsub_d(&LINE, ft_strchr(LINE, ' ') - LINE, ft_strlen(LINE));
		ls->map_w = ft_atoi(LINE);
		//ft_strdel(&LINE);
	}
	else
		error_msg("while reading 2nd line!", ls);
	debug_msg_nonl("map_width="); debug_msg(ft_itoa_u(ls->map_w));
	debug_msg_nonl("map_height="); debug_msg(ft_itoa_u(ls->map_h));
	first_read_map(ls);
}

void			read_map(t_filler *ls)
{debug_msg("read_map");
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
		// debug_msg(LINE);
		// debug_msg((ls->map)[i]);
		i++;
		// sleep(1);
	}
	// sleep(1);
	read_piece(ls);
	distance_matrix_reset(ls);
	make_distance_matrix(ls);
}

int				try_to_put_piece(t_filler *ls, ssize_t y, ssize_t x)
{
	ssize_t f_x;
	ssize_t f_y;
// debug_msg("START");
	ls->is_overlap = 0;
	f_x = 0;
	while (f_x < ls->fig_w)
	{
		f_y = 0;
		while (f_y < ls->fig_h)
		{
		// debug_msg_nonl("try at ");debug_msg_nonl(ft_itoa_u(x+f_x)); debug_msg_nonl(" : "); debug_msg_nonl(ft_itoa_u(y+f_y)); debug_msg_nonl("; fig at ");debug_msg_nonl(ft_itoa_u(f_x)); debug_msg_nonl(" : "); debug_msg(ft_itoa_u(f_y));
			if ((ls->fig)[f_y][f_x] == '*')
			{//debug_msg("is *; ");
				if (!(ls->is_overlap) && (ls->map)[y + f_y][x + f_x] == ls->c)
				{//debug_msg_nonl("try_to_put_piece "); debug_msg_nonl(ft_itoa_u(x)); debug_msg_nonl(" : "); debug_msg(ft_itoa_u(y));
					//debug_msg_nonl("overlap at ");debug_msg_nonl(ft_itoa_u(x+f_x)); debug_msg_nonl(" : "); debug_msg(ft_itoa_u(y+f_y));
					ls->is_overlap = 1;
				}
				else if (!((ls->map)[y + f_y][x + f_x] == '.'))
					return (0);
			}
			f_y++;
		}
		f_x++;
	}
	//debug_msg_nonl("endtry ");debug_msg_nonl(ft_itoa_u(f_x)); debug_msg_nonl(" : "); debug_msg(ft_itoa_u(f_y));
	return (((ls->is_overlap && f_x == ls->fig_w && f_y == ls->fig_h) ? 1 : 0));
	// return (1);
}

void				compare_and_set_new_distance(t_filler *ls, ssize_t new_y, ssize_t new_x)
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
{debug_msg("find_place_depending_on_min");
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
				compare_and_set_new_distance(ls, y, x);
			}
			x++;
		}
		y++;
	}
	debug_msg_nonl("FOUND_BY_MIN "); debug_msg_nonl(ft_itoa_u(ls->put_x)); debug_msg_nonl(" : "); debug_msg(ft_itoa_u(ls->put_y));
	return ((ls->put_x >= 0 ? 1 : 0));
}

int				find_min_in_matrix(t_filler *ls)
{
	ssize_t		y;
	ssize_t		x;
	int			min[3];

	y = 0;
	min[0] = INT_MAX;
	while (y < ls->map_h - ls->fig_h + 1)
	{
		x = 0;
		while (x < ls->map_w - ls->fig_w + 1)
		{
			if ((ls->matr)[y][x] < min[0] && (ls->matr)[y][x] > 0)
			{
				min[0] = (ls->matr)[y][x];
				MIN_Y = y;
				MIN_X = x;
			}
			x++;
		}
		y++;
	}
	//check here x&y
	if (min[0] == INT_MAX)
		return (0);
	(ls->matr)[MIN_Y][MIN_X] = INT_MAX;
	if (try_to_put_piece(ls, MIN_Y, MIN_X))
	{
		ls->put_y = MIN_Y;
		ls->put_x = MIN_X;
		debug_msg_nonl("FOUND_BY_MIN "); debug_msg_nonl(ft_itoa_u(ls->put_x)); debug_msg_nonl(" : "); debug_msg(ft_itoa_u(ls->put_y));
		return (1);
	}
	else
	{

		return (find_min_in_matrix(ls));
	}
}

// void			find_place_depending_on_distance(t_filler *ls, ssize_t x, ssize_t y)
// {debug_msg("find_place_depending_on_distance");
// 	if (ls->map_w >= ls->fig_w && ls->map_h >= ls->fig_h)
// 	{
// 		while (y >= 0)
// 		{
// 			x = ls->map_w - ls->fig_w;
// 			while (x >= 0)
// 			{
// 				if (try_to_put_piece(ls, x, y))
// 				{
// 					ls->put_x = x;
// 					ls->put_y = y;
// 					debug_msg_nonl("FOUND "); debug_msg_nonl(ft_itoa_u(x)); debug_msg_nonl(" : "); debug_msg(ft_itoa_u(y));
// 					return ;
// 				}
// 				x--;
// 			}
// 			y--;
// 		}
// 		error_msg("there is no way to put that shit on map!", ls);
// 	}
// 	else
// 		error_msg("figure is smaller than map!", ls);
// }

void			find_place(t_filler *ls, ssize_t x, ssize_t y)
{debug_msg("find_place");
	if (ls->map_w >= ls->fig_w && ls->map_h >= ls->fig_h)
	{
		while (y >= 0)
		{
			x = ls->map_w - ls->fig_w;
			while (x >= 0)
			{
				if (try_to_put_piece(ls, x, y))
				{
					ls->put_x = x;
					ls->put_y = y;
					debug_msg_nonl("FOUND "); debug_msg_nonl(ft_itoa_u(x)); debug_msg_nonl(" : "); debug_msg(ft_itoa_u(y));
					return ;
				}
				x--;
			}
			y--;
		}
		error_msg("there is no way to put that shit on map!", ls);
	}
	else
		error_msg("figure is smaller than map!", ls);
}

void			find_place_reverse(t_filler *ls, ssize_t x, ssize_t y)
{debug_msg("find_place_reverse");
	ssize_t x_w;
	ssize_t y_h;

	if (ls->map_w >= ls->fig_w && ls->map_h >= ls->fig_h)
	{
		x_w = ls->map_w - ls->fig_w;
		y_h = ls->map_h - ls->fig_h;
		while (y < y_h)
		{
			x = 0;
			while (x < x_w)
			{
				if (try_to_put_piece(ls, x, y))
				{
					ls->put_x = x;
					ls->put_y = y;
					debug_msg_nonl("FOUND "); debug_msg_nonl(ft_itoa_u(x)); debug_msg_nonl(" : "); debug_msg(ft_itoa_u(y));
					return ;
				}
				x++;
			}
			y++;
		}
		error_msg("there is no way to put that shit on map!", ls);
	}
	else
		error_msg("figure is smaller than map!", ls);
}

void			do_answer(t_filler *ls)
{debug_msg("do_answer");
	ft_putnbr_u(ls->put_y);
	ft_putchar(' ');
	ft_putnbr_u(ls->put_x);
	ft_putchar('\n');
}

void			check_direction(t_filler *ls)
{debug_msg("check_direction");
	ssize_t		i;
	ssize_t		pos[2][2];
	char		*fnd_o;
	char		*fnd_x;

	i = 0;
	while (i < ls->map_h)
	{
		fnd_o = ft_strchr((ls->map)[i], 'O');
		fnd_x = ft_strchr((ls->map)[i], 'X');
		if (fnd_o)
		{
			pos[0][0] = fnd_o - (ls->map)[i];
			pos[0][1] = i;
		}
		if (fnd_x)
		{
			pos[1][0] = fnd_x - (ls->map)[i];
			pos[1][1] = i;
		}
		i++;
	}
	if (ls->c == 'O')
		ls->reverse = ((pos[0][1] > pos[1][1]) ? 1 : 0);
	else
		ls->reverse = ((pos[0][1] > pos[1][1]) ? 0 : 1);
	debug_msg_nonl("reverse ="); debug_msg(ft_itoa_u(ls->reverse));
}

int				main(void)
{
	t_filler	*ls;

	ls = (t_filler *)ft_memalloc(sizeof(t_filler));
	ls->put_dist = SSIZE_MAX;
	read_header(ls);
	check_direction(ls);
	// if (ls->reverse)
	// 		find_place_reverse(ls, 0, 0);
	// else
	// 	find_place(ls, ls->map_w - ls->fig_w, ls->map_h - ls->fig_h);
	find_place_depending_on_min(ls);
	do_answer(ls);
	// 	sleep(1);
	while(1)
	{
		read_map(ls);
		// if (ls->reverse)
		// 	find_place_reverse(ls, 0, 0);
		// else
		// 	find_place(ls, ls->map_w - ls->fig_w, ls->map_h - ls->fig_h);
		find_place_depending_on_min(ls);
		do_answer(ls);
		// debug_msg_nonl("PUT_AT "); debug_msg_nonl(ft_itoa_u(ls->put_x)); debug_msg_nonl(" : "); debug_msg(ft_itoa_u(ls->put_y));
		// printf("%zu %zu\n", ls->put_y, ls->put_x);
		// do_answer(ls);
	}
	// struct_delete(&ls);
	error_msg("##EXITING##", ls);
	return (0);
}
