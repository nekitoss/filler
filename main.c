#include "ft_filler.h"

typedef struct	s_filler
{
	size_t	map_w;
	size_t	map_h;
	size_t	fig_w;
	size_t	fig_h;
	char	**fig;
	char	**map;
	
}				t_filler;

void			struct_delete(t_filler	**ls)
{
	free(*ls);
	*ls = NULL;
}

int				main(void)
{
	char		*line;
	t_filler	*ls;
	size_t		i;

	i = 0;
	ls = (t_filler *)ft_memalloc(sizeof(t_filler));
	while (i < 28 && get_next_line(0, &line))
	{
		ft_putstr_fd("MY_TXT#\t|", 2);
		ft_putendl_fd("line", 2);
		ft_strdel(&line);
		i++;
	}
	struct_delete(&ls);
	return (0);
}
