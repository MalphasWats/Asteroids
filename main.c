#include <avr/io.h>

#include "main.h"

unsigned long t = 0;
unsigned long btn_timer = 0;

byte rotation=0;
int ship_x=64;
int ship_y=32;

bool ship_alive = TRUE;

int x_vectors[] = {0, 1, 2, 4, 4, 4, 2, 1, 0, -1, -2, -4, -4, -4, -2, -1};
int y_vectors[] = {-4, -4, -2, -1, 0, 1, 2, 4, 4, 4, 2, 1, 0, -1, -2, -4};

int a_vectors[] = {-1, 1, 0, -1, 1, 2, -1, -2};

int vx=0;
int vy=0;

unsigned long update_timer = 0;
unsigned long action_timer = 0;

Sprite asteroids[MAX_ASTEROIDS];
Sprite torpedos[MAX_TORPEDOS];

int main (void) 
{    
    initialise();
    // display logo
    for(byte y=0 ; y<LOGO_HEIGHT ; y++)
        for(byte x=0 ; x<LOGO_WIDTH ; x++)
            buffer[(y+2)*SCREEN_WIDTH + (x+16)] = LOGO[y*LOGO_WIDTH + x];
            draw();
            
    note(_A4, 90);
    delay_ms(180);
    note(_C5, 60);
    delay_ms(120);
    note(_E5, 60);
    
    delay_ms(SPLASH_DELAY);
    
    byte buttons;
    
    word score = 0;
    
    asteroids[0] = (Sprite){
        .x = rng() & 63,//19,
        .y = rng() & 127, //22,
        
        .vx = -1,
        .vy = 2,
        
        .size = 3*8,
        
        .tile = LARGE1,
    };
    
    asteroids[1] = (Sprite){
        .x = rng() & 63,//19,
        .y = rng() & 127, //22,
        
        .vx = 1,
        .vy = -1,
        
        .size = 3*8,
        
        .tile = LARGE2,
    };
    
    for(ever)
    {
        t = millis();
        
        buttons = ~PINC;
        if (btn_timer <= t)
        {
            if(buttons & _DOWN)
            {
                click();
                // Hyperspace
                btn_timer = t+BTN_DELAY;
            }
            else if(buttons & _LEFT)
            {
                if (rotation == 0)
                    rotation = 15;
                else
                    rotation -= 1;
                btn_timer = t+BTN_DELAY;
            }
            else if(buttons & _RIGHT)
            {
                if (rotation == 15)
                    rotation = 0;
                else
                    rotation += 1;
                btn_timer = t+BTN_DELAY;
            }
        }
        
        if (action_timer <= t)
        {   
            if(buttons & _A)
            {
                /*if (vx < MAX_VELOCITY &&
                    vx > -MAX_VELOCITY &&
                    vy < MAX_VELOCITY &&
                    vy > -MAX_VELOCITY)
                {*/
                    // accelerate
                    vx += x_vectors[rotation];
                    if (vx < -MAX_VELOCITY)
                        vx = -MAX_VELOCITY;
                    if (vx > MAX_VELOCITY)
                        vx = MAX_VELOCITY;
                        
                    vy += y_vectors[rotation];
                    if (vy < -MAX_VELOCITY)
                        vy = -MAX_VELOCITY;
                    if (vy > MAX_VELOCITY)
                        vy = MAX_VELOCITY;
                    action_timer = t+ACTION_DELAY;
                //}
                
                // Cycle RNG
                rng();
            }
            
            if(buttons & _B)
            {
                click();
                for (byte i=0 ; i<MAX_TORPEDOS ; i++)
                {
                    if (torpedos[i].size == 0)
                    {
                        torpedos[i] = (Sprite){
                            .x = ship_x+3,
                            .y = ship_y+3,
                            .vx = x_vectors[rotation],
                            .vy = y_vectors[rotation],
                            .size = 8,
                            .tile = 0,
                        };
                        break;
                    }
                }
                action_timer = t+ACTION_DELAY;
            }
        }
        
        if (update_timer <= t)
        {
            ship_x += vx;
            ship_y += vy;
            
            for (byte i=0 ; i<MAX_ASTEROIDS ; i++)
            {
                if (asteroids[i].size > 0)
                {
                    asteroids[i].x += asteroids[i].vx;
                    asteroids[i].y += asteroids[i].vy;
                    
                    if (asteroids[i].x < -asteroids[i].size)
                    {
                        asteroids[i].x = SCREEN_WIDTH;
                    }
                    if (asteroids[i].x > SCREEN_WIDTH)
                    {
                        asteroids[i].x = -asteroids[i].size;
                    }
                    
                    if (asteroids[i].y < -asteroids[i].size)
                    {
                        asteroids[i].y = SCREEN_HEIGHT;
                    }
                    
                    if (asteroids[i].y > SCREEN_HEIGHT)
                    {
                        asteroids[i].y = -asteroids[i].size;
                    }
                }
            }
            
            for (byte i=0 ; i<MAX_TORPEDOS ; i++)
            {
                if (torpedos[i].size > 0)
                {
                    torpedos[i].x += torpedos[i].vx;
                    torpedos[i].y += torpedos[i].vy;
                    torpedos[i].tile += 1;
                    
                    if (torpedos[i].x < -torpedos[i].size)
                    {
                        torpedos[i].x = SCREEN_WIDTH;
                    }
                    if (torpedos[i].x > SCREEN_WIDTH)
                    {
                        torpedos[i].x = -torpedos[i].size;
                    }
                    
                    if (torpedos[i].y < -torpedos[i].size)
                    {
                        torpedos[i].y = SCREEN_HEIGHT;
                    }
                    
                    if (torpedos[i].y > SCREEN_HEIGHT)
                    {
                        torpedos[i].y = -torpedos[i].size;
                    }
                    
                    if (torpedos[i].tile == 16)
                       torpedos[i].size = 0;
                }
            }
                    
            update_timer = t + UPDATE_DELAY;
        }
        
        if (ship_x < -4)
            ship_x += SCREEN_WIDTH+4;
        if (ship_x > SCREEN_WIDTH+4)
            ship_x -= SCREEN_WIDTH+4;
            
        if (ship_y < -4)
            ship_y += SCREEN_HEIGHT+4;
        if (ship_y > SCREEN_HEIGHT+4)
            ship_y -= SCREEN_HEIGHT-4;
            
            
        for (word i=0 ; i<(SCREEN_WIDTH*SCREEN_ROWS) ; i++)
            buffer[i] = STARFIELD[i];
            
        for (byte i=0 ; i<MAX_ASTEROIDS ; i++)
        {
            
            draw_asteroid(&asteroids[i]);
        }
        
        byte c;
        for (byte i=0 ; i<MAX_TORPEDOS ; i++)
        {
            if (torpedos[i].size > 0)
            {
                draw_tile(&TORPEDO[0], &TORPEDO[8], torpedos[i].x, torpedos[i].y);
                
                c = collide_with_asteroid(torpedos[i].x, torpedos[i].y);
                if (c < MAX_ASTEROIDS)
                {
                    torpedos[i].size = 0;
                    asteroids[c].vx = a_vectors[rng() & 7];
                    asteroids[c].vy = a_vectors[rng() & 7];
                    
                    if (asteroids[c].size == 3*8)
                    {
                        asteroids[c].size = 2*8;
                        asteroids[c].tile = MEDIUM1;
                        
                        for (byte a=0; a<MAX_ASTEROIDS ; a++)
                        {
                            if (asteroids[a].size == 0)
                            {
                                asteroids[a] = (Sprite){
                                    .x = asteroids[c].x,
                                    .y = asteroids[c].y,
                                    
                                    .vx = a_vectors[rng() & 7],
                                    .vy = a_vectors[rng() & 7],
                                    
                                    .size = 2*8,
                                    
                                    .tile = MEDIUM2,
                                };
                                break;
                            }
                        }
                        
                    }
                    else if (asteroids[c].size == 2*8)
                    {
                        asteroids[c].size = 8;
                        asteroids[c].tile = SMALL1;
                        
                        for (byte a=0; a<MAX_ASTEROIDS ; a++)
                        {
                            if (asteroids[a].size == 0)
                            {
                                asteroids[a] = (Sprite){
                                    .x = asteroids[c].x,
                                    .y = asteroids[c].y,
                                    
                                    .vx = a_vectors[rng() & 7],
                                    .vy = a_vectors[rng() & 7],
                                    
                                    .size = 8,
                                    
                                    .tile = SMALL3,
                                };
                                break;
                            }
                        }
                        
                        for (byte a=0; a<MAX_ASTEROIDS ; a++)
                        {
                            if (asteroids[a].size == 0)
                            {
                                asteroids[a] = (Sprite){
                                    .x = asteroids[c].x,
                                    .y = asteroids[c].y,
                                    
                                    .vx = a_vectors[rng() & 7],
                                    .vy = a_vectors[rng() & 7],
                                    
                                    .size = 8,
                                    
                                    .tile = SMALL2,
                                };
                                break;
                            }
                        }
                    }
                    else 
                    {
                        asteroids[c].size = 0;
                    }
                }
            }
        }
        
        
        if (ship_alive)
        {
            c = collide_with_asteroid(ship_x, ship_y);
            if (c < MAX_ASTEROIDS)
            {
                ship_alive = FALSE;
                asteroids[MAX_ASTEROIDS-1] = (Sprite){
                                                .x = ship_x,
                                                .y = ship_y,
                                                .vx = -1,
                                                .vy = 2,
                                                .size = 8,
                                                .tile = DEBRIS,
                                            };
                                            
                asteroids[MAX_ASTEROIDS-2] = (Sprite){
                                                .x = ship_x,
                                                .y = ship_y,
                                                .vx = 0,
                                                .vy = 1,
                                                .size = 8,
                                                .tile = DEBRIS+1,
                                            };
                asteroids[MAX_ASTEROIDS-3] = (Sprite){
                                                .x = ship_x,
                                                .y = ship_y,
                                                .vx = 1,
                                                .vy = -1,
                                                .size = 8,
                                                .tile = DEBRIS+2,
                                            };
                asteroids[MAX_ASTEROIDS-4] = (Sprite){
                                                .x = ship_x,
                                                .y = ship_y,
                                                .vx = 2,
                                                .vy = 1,
                                                .size = 8,
                                                .tile = DEBRIS+3,
                                            };
            }
            
            draw_tile(&SHIP[rotation*8], &SHIP_MASKS[rotation*8], ship_x, ship_y);
        }
        
        
        draw();
    }
}

