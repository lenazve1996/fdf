/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:22:46 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/01/20 12:48:30 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

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
	t_img		*images;
}			t_data;

char	*ft_itoa(int n);
char	*ft_strjoin_free(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
void	ft_cleaning(t_data *data);
void	ft_destroy_imgs(t_data *data);
int		ft_put_image(char symb, t_data *data);
t_img	*ft_lstnew(void	*img, int n, int j);
void	ft_lstadd_back(t_img **lst, t_img *new);
void	ft_error_inmap_read(char *line, char *tmp, char *str);
int		ft_putstr_fd_ret(char *s, int fd);
int		ft_patrols(t_data *data);
int		ft_map_validation(char **map, t_data *data);
int		ft_destroy(t_data *data);
int		ft_win_and_img_creation(t_data *data);
void	ft_put_img_to_fond(t_data *data, void *character, int x, int y);
int		ft_fill_window(char **map, t_data *data);
void	ft_animation(t_data *data, int c);
t_img	*ft_locate_new_pos(t_data *data, int keycode, t_img *old_p);
char	*ft_strchr(const char *s, int c);
int		ft_parser(char	**argv, t_data *data);
void	ft_player_lose(t_img *new_p, t_data *data);
void	ft_move_processing(t_img *old_p, t_img *new_p, t_data *data);
int		ft_error_processing(char *str);

#endif