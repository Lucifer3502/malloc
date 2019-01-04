/*
 * m_mem.h
 *
 *  Created on: 2019/1/3
 *      Author: heyan
 */

#ifndef INCLUDE_M_MEM_H_
#define INCLUDE_M_MEM_H_

#include "stdint.h"
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/*
* please redefine MEM_BUF_SIZE and MEM_BUF_SIZE according to your environment;
* MEM_BUF_SIZE: global heap size; MEM_BUF_MIN: the malloc min size;
*/
#define MEM_BUF_SIZE    (10 * 1024)
#define MEM_BUF_MIN     (32)
#define MEM_ALIGN_SIZE  (0x04)
#define SIZE_OF_POINT   (sizeof(void *))

#define MEM_API(func_name)   hy_##func_name
#define MEM_API_ATTR  

#define MEM_LOG(fmt, ...)  printf(fmt, ##__VA_ARGS__)


#define MEM_LOG_DEBUG(fmt, ...)  \
    do {\
        MEM_LOG("[DEBUG]: %s(), (line: %d), " fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
    }while(0)
    
#define MEM_LOG_INFO(fmt, ...)  \
    do {\
        MEM_LOG("[INFO]: %s(), (line: %d), " fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
    }while(0)
    
#define MEM_LOG_ERROR(fmt, ...) \
    do {\
        MEM_LOG("[ERROR]: %s(), (line: %d), " fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
    }while(0)
    
#define MEM_LOG_FATAL(fmt, ...) \
    do {\
        MEM_LOG("[FATAL]: %s(), (line: %d), " fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
    }while(0)


/*
* Note: not thread safe!!! Please remember that!
*/
void *MEM_API(malloc)(uint32_t size);

void MEM_API(free)(void *ptr);

uint32_t MEM_API(get_free_heap_size)(void);

void MEM_API(show_mem_map)(void);


#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
}
#endif

#endif /* INCLUDE_M_MEM_H_ */
