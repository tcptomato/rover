#ifndef __JOYSTICK_H
#define __JOYSTICK_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>

union input_events
{
	struct {
	int16_t js1_lr;
	int16_t js1_ud;
	int16_t js2_lr;
	int16_t js2_ud;
	int16_t gp_lr;
	int16_t gp_ud;
	int16_t bt_tri;
	int16_t bt_cir;
	int16_t bt_x;
	int16_t bt_sqr;
	int16_t bt_l1;
	int16_t bt_r1;
	int16_t bt_l2;
	int16_t bt_r2;
	int16_t bt_sel;
	int16_t bt_strt;
	int16_t js1_bt;
	int16_t js2_bt;
	};
	int16_t inps[18];
};


extern volatile union input_events ie;

void* joystick_main(void *);

#ifdef __cplusplus
}
#endif

#endif
