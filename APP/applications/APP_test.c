#include "App_test.h"
#include "Lib_Log_Util.h"
#include "OS_TASK.h"
#include "MCAL_Timer.h"
#include "MCAL_GPIO.h"

void APP_test_init(void)
{

}

void APP_test_mainfunction(void)
{
    MCAL_GPIO_FlipcBit(GPIOC,GPIO_Pin_13);
}

