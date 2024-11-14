/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:42:58 by ssian             #+#    #+#             */
/*   Updated: 2024/11/06 10:43:00 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_CUB3D_H
# define FT_CUB3D_H
# include <unistd.h>
# include <stdio.h>
# include "../minilibx-linux/mlx.h"
# include "cub3d.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include "libft.h"
# include <math.h>

# define RED				0xFF0000
# define GRAY				0x808080
# define GREEN              0x00FF00
# define WHITE              0xFFFFFF
# define BLUE               0x0000FF

# define CEILING_COLOR      0x87CEEB
# define FLOOR_COLOR        0x964B00


# define WINDOW_WIDTH			2112
# define WINDOW_HEIGHT			896

# define BOX_WIDTH 64
# define BOX_HEIGHT 64

# define STEPS 10
# define FROM_WALL 10
# define PLAYER_RADIUS 10
# define ANGLE_ROTATE 0.05

# define MAP_2D 0

typedef struct s_player
{
    double pos_x;                // player position
    double pos_y;                   
    double dir_x;                // player direction
    double dir_y;                    
    double plane_x;             // camera plane
    double plane_y;              
}               t_player;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_image;

// Structure to hold the texture data
typedef struct s_texture
{
    void *img;
    char *addr;
    int width;
    int height;
    int bpp;                         // Bits per pixel
    int line_length;                 // Line length in bytes
    int endian;                      // Endian format
}           t_texture;


typedef struct	s_data
{
	void	*mlx;
	void	*win;
	t_image	t_img;
    t_player player;
    char **my_map;
    t_texture no;
    t_texture so;
    t_texture we;
    t_texture ea;
}				t_data;


typedef struct	s_ray
{
	double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
    double camera_x;
    double ray_dir_x;
    double ray_dir_y;
    double pos_x;
    double pos_y;
    int box_x;
    int box_y;
    double side_dist_x;
    double side_dist_y;
    double delta_dist_x;
    double delta_dist_y;
    double perp_wall_dist;
    int side;
    int step_x;
    int step_y;
    int line_height;
    int draw_start_y;
    int draw_end_y;
    double wall_x;
    t_texture chosen_texture;
    int texture_x;
    int texture_y;
    int top_dist;
    
}				t_ray;

//cub3d.c
int	render(t_data *data);

//event_handler.c
void	init_event_hooks(t_data *data);
int	key_handler(int keycode, t_data *data);
int	close_handler(t_data *data);

//ray_casting.c
void ray_casting(t_data *data);

//image_helper.c
t_texture load_texture(void *mlx, char *file_path);
void	my_mlx_pixel_put(t_image *t_img, int x, int y, int color);


//movement.c
void rotate_player(double *dir_x, double *dir_y, double *plane_x, double *plane_y, double angle);
void move_front(t_data *data);
void move_back(t_data *data);
void move_left(t_data *data);
void move_right(t_data *data);
int check_point_in_wall(int x, int y, t_data *data);

//init.c
void load_wall_texture(t_data *data);
char **get_map();
void load_player(t_data *data);

//player_helper.c
int get_player_pos_x(int box_x);
int get_player_pos_y(int box_y);
int get_player_dir_x(char facing);
int get_player_dir_y(char facing);
double get_plane_x(char dir);
double get_plane_y(char dir);

//draw_helper.c
void draw_line(t_data *data, int beginX, int beginY, int endX, int endY, int color);
void draw_circle(t_data *data, int cx, int cy, int radius, int color);
void clear_window(t_data *data);
void draw_point_map(int x, int y, t_data *data);

#endif