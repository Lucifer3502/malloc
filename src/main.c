#include "common.h"
#include "m_mem.h"


int main(int argc, char *argv[])
{
    MEM_API(show_mem_map)();
    
    void *p1 = MEM_API(malloc)(1024);
    //MEM_LOG_INFO("free size = %u\r\n", MEM_API(get_free_heap_size)());
    MEM_API(show_mem_map)();

    MEM_API(free)(p1);
    //MEM_LOG_INFO("free size = %u\r\n", MEM_API(get_free_heap_size)());
    MEM_API(show_mem_map)();
    
 #if 1
    void *p2 = MEM_API(malloc)(500);
    //MEM_LOG_INFO("free size = %u\r\n", MEM_API(get_free_heap_size)());
    MEM_API(show_mem_map)();
    
    void *p3 = MEM_API(malloc)(2000);
    //MEM_LOG_INFO("free size = %u\r\n", MEM_API(get_free_heap_size)());
    MEM_API(show_mem_map)();
    
    MEM_API(free)(p1);
    //MEM_LOG_INFO("free size = %u\r\n", MEM_API(get_free_heap_size)());
    MEM_API(show_mem_map)();

    MEM_API(free)(p3);
    //MEM_LOG_INFO("free size = %u\r\n", MEM_API(get_free_heap_size)());
    MEM_API(show_mem_map)();

    MEM_API(free)(p2);
    //MEM_LOG_INFO("free size = %u\r\n", MEM_API(get_free_heap_size)());
    MEM_API(show_mem_map)();
#endif
    return 0;
}

