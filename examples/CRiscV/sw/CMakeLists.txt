cmake_minimum_required(VERSION 3.8)
set(can_use_assembler TRUE)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_ASM_COMPILER_WORKS 1)
enable_language(C ASM)

project(CRiscV LANGUAGES C)
set(CMAKE_VERBOSE_MAKEFILE 1)

INCLUDE_DIRECTORIES(
    .
    bsp
    driver
    )


file(GLOB HEADERS
    bsp/*.h
    driver/*.h
    )
set(SRCS
    test.c
    platform.c
    platform.h
    )

set(BASE_SRC bsp/crt.S)

get_filename_component(LINKS bsp/linker.ld ABSOLUTE)

add_executable(CRiscV ${BASE_SRC} ${SRCS})

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_C_FLAGS "-march=rv32im -mabi=ilp32 -DUSE_GP -mcmodel=medany -nostartfiles -ffreestanding -specs=nosys.specs -O2 -g")
    target_link_options(CRiscV PUBLIC -march=rv32im -mabi=ilp32 -mcmodel=medany -nostartfiles -ffreestanding -lc -lgcc -Wl,-Bstatic,-T,${LINKS},--print-memory-usage)
else()
    set(CMAKE_C_FLAGS "-march=rv32im -mabi=ilp32 -DUSE_GP -specs=nosys.specs -O3 -fdata-sections -ffunction-sections")
    target_link_options(CRiscV PUBLIC -march=rv32im -mabi=ilp32 -mcmodel=medany -nostartfiles -ffreestanding -lc -lgcc -Wl,-Bstatic,-T,${LINKS},--print-memory-usage,--gc-sections)
endif()

set(CMAKE_ASM_FLAGS ${CMAKE_C_FLAGS})

target_link_libraries(CRiscV c)

add_custom_command(TARGET CRiscV POST_BUILD COMMAND ${CMAKE_OBJCOPY} -O ihex CRiscV CRiscV.hex)
target_sources(CRiscV PRIVATE ${HEADERS} ${LINKS} ${OPENOCD})
