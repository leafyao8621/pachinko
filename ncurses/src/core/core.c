#include <stdio.h>
#include <stdlib.h>
#include "core.h"

int core_initialize(struct Runner *runner,
                    unsigned iter,
                    unsigned level,
                    unsigned up,
                    unsigned hole1,
                    unsigned hole2,
                    unsigned hole3,
                    unsigned seed) {
    if (!runner) {
        return 1;
    }
    runner->iter = iter;
    if (!(level & 1)) {
        ++level;
    }
    runner->level = level;
    runner->up = up;
    runner->hole[0] = hole1;
    runner->hole[1] = hole2;
    runner->hole[2] = hole3;
    runner->stats.hist = calloc(((level - 1) << 1) + 1, sizeof(unsigned));
    if (!runner->stats.hist) {
        return 2;
    }
    runner->stats.level = 0;
    runner->stats.success = 0;
    mt19937_initialize(&runner->gen, seed);
    return 0;
}

int core_run(struct Runner *runner) {
    if (!runner) {
        return 1;
    }
    unsigned *hist = runner->stats.hist + runner->level - 1;
    for (unsigned i = 0; i < runner->iter; ++i) {
        int num = 0;
        for (unsigned j = 1; j < runner->level; ++j) {
            unsigned temp = mt19937_gen(&runner->gen) % 100;
            num += temp < runner->up ? 1 : -1;
        }
        ++hist[num];
        if (!num) {
            ++runner->stats.level;
            _Bool success = 1;
            for (unsigned k = 0, *l = runner->hole; k < 3; ++k, ++l) {
                if (mt19937_gen(&runner->gen) % *l) {
                    success = 0;
                    break;
                }
            }
            if (success) {
                ++runner->stats.success;
            }
        }
    }
    return 0;
}

int core_finalize(struct Runner *runner) {
    if (!runner) {
        return 1;
    }
    free(runner->stats.hist);
    return 0;
}
