#include "main.h"
#include "asteroids.h"


int  main (void)
{
    initialise();

    uint8_t debounce = 0;
    bool button_down = FALSE;

    uint32_t t=0;
    uint8_t buttons;

    for(ever)
    {
        t = millis();

        draw_image(&TITLE, 0, 0);
        draw_battery();
        draw();

        buttons = read_buttons();
        if(buttons == BTN_A && !button_down)
        {
            button_down = TRUE;
            debounce = t+10;
        }

        if (buttons != BTN_A && button_down && debounce <= t)
        {
            button_down = FALSE;
            asteroids_game();
        }
    }
}
