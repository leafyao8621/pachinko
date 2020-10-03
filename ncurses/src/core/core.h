#ifndef _CORE_H_
#define _CORE_H_

#include "../util/mt19937.h"

struct Runner {
    unsigned iter, level, up, hole[3];
    struct MT19937 gen;
    struct {
        unsigned *hist;
        unsigned level, success;
    } stats;
};

int core_initialize(struct Runner *runner,
                    unsigned iter,
                    unsigned level,
                    unsigned up,
                    unsigned hole1,
                    unsigned hole2,
                    unsigned hole3,
                    unsigned seed);
int core_run(struct Runner *runner);
int core_finalize(struct Runner *runner);

#endif
