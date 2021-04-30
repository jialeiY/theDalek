ASM=arm-none-eabi-gcc
CC=arm-none-eabi-gcc
CPP=arm-none-eabi-g++
LINKER=arm-none-eabi-gcc

COMMFLAGS += -DSTM32F40_41xxx
COMMFLAGS += -mcpu=cortex-m4 
COMMFLAGS += -O2 
COMMFLAGS += -ggdb 
COMMFLAGS += -fomit-frame-pointer 
COMMFLAGS += -falign-functions=16 
COMMFLAGS += -ffunction-sections 
COMMFLAGS += -fdata-sections 
COMMFLAGS += -fno-common 
#COMMFLAGS += -Wa,-amhls=build/lst/crt0_v7m.lst
COMMFLAGS += -DCORTEX_USE_FPU=FALSE  
COMMFLAGS += -DTHUMB_PRESENT 
COMMFLAGS += -mno-thumb-interwork 
COMMFLAGS += -DTHUMB_NO_INTERWORKING 
COMMFLAGS += -mthumb 
COMMFLAGS += -DTHUMB
COMMFLAGS += -c 


ASMFLAGS = $(COMMFLAGS)

#CFLAGS += -Wa,-alms=build/lst/hal_st.lst 

CFLAGS = $(COMMFLAGS)
CFLAGS += -Wall 
CFLAGS += -Wextra 
CFLAGS += -Wundef 
CFLAGS += -Wstrict-prototypes 

CPPFLAGS = $(COMMFLAGS)
CFLAGS += -Wall 
CFLAGS += -Wextra 
CFLAGS += -Wundef 


LDFLAGS += -mcpu=cortex-m4 
LDFLAGS += -O2 
LDFLAGS += -ggdb 
LDFLAGS += -fomit-frame-pointer 
LDFLAGS += -falign-functions=16 
LDFLAGS += -ffunction-sections 
LDFLAGS += -fdata-sections 
LDFLAGS += -fno-common 
LDFLAGS += -nostartfiles
LDFLAGS += -mno-thumb-interwork 
LDFLAGS += -mthumb   