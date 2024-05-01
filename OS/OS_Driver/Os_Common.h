#ifndef MINI_OS_COMMON_H_
#define MINI_OS_COMMON_H_

#include "Platform_Types.h"

#define _DI() __disable_irq()//DisableInterrupts
#define _EI() __enable_irq()//EnableInterrupts

#define OS_LOCAL //static
#define OS_EXTERN //extern

#define OS_RET_NG 0
#define OS_RET_OK 1

#endif

