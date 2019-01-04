/*
 * m_mem.c
 *
 *  Created on: 2019/1/3
 *      Author: heyan
 */

#include "common.h"
#include "m_mem.h"

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

typedef struct {
    uint32_t pre:1;  /* the pre mem buf free flag. if valid, flag = 1*/
    uint32_t flag:1; /* self mem buf free flag. if valid, flag = 1*/
    uint32_t size:30;
}mem_header_t;

#define MEM_HEAD_SIZE sizeof(mem_header_t)


static uint8_t g_mem_buf[MEM_BUF_SIZE];

static void MEM_API_ATTR
mem_buf_init(void)
{
    static uint8_t init = 0;
    if(init) {
        return;
    }
    
    mem_header_t *head = (mem_header_t *)g_mem_buf;
    head->pre = 0;
    head->flag = 1;
    head->size = MEM_BUF_SIZE - MEM_HEAD_SIZE;
    init = 1;
}

void MEM_API_ATTR
*MEM_API(malloc)(uint32_t size)
{
    uint32_t sz = (size + (MEM_ALIGN_SIZE - 1)) & (~(MEM_ALIGN_SIZE - 1));
    uint32_t offset = 0;
    mem_header_t *head = (mem_header_t *)(g_mem_buf + offset);
    mem_header_t *next = NULL;
    
    mem_buf_init();
    MEM_LOG_DEBUG("malloc size: %u\r\n", sz);
    if(sz >= MEM_BUF_SIZE) {
        MEM_LOG_FATAL("OVER SIZE: %u\r\n", size);
        return NULL;
    }
    if(sz < MEM_BUF_MIN) {
        sz = MEM_BUF_MIN;
    }
    while(offset < MEM_BUF_SIZE) {
        if(0 == head->flag || head->size < sz) {
            offset += head->size + MEM_HEAD_SIZE;
            head = (mem_header_t *)(g_mem_buf + offset);
            continue;
        }
        
        //change the the next buf info.
        offset += head->size + MEM_HEAD_SIZE;
        if(offset < MEM_BUF_SIZE) {
            next = (mem_header_t *)(g_mem_buf + offset);
            next->pre = 0;
        }
        
        if(head->size < (sz * 2 + MEM_HEAD_SIZE)) {
            //small free buf, do not need to split, so return the whole buf.
            head->flag = 0;
            return (void *)((uint8_t *)head + MEM_HEAD_SIZE);
        } else {
            //big buf, split into two small buf.
            mem_header_t *new = (mem_header_t *)(g_mem_buf + offset - MEM_HEAD_SIZE - sz);
            void *addr = (void *)((uint8_t *)new - SIZE_OF_POINT);

            /*update the head info*/
            head->size -= sz + MEM_HEAD_SIZE;
            
            /*
            * Write head addr in the tail of the free buf.
            * When free the new buf, do not need to find the pre buf head.
            */
            memcpy(addr, &head, SIZE_OF_POINT);
            
            //return the split new buf;
            new->pre = 1;
            new->flag = 0;
            new->size = sz;
            return (void *)((uint8_t *)new + MEM_HEAD_SIZE);
        }
    }
    MEM_LOG_DEBUG("there is no valid free mem size: %u\r\n", size);
    return NULL;
}

void MEM_API_ATTR
MEM_API(free)(void *ptr)
{
    uint32_t offset = 0;
    mem_header_t *head = (mem_header_t *)(g_mem_buf + offset);
    mem_header_t *next = NULL;
    void *addr = NULL;
    
    if(NULL == ptr) {
        return;
    }
    mem_buf_init();
    while(offset < MEM_BUF_SIZE) {
        if(ptr != g_mem_buf + offset + MEM_HEAD_SIZE) {
            offset += head->size + MEM_HEAD_SIZE;
            head = (mem_header_t *)(g_mem_buf + offset);
            continue;
        }

        offset += head->size + MEM_HEAD_SIZE;
        if(offset < MEM_BUF_SIZE) {
            next = (mem_header_t *)(g_mem_buf + offset);
        }
        
        head->flag = 1;
        addr = (void *)((uint8_t *)head + MEM_HEAD_SIZE + head->size - SIZE_OF_POINT);
        memcpy(addr, &head, SIZE_OF_POINT);

        //merge next buf handle;
        if(next) {
            next->pre = 1; 
            if(0 != next->flag) {
                addr = (void *)((uint8_t *)next + MEM_HEAD_SIZE + next->size - SIZE_OF_POINT);
                head->size += next->size + MEM_HEAD_SIZE;
                memcpy(addr, &head, SIZE_OF_POINT);
            }
        }

        //merge pre buf handle;
        if(head->pre) {
            mem_header_t *pre = NULL;
            void *preaddr = (void *)((uint8_t *)head - SIZE_OF_POINT);
            memcpy(&pre, preaddr, SIZE_OF_POINT);
            
            if(NULL == pre || 0 == pre->flag ) {
                MEM_LOG_FATAL("A big bug.\r\n");
                return;
            }
            addr = (void *)((uint8_t *)head + MEM_HEAD_SIZE + head->size - SIZE_OF_POINT);
            pre->size += head->size + MEM_HEAD_SIZE;
            memcpy(addr, &pre, SIZE_OF_POINT);
        }
    }
}

uint32_t MEM_API_ATTR
MEM_API(get_free_heap_size)(void)
{
    uint32_t offset = 0;
    mem_header_t *head = (mem_header_t *)(g_mem_buf + offset);
    uint32_t size = 0;
    mem_buf_init();

    while(offset < MEM_BUF_SIZE) {
        if(head->flag) {
            size += head->size;
        }
        offset += head->size + MEM_HEAD_SIZE;
        head = (mem_header_t *)(g_mem_buf + offset);
    }
    return size;
}


void MEM_API_ATTR
MEM_API(show_mem_map)(void)
{
    uint32_t offset = 0;
    mem_header_t *head = (mem_header_t *)(g_mem_buf + offset);
    uint32_t index = 0;
    
    mem_buf_init();

    MEM_LOG("\r\n=====memory map info=====\r\n");
    while(offset < MEM_BUF_SIZE) {
        MEM_LOG("index %d: flag: %d, size: [%u]\r\n", index, head->flag, head->size);
        offset += head->size + MEM_HEAD_SIZE;
        head = (mem_header_t *)(g_mem_buf + offset);
        index++;
    }
    MEM_LOG("=====memory map end=====\r\n\r\n");
}


#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
}
#endif

