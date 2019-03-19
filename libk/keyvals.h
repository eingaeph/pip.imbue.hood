enum KEY_CODES
{
        KEY_NULL = 0,       /* NULL */
        CTRL_B = 2,         /* Ctrl-b */
        CTRL_C = 3,         /* Ctrl-c */
        CTRL_D = 4,         /* Ctrl-d */
        CTRL_F = 6,         /* Ctrl-f */
        CTRL_H = 8,         /* Ctrl-h */
        TAB = 9,            /* Tab */
        CTRL_L = 12,        /* Ctrl+l */
        ENTER = 13,         /* Enter */
        CTRL_Q = 17,        /* Ctrl-q */
        CTRL_S = 19,        /* Ctrl-s */
        CTRL_U = 21,        /* Ctrl-u */
        ESC = 27,           /* Escape */
        BACKSPACE =  127,   /* Backspace */

        /* The following are soft codes, 
           reported by the terminal 
           as groups of glyphs. */

        ARROW_LEFT = 1000,
/*1001*/ARROW_RIGHT,
/*1002*/ARROW_UP,
/*1003*/ARROW_DOWN,
/*1004*/INSERT_KEY,
/*1005*/DEL_KEY,
/*1006*/HOME_KEY,
/*1007*/END_KEY,
/*1008*/PAGE_UP,
/*1009*/PAGE_DOWN
};
