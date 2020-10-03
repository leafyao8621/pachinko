#include <stdio.h>
#include <time.h>
#include <ncurses.h>
#include "../core/core.h"

static signed char loc = 0;
static unsigned iter = 100;
static unsigned level = 5;
static unsigned up = 50;
static unsigned hole1 = 3;
static unsigned hole2 = 4;
static unsigned hole3 = 5;

void controller_initialize(void) {
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    mvaddstr(0, 0, "PACHINKO");
    mvprintw(1, 0, "%-10s:%6d", "Iter", 100);
    mvprintw(2, 0, "%-10s:%6d", "Level", 5);
    mvprintw(3, 0, "%-10s:%6d%%", "Up", 50);
    mvprintw(4, 0, "%-10s:%6d", "Hole 1", 3);
    mvprintw(5, 0, "%-10s:%6d", "Hole 2", 4);
    mvprintw(6, 0, "%-10s:%6d", "Hole 3", 5);
    move(1, 16);
}

static void run_simulation(void) {
    struct Runner runner;
    core_initialize(&runner, iter, level, up, hole1, hole2, hole3, time(0));
    core_run(&runner);
    mvprintw(20, 0, "%-10s:%6d", "Level", runner.stats.level);
    mvprintw(21, 0, "%-10s:%6d", "Success", runner.stats.success);
    unsigned *hist = runner.stats.hist + runner.level - 1;
    int st = -8;
    if (runner.level - 1 < 8) {
        st = 1 - (int)runner.level;
    }
    unsigned max = hist[st];
    for (int i = st + 2; i <= -st; i += 2) {
        if (hist[i] > max) {
            max = hist[i];
        }
    }
    double scale = 20.0 / max;
    char buf[20];
    for (int i = st, j = 10; i <= -st; i += 2, ++j) {
        unsigned num = scale * hist[i];
        mvprintw(j, 0, "%40c", ' ');
        snprintf(buf, 19, "%%+4d:%%0%dd:%%-6d", num);
        mvprintw(j, 0, buf, i, 0, hist[i]);
    }
    core_finalize(&runner);
}

int controller_handle_key_press(void) {
    int ch = getch();
    switch (ch) {
    case 'Q':
    case 'q':
        return 0;
    case KEY_UP:
        switch (loc) {
        case 0:
            iter += 1000;
            if (iter > 10000) {
                iter = 10000;
            }
            break;
        case 1:
            level += 10;
            if (level > 10000) {
                level = 100;
            }
            break;
        case 2:
            up += 10;
            if (up > 10000) {
                up = 10000;
            }
            break;
        case 3:
            hole1 += 10;
            if (hole1 > 10000) {
                hole1 = 10000;
            }
            break;
        case 4:
            hole2 += 10;
            if (hole2 > 10000) {
                hole2 = 10000;
            }
            break;
        case 5:
            hole3 += 10;
            if (hole3 > 10000) {
                hole3 = 10000;
            }
            break;
        }
        break;
    case KEY_DOWN:
        switch (loc) {
        case 0:
            iter -= 1000;
            if ((int)iter < 100) {
                iter = 100;
            }
            break;
        case 1:
            level -= 10;
            if ((int)level < 3) {
                level = 3;
            }
            break;
        case 2:
            up -= 10;
            if ((int)up < 1) {
                up = 1;
            }
            break;
        case 3:
            hole1 -= 10;
            if ((int)hole1 < 1) {
                hole1 = 1;
            }
            break;
        case 4:
            hole2 -= 10;
            if ((int)hole2 < 1) {
                hole2 = 1;
            }
            break;
        case 5:
            hole3 -= 10;
            if ((int)hole3 < 1) {
                hole3 = 1;
            }
            break;
        }
        break;
    case KEY_RIGHT:
        switch (loc) {
        case 0:
            iter += 100;
            if (iter > 10000) {
                iter = 10000;
            }
            break;
        case 1:
            level += 2;
            if (level > 100) {
                level = 100;
            }
            break;
        case 2:
            up += 1;
            if (up > 10000) {
                up = 10000;
            }
            break;
        case 3:
            hole1 += 1;
            if (hole1 > 10000) {
                hole1 = 10000;
            }
            break;
        case 4:
            hole2 += 1;
            if (hole2 > 10000) {
                hole2 = 10000;
            }
            break;
        case 5:
            hole3 += 1;
            if (hole3 > 10000) {
                hole3 = 10000;
            }
            break;
        }
        break;
    case KEY_LEFT:
        switch (loc) {
        case 0:
            iter -= 100;
            if ((int)iter < 100) {
                iter = 100;
            }
            break;
        case 1:
            level -= 2;
            if ((int)level < 3) {
                level = 3;
            }
            break;
        case 2:
            up -= 1;
            if ((int)up < 1) {
                up = 1;
            }
            break;
        case 3:
            hole1 -= 1;
            if ((int)hole1 < 1) {
                hole1 = 1;
            }
            break;
        case 4:
            hole2 -= 1;
            if ((int)hole2 < 1) {
                hole2 = 1;
            }
            break;
        case 5:
            hole3 -= 1;
            if ((int)hole3 < 1) {
                hole3 = 1;
            }
            break;
        }
        break;
    case '.':
        loc = (loc + 1) % 6;
        break;
    case ',':
        loc = (((loc - 1) % 6) + 6) % 6;
        break;
    case ' ':
        run_simulation();
        break;
    }
    mvprintw(1, 0, "%-10s:%6d", "Iter", iter);
    mvprintw(2, 0, "%-10s:%6d", "Level", level);
    mvprintw(3, 0, "%-10s:%6d%%", "Up", up);
    mvprintw(4, 0, "%-10s:%6d", "Hole 1", hole1);
    mvprintw(5, 0, "%-10s:%6d", "Hole 2", hole2);
    mvprintw(6, 0, "%-10s:%6d", "Hole 3", hole3);
    move(loc + 1, 16);
    return 1;
}

void controller_finalize(void) {
    endwin();
}
