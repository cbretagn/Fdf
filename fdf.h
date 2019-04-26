/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 20:02:41 by cbretagn          #+#    #+#             */
/*   Updated: 2019/04/26 12:08:18 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#define WIDTH 1600
#define HEIGHT 1200
#define IMG_W 1200
#define IMG_H 800
#define BASE 20
#define	COLOR 0xFFFFFF

typedef struct s_param_line
{
			int			x1;
			int			x2;
			int			y1;
			int			y2;
			int			x_slope;
			int			y_slope;
			int			dir_x;
			int			dir_y;
}				t_param_line;

typedef struct s_matrix
{
			float		x[9];
			float		y[9];
			float		z[9];
			float		mat[9];
}				t_matrix;

typedef struct s_env
{
			void			*mlx_ptr;
			void			*window;
			void			*img;
			int				*str_img;
			int				x;
			int				y;
			int				bpp;
			int				s_l;
			int				endian;
			float			**points;
			int				**projected;
			t_param_line	*line;
			t_matrix		*matrix;
}				t_env;

void		put_pixel(t_env env, int x, int y, int color);
void		draw_line(t_env *env, int color);
void		display_img(t_env *env);
void		assign_points(t_env *env, int p1, int p2);
void		check_line(t_param_line *line); //TODO remove

int			plot(float nb);
int			**generate_array(int x, int y);
void		parallel_proj(int **projected, float **points, int x, int y);

float		**generate_array_points(int x, int y);

float		**get_points(char *file, t_env *env);
//TODO remove
void		print_point(float *point, int i, int x);
void		print_array_points(float **array, int x, int y);

void		matrix_init(t_matrix *matrix);
void		x_matrix(t_matrix *matrix, float angle);
void		y_matrix(t_matrix *matrix, float angle);
void		z_matrix(t_matrix *matrix, float angle);
void		compute_points(t_env *env, t_matrix *matrix, int p1, int p2);
void		print_matrix(float matrix[9]);//TODO remove

int			key_handle(int keycode, t_env *env);
#endif
