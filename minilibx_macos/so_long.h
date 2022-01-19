#ifndef SO_LONG_H
# define SO_LONG_H

#include "mlx.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_img
{
	void		*img;
	int			return_exit;
	int			x;
	int			y;
	void		*next;
	void		*prev;
	int			direction;
}				t_img;

typedef struct s_data
{
	void		*wn;
	void		*ml;
	void		*fond;
	void		*wall;
	void		*harry;
	void		*ex;
	void		*plr;
	void		*enemy;
	void		*enemy2;
	void		*enemy3;
	char		**map;
	int			tmp_str;
	int			tmp_c;
	int			movements;
	int			im_hei;
	int			im_wid;
	int			map_width;
	int			map_wid_pix;
	int			map_height;
	int			map_hei_pix;
	int			enemy_numb;
	long long	loop_count;
	t_img	*images;
}			t_data;

char	*ft_itoa(int n);
char	*ft_strjoin_free(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
void	ft_cleaning(t_data *data);
void	ft_destroy_imgs(t_data *data);
t_img	*ft_lstnew(void	*img, int n, int j);
void	ft_lstadd_back(t_img **lst, t_img *new);

#endif