/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:31:35 by ssian             #+#    #+#             */
/*   Updated: 2024/11/12 11:31:41 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static void ray_init(t_ray *ray, t_data *data)
{
    ray->dir_x = data->player.dir_x;
    ray->dir_y = data->player.dir_y;
    ray->plane_x = data->player.plane_x;
    ray->plane_y = data->player.plane_y;
}

static void ray_setup(t_ray *ray, t_data *data, int x)
{
    ray->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
    ray->ray_dir_x = ray->dir_x + ray->plane_x * ray->camera_x;
    ray->ray_dir_y = ray->dir_y + ray->plane_y * ray->camera_x;
    ray->pos_x = data->player.pos_x / BOX_WIDTH;
    ray->pos_y = data->player.pos_y / BOX_HEIGHT;
    ray->box_x = (int)ray->pos_x;
    ray->box_y = (int)ray->pos_y;
    ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
    ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

/* calculate initial step and initial side dist */
static void cal_step_side_dist(t_ray *ray)
{
     
    if (ray->ray_dir_x < 0) 
    {
        ray->step_x = -1;
        ray->side_dist_x = (ray->pos_x - ray->box_x) * ray->delta_dist_x;
    } 
    else 
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->box_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
    }

    if (ray->ray_dir_y < 0) 
    {
        ray->step_y = -1;
        ray->side_dist_y = (ray->pos_y - ray->box_y) * ray->delta_dist_y;
    } 
    else 
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->box_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
    }
}

/* perform DDA, stop when wall hit */
static void perform_dda(t_ray *ray, t_data *data)
{
    int hit;    

    hit = 0;
    while (hit == 0) 
    {
        // Jump to the next map square, either in x-direction or y-direction
        if (ray->side_dist_x < ray->side_dist_y) 
        {
            ray->side_dist_x = ray->side_dist_x + ray->delta_dist_x;
            ray->box_x = ray->box_x + ray->step_x;                            //x-direction 
            ray->side = 0;
        } 
        else 
        {
            ray->side_dist_y = ray->side_dist_y + ray->delta_dist_y;
            ray->box_y = ray->box_y + ray->step_y;                           //y-direction
            ray->side = 1;
        }
        if (data->my_map[ray->box_y][ray->box_x] == '1')                     // Check if the ray has hit a wall
            hit = 1;
    }

    //Calculate the perpendicular distance to the wall to avoid the fish-eye effect
    //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
    if(ray->side == 0) 
        ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
    else          
        ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
}

/* draw rays from player to the walls*/
static void draw_ray(t_ray *ray, t_data *data)
{
    // Calculate the end coordinates of the ray where it hits the wall
    double ray_end_x;
    double ray_end_y;

    ray_end_x = ray->pos_x + ray->ray_dir_x * ray->perp_wall_dist;
    ray_end_y = ray->pos_y + ray->ray_dir_y * ray->perp_wall_dist;
    draw_line(data, (ray->pos_x * BOX_WIDTH), (ray->pos_y * BOX_HEIGHT), (ray_end_x * BOX_WIDTH), (ray_end_y * BOX_HEIGHT), RED);
}

/* calculate height of the line, start_y, end_y points to draw */
static void cal_line_height(t_ray *ray)
{
    ray->line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);        // Calculate the height of the line
    ray->draw_start_y = (-ray->line_height / 2) + (WINDOW_HEIGHT / 2);    // Calculate the start and end positions of the line
    if (ray->draw_start_y < 0) 
        ray->draw_start_y = 0;
    ray->draw_end_y = (ray->line_height / 2) + (WINDOW_HEIGHT / 2);
    if (ray->draw_end_y >= WINDOW_HEIGHT) 
        ray->draw_end_y = WINDOW_HEIGHT - 1;
    
    //draw 3d box        
    //draw_line(data, x, drawStart , x, drawEnd, BLUE);
}

/* calculate the x point hit on the wall, exact point of intersection between the ray and the wall,
   Note that even if it's called wall_x, it's actually an y-coordinate of the wall if side==1,
   but it's always the x-coordinate of the texture.
*/
static void cal_wall_hit(t_ray *ray)
{
    if (ray->side == 0) 
        ray->wall_x = ray->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
    else 
        ray->wall_x = ray->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
    ray->wall_x = ray->wall_x - floor(ray->wall_x);
}

/*static draw_wall(t_ray *ray, t_data *data, int x)
{
    // Render the wall slice
    int y;
    int texture_y;
    int top_dist;
    char *pixel;
    unsigned int color;

    y = ray->draw_start_y;
    while (y < ray->draw_end_y)
    //for (int y = ray->draw_start_y; y < ray->draw_end_y; y++) 
    {
        top_dist = (y * 256 - WINDOW_HEIGHT * 128 + ray->line_height * 128); // Calculate distance from top of the screen
        texture_y = ((top_dist * BOX_HEIGHT) / ray->line_height) / 256; // Map y-coordinate to the texture
        
        pixel = chosen_texture.addr + (texture_y * chosen_texture.line_length + texture_x * (chosen_texture.bpp / 8));
        color = *(unsigned int *)pixel;


        // Draw pixel to screen (replace this with your own method)
        my_mlx_pixel_put(&(data->t_img), x, y, color);
        y++;
    }
}*/

/* select the texture based on the wall side to draw 
   side = 0 is vertical wall, side = 1 is horizontal wall
*/
static void chose_texture(t_ray *ray, t_data *data)
{
    if (ray->side == 0)                                // Vertical wall (east/west)
    {    
        if (ray->ray_dir_x > 0)
            ray->chosen_texture = data->ea;
        else
            ray->chosen_texture = data->we;
    } 
    else                                               // Horizontal wall (north/south)
    {           
        if (ray->ray_dir_y > 0)
            ray->chosen_texture = data->so;
        else
            ray->chosen_texture = data->no;
    }
}

/* map wall_x to the texture x coordinate*/
static void get_texture_x(t_ray *ray)
{
    // Map wallX to the texture's x-coordinate (0 to TEXTURE_WIDTH)
    //texture_x = (int)(ray->wall_x * (double)BOX_WIDTH);
    ray->texture_x = (int)(ray->wall_x * (double)ray->chosen_texture.width);
//    if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1 && ray->ray_dir_y < 0)) 
        //texture_x = BOX_WIDTH - texture_x - 1; // Flip texture for certain sides to correct orientation
//        ray->texture_x = ray->chosen_texture.width - ray->texture_x - 1; // Flip texture for certain sides to correct orientation
        // ray->texture_x = ray->chosen_texture.width - ray->texture_x - 1;

        // Flip condition (refine based on your ray casting logic)
    if (ray->side == 0 && ray->ray_dir_x < 0) // Flip horizontally for specific wall
        ray->texture_x = ray->chosen_texture.width - ray->texture_x - 1;
    else if (ray->side == 1 && ray->ray_dir_y > 0) // Flip vertically for another wall
        ray->texture_x = ray->chosen_texture.width - ray->texture_x - 1;


        
    if (ray->texture_x < 0) 
        ray->texture_x = 0;
    if (ray->texture_x >= ray->chosen_texture.width) 
        ray->texture_x = ray->chosen_texture.width - 1;
}

/*static void get_texture_x(t_ray *ray) {
    // Vertical mapping
    ray->top_dist = (y * 256 - WINDOW_HEIGHT * 128 + ray->line_height * 128);
    ray->texture_y = (ray->top_dist * ray->chosen_texture.height) / (ray->line_height * 256);

    // Vertical flip (if needed)
    ray->texture_y = ray->chosen_texture.height - ray->texture_y - 1;

    // Clamp texture_y
    if (ray->texture_y < 0)
        ray->texture_y = 0;
    if (ray->texture_y >= ray->chosen_texture.height)
        ray->texture_y = ray->chosen_texture.height - 1;

    // Horizontal mapping (flip texture horizontally)
    ray->texture_x = ray->chosen_texture.width - ray->texture_x - 1;

    // Clamp texture_x
    if (ray->texture_x < 0)
        ray->texture_x = 0;
    if (ray->texture_x >= ray->chosen_texture.width)
        ray->texture_x = ray->chosen_texture.width - 1;
}*/

