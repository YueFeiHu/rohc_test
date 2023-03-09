#ifndef _PROC_ROHC_H_
#define _PROC_ROHC_H_
#include "comp.h"
#include "decomp.h"
int rohc_proc_init(void);
void rohc_proc_set(struct sc_rohc *c, struct sd_rohc *d);
void rohc_proc_remove(void);
#endif
