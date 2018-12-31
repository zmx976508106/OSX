#include <mm/mm_test.h>

pid_t pid = 0;
int alloc_size[TEST_COUNT] = {33, 64, 128, 256, 512, 1024, 2048, 4096, 6144};
// 0x80022000


int test_alloc_memory(){
    int *addr_alloc[TEST_COUNT] = {NULL};
    int addr_true_int[TEST_COUNT] = {0x80022ec0, 0x80022e80, 0x80022c80, 0x80022800, 0x80022400, 0x80022000, 0x80023000, 0x80024000, 0x80025000};
    int *addr_true[TEST_COUNT];
    
    int i;
    for(i = 0; i < TEST_COUNT; ++i)
        addr_true[i] = (int *)(addr_true_int[i] - 0x80000000);
    for (i = 0; i < TEST_COUNT; ++i){
        // writeValTo7SegsDec(i);
        addr_alloc[i] = (int *)kmalloc(pid, alloc_size[i]);
        if(get_page_status((uint32_t)addr_alloc[i]) != 1){
            // 错误类型一
            // 页面在分配之后未修改标志位
            writeValTo7SegsHex(0xffffffff);
            return 1000;
        }

        if(addr_alloc[i] != addr_true[i]){
            // 错误类型二
            // 页面分配得到的地址不正确
            // pte_t *pte = get_pte_by_page_addr(0x00022000);
            // uint32_t high = (uint32_t)((*pte) >> 32);
            // writeValTo7SegsHex(high);

            writeValTo7SegsHex(0xfffffff0);
            writeValTo7SegsDec(i);
            writeValTo7SegsHex(addr_alloc[i]);
            return 2000;
        }
            
    }
    return 3000;
}

int test_rw_memory(){
    int *addr = (int *)kmalloc(0, 32);
    *addr = 2048;
    writeValTo7SegsDec(*addr);
    return 1;
}

int test_free_memory(){
    return 1;
}