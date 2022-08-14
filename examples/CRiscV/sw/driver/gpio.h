#ifndef GPIO_H_
#define GPIO_H_
#include "io.h"

typedef struct
{
  volatile u32 INPUT;
  volatile u32 OUTPUT;
  volatile u32 OUTPUT_ENABLE;
} Gpio_Reg;


#endif /* GPIO_H_ */


