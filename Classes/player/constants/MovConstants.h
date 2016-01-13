#ifndef _MOV_CONSTANTS_H_
#define _MOV_CONSTANTS_H_

#include "util/common/UtilMacros.h"

#define JMP_LOW_CYCLE 22
#define JMP_HIGH_CYCLE 27

#define STEP_PX 4
#define MAX_STEP_PX 12

#define JMPS_PX 6
#define GRAVITY_PX 2

#define MAX_FALL_PX 8

#define WLS_STEP p(-STEP_PX,0)
#define WRS_STEP p(STEP_PX,0)
#define JMPS_STEP p(0,JMPS_PX)
#define STAND_STEP p(0,0)

#define GRAVITY p(0, -GRAVITY_PX)

#define ORIENTATION_LEFT 0
#define ORIENTATION_RIGHT 1
#define ORIENTATION_NONE -1

#endif // _MOV_CONSTANTS_H_