byte collide_with_asteroid(int x, int y)
{
    for (byte i=0 ; i<MAX_ASTEROIDS ; i++)
    {
        if (asteroids[i].size > 0)
        {
            if (x > asteroids[i].x &&
                x < asteroids[i].x+asteroids[i].size &&
                y > asteroids[i].y &&
                y < asteroids[i].y+asteroids[i].size)
            {
                return i;
            }
        }
    }
    return MAX_ASTEROIDS;
}

void draw_asteroid(Sprite *a)
{
    byte tiles = a->size >> 3;
    //byte half_width = a->size >> 1;
    
    for(byte h=0 ; h<tiles ; h++)
    {
        for (byte w=0 ; w<tiles ; w++)
        {
            
            draw_tile(&ASTEROIDS[(a->tile+(h*tiles+w))*8], &ASTEROID_MASKS[(a->tile+(h*tiles+w))*8], a->x+(w*8), a->y+(h*8));
            
        }
    }
    
}

void draw_tile(const byte __memx *glyph, const byte __memx *mask, int x, int y)
{
    /* is the tile actually visible */
    if (x < -7 || x >= SCREEN_WIDTH || y < -7 || y >= SCREEN_HEIGHT)
        return;
    
    
    int y_ = y;
    
    if (y < 0)
        y_ = 0-y;
        
    int tile_start = ((y_ >> 3) * SCREEN_WIDTH) + x;
    
    byte y_offset_a = y & 7; // y % 8
    byte y_offset_b = 8-y_offset_a;
    
    byte glyph_index = 0;
    byte tile_width = 8;
    if (x < 0)
    {
        tile_start -= x;
        glyph_index = 0-x;
        tile_width -= glyph_index;
    }
    
    if (x > SCREEN_WIDTH-8)
    {
        tile_width = SCREEN_WIDTH-x;
    }
    
    if (y < 0)
    {
        y_offset_a = 8;
        y_offset_b = 0-y;
        tile_start -= SCREEN_WIDTH;
    }
    
    if (y > SCREEN_HEIGHT-8)
    {
        y_offset_b = 8;
    }
    
    for(byte tile_offset=0 ; tile_offset<tile_width ; tile_offset++, glyph_index++)
    {
        if (y_offset_a < 8)
        {
            buffer[tile_start+tile_offset] &= (mask[glyph_index] << y_offset_a) | ~(0xff << y_offset_a);
            buffer[tile_start+tile_offset] |= glyph[glyph_index] << y_offset_a;
        }
        if (y_offset_b < 8)
        {
            buffer[tile_start+SCREEN_WIDTH+tile_offset] &= (mask[glyph_index] >> y_offset_b) | ~(0xff >> y_offset_b);
            buffer[tile_start+SCREEN_WIDTH+tile_offset] |= glyph[glyph_index] >> y_offset_b;
        }
        
        /*if (y_offset_a < 8)
        {
            
            buffer[tile_start+tile_offset] |= glyph[glyph_index] << y_offset_a;
        }
        if (y_offset_b < 8)
        {
            buffer[tile_start+SCREEN_WIDTH+tile_offset] |= glyph[glyph_index] >> y_offset_b;
        }*/
    }
}