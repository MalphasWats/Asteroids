#include "asteroids.h"

uint32_t t = 0;
uint32_t btn_timer = 0;

uint8_t rotation=0;
int16_t ship_x=64;
int16_t ship_y=32;

bool ship_alive = TRUE;

int16_t x_vectors[] = {0, 1, 2, 3, 3, 3, 2, 1, 0, -1, -2, -3, -3, -3, -2, -1};
int16_t y_vectors[] = {-3, -3, -2, -1, 0, 1, 2, 3, 3, 3, 2, 1, 0, -1, -2, -3};

int16_t a_vectors[] = {-1, 1, 0, -1, 1, 2, -1, -2};

int16_t vx=0;
int16_t vy=0;

uint32_t update_timer = 0;
uint32_t action_timer = 0;

Sprite asteroids[MAX_ASTEROIDS];
Sprite torpedos[MAX_TORPEDOS];

Sprite d0 = {.x=9*8, .y=4*8, .tile=0};
Sprite d1 = {.x=8*8, .y=4*8, .tile=0};
Sprite d2 = {.x=7*8, .y=4*8, .tile=0};
Sprite d3 = {.x=6*8, .y=4*8, .tile=0};

uint32_t spawn_timer = 0;
uint32_t restart_timer = 0;

uint8_t buttons;

void asteroids_game(void)
{
    rotation=0;
    ship_x=64;
    ship_y=32;

    ship_alive = TRUE;

    vx=0;
    vy=0;

    update_timer = 0;
    action_timer = 0;

    for (uint8_t i=0 ; i<MAX_ASTEROIDS ; i++)
    {
        asteroids[i].size=0;
    }
    for (uint8_t i=0 ; i<MAX_TORPEDOS ; i++)
    {
        torpedos[i].size = 0;
    }

    spawn_timer = 0;
    restart_timer = 0;

    uint16_t score = 0;

    asteroids[0] = (Sprite){
        .x = rng() & 127,//19,
        .y = 0, //22,

        .vx = 1,
        .vy = 1,

        .size = 3*8,

        .tile = LARGE1,
    };

    for(ever)
    {
        t = millis();

        buttons = read_buttons();
        if (btn_timer <= t)
        {
            if(buttons & BTN_DOWN)
            {
                click();
                // Hyperspace
                btn_timer = t+MOVE_DELAY;
            }
            else if(buttons & BTN_LEFT)
            {
                if (rotation == 0)
                    rotation = 15;
                else
                    rotation -= 1;
                btn_timer = t+MOVE_DELAY;
            }
            else if(buttons & BTN_RIGHT)
            {
                if (rotation == 15)
                    rotation = 0;
                else
                    rotation += 1;
                btn_timer = t+MOVE_DELAY;
            }
        }

        if (action_timer <= t && ship_alive)
        {
            if(buttons & BTN_A)
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

            if(buttons & BTN_B)
            {
                click();
                for (uint8_t i=0 ; i<MAX_TORPEDOS ; i++)
                {
                    if (torpedos[i].size == 0)
                    {
                        torpedos[i] = (Sprite){
                            .x = ship_x+3,
                            .y = ship_y+3,
                            .vx = x_vectors[rotation]+vx,
                            .vy = y_vectors[rotation]+vy,
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

            if (spawn_timer <= t)
            {
                for (uint8_t a=0; a<MAX_ASTEROIDS ; a++)
                {
                    if (asteroids[a].size == 0)
                    {
                        asteroids[a] = (Sprite){
                            .x = rng() & 127,//19,
                            .y = rng() & 63, //22,

                            .vx = a_vectors[rng() & 7],
                            .vy = a_vectors[rng() & 7],

                            .size = 3*8,

                            .tile = LARGE2,
                        };
                        break;
                    }
                }
                spawn_timer = t+10000;
            }

            for (uint8_t i=0 ; i<MAX_ASTEROIDS ; i++)
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

            for (uint8_t i=0 ; i<MAX_TORPEDOS ; i++)
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


        for (uint16_t i=0 ; i<(SCREEN_WIDTH*SCREEN_ROWS) ; i++)
            buffer[i] = STARFIELD[i];

        for (uint8_t i=0 ; i<MAX_ASTEROIDS ; i++)
        {

            draw_asteroid(&asteroids[i]);
        }

        uint8_t c;
        for (uint8_t i=0 ; i<MAX_TORPEDOS ; i++)
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

                        for (uint8_t a=0; a<MAX_ASTEROIDS ; a++)
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

                        score += 3;

                    }
                    else if (asteroids[c].size == 2*8)
                    {
                        asteroids[c].size = 8;
                        asteroids[c].tile = SMALL1;

                        for (uint8_t a=0; a<MAX_ASTEROIDS ; a++)
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

                        for (uint8_t a=0; a<MAX_ASTEROIDS ; a++)
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

                        score += 4;
                    }
                    else
                    {
                        asteroids[c].size = 0;

                        score += 6;
                    }
                }
            }
        }


        if (ship_alive)
        {
            c = collide_with_asteroid(ship_x+4, ship_y+4);
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

                draw_int(score, 5, 6*8, 4*8);

                restart_timer = t+3500;
            }

            draw_tile(&SHIP[rotation*8], &SHIP_MASKS[rotation*8], ship_x, ship_y);
        }
        else
        {
            draw_int(score, 5, 6*8, 4*8);

            if (restart_timer <= t)
                return;
        }

        draw();
    }
}

uint8_t collide_with_asteroid(int16_t x, int16_t y)
{
    for (uint8_t i=0 ; i<MAX_ASTEROIDS ; i++)
    {
        if (asteroids[i].size > 0)
        {
            if (x+1 > asteroids[i].x &&
                x-1 < asteroids[i].x+asteroids[i].size &&
                y+1 > asteroids[i].y &&
                y-1 < asteroids[i].y+asteroids[i].size)
            {
                return i;
            }
        }
    }
    return MAX_ASTEROIDS;
}

void draw_asteroid(Sprite *a)
{
    uint8_t tiles = a->size >> 3;
    //byte half_width = a->size >> 1;

    for(uint8_t h=0 ; h<tiles ; h++)
    {
        for (uint8_t w=0 ; w<tiles ; w++)
        {

            draw_tile(&ASTEROIDS[(a->tile+(h*tiles+w))*8], &ASTEROID_MASKS[(a->tile+(h*tiles+w))*8], a->x+(w*8), a->y+(h*8));

        }
    }

}