/*static void get_texture_x(t_ray *ray) {
    // Flip texture horizontally
    ray->texture_x = ray->chosen_texture.width - ray->texture_x - 1;

    // Clamp texture_x within valid range (optional for safety)
    if (ray->texture_x < 0)
        ray->texture_x = 0;
    if (ray->texture_x >= ray->chosen_texture.width)
        ray->texture_x = ray->chosen_texture.width - 1;
}*/


static void get_texture_y(t_ray *ray, int y)
{
    ray->top_dist = (y * 256 - WINDOW_HEIGHT * 128 + ray->line_height * 128);                    // Calculate distance from top of the screen
    ray->texture_y = ((ray->top_dist * ray->chosen_texture.height) / ray->line_height) / 256;    // Map y-coordinate to the texture
    if (ray->texture_y < 0) 
        ray->texture_y = 0;
    if (ray->texture_y >= BOX_HEIGHT) 
        ray->texture_y = BOX_HEIGHT - 1;
}

/*static void get_texture_y(t_ray *ray, int y) {
    // Calculate distance from top of the screen in scaled space
    ray->top_dist = (y * 256 - WINDOW_HEIGHT * 128 + ray->line_height * 128);

    // Map y-coordinate to the texture coordinate
    ray->texture_y = (ray->top_dist * ray->chosen_texture.height) / (ray->line_height * 256);

    // Flip texture vertically if needed
    ray->texture_y = ray->chosen_texture.height - ray->texture_y - 1;

    // Clamp texture_y within valid range
    if (ray->texture_y < 0)
        ray->texture_y = 0;
    if (ray->texture_y >= ray->chosen_texture.height)
        ray->texture_y = ray->chosen_texture.height - 1;
}*/


/* draw the texure wall on screen */
static void draw_texture_wall(t_ray *ray, t_data *data, int x)
{
    int y;
    char *pixel;
    unsigned int color;

    get_texture_x(ray);
    y = ray->draw_start_y;
    while (y < ray->draw_end_y) 
    {
        get_texture_y(ray, y);
        pixel = ray->chosen_texture.addr + (ray->texture_y * ray->chosen_texture.line_length + ray->texture_x * (ray->chosen_texture.bpp / 8));
        color = *(unsigned int *)pixel;
        my_mlx_pixel_put(&(data->t_img), x, y, color);
        y++;
    }
}

static void draw_ceiling(t_ray *ray, t_data *data, int x)
{
    int y;

    y = 0;
    while (y < ray->draw_start_y)
    {
        //my_mlx_pixel_put(&(data->t_img), x, y, CEILING_COLOR);
        my_mlx_pixel_put(&(data->t_img), x, y, data->ceiling_color);
        y++;
    }
}

static void draw_floor(t_ray *ray, t_data *data, int x)
{
    int y;

    y = ray->draw_end_y;
    while (y < WINDOW_HEIGHT)
    {
        //my_mlx_pixel_put(&(data->t_img), x, y, FLOOR_COLOR);
        my_mlx_pixel_put(&(data->t_img), x, y, data->floor_color);
        y++;
    }
}

void ray_casting(t_data *data)
{
    int x;
    t_ray ray;

    ft_bzero(&ray, sizeof(t_ray));
    ray_init(&ray, data);
    x = 0;
    while (x < WINDOW_WIDTH) 
    {
        ray_setup(&ray, data, x);
        cal_step_side_dist(&ray);  
        perform_dda(&ray, data);
        if (MAP_2D == 1)
            draw_ray(&ray, data);
        cal_line_height(&ray);
        cal_wall_hit(&ray);
        if (MAP_2D == 0)
        {
            chose_texture(&ray, data);        
            draw_texture_wall(&ray, data, x);
            draw_ceiling(&ray, data, x);
            draw_floor(&ray, data, x);
        }
        x++;
    }
}