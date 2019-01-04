#include "common.h"
#include "m_mem.h"
#include "cJSON.h"

void cjson_init(void)
{
    cJSON_Hooks hooks;
    hooks.free_fn = MEM_API(free);
    hooks.malloc_fn = (void *)(MEM_API(malloc));
    cJSON_InitHooks(&hooks);
}

void cjson_mem_test(void)
{
    cJSON *root = cJSON_CreateObject();
    MEM_API(show_mem_map)();
    cJSON_AddItemToObject(root, "item1", cJSON_CreateString("hello world"));
    MEM_API(show_mem_map)();
    cJSON_AddItemToObject(root, "item2", cJSON_CreateNumber(12345));
    MEM_API(show_mem_map)();
    cJSON_AddItemToObject(root, "item3", cJSON_CreateTrue());
    MEM_API(show_mem_map)();
    char *fmt = cJSON_PrintUnformatted(root);
    MEM_API(show_mem_map)();
    MEM_LOG_INFO("json fmt: [%s]\r\n", fmt);
    cJSON_Delete(root);
    MEM_API(show_mem_map)();
    cJSON_free(fmt);
    MEM_API(show_mem_map)();
}

int main(int argc, char *argv[])
{
    MEM_API(show_mem_map)();
    cjson_init();
    cjson_mem_test();
    MEM_API(show_mem_map)();
    return 0;
}

