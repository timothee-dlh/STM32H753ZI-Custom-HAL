#include "stdint.h"
#include "utils.h"

int buffer_len[50] = {0};
int buffer_put_index[50] = {0};
int buffer_get_index[50] = {0};
char buffer[50][200] = {0};


void spin(volatile uint32_t count) 
{
        while (count--) asm("nop");
}

int reg_buf(int buf_num, int len)
{
        if(buf_num > 49){
                return 1;
        }

        buffer_len[buf_num] = len;        
        return 0;
}

int put(int buf_num, char value)
{
        if((buffer_put_index[buf_num] + 1) % buffer_len[buf_num] == buffer_get_index[buf_num]) {
                return 0; // Buffer Full
        }
        buffer[buf_num] [buffer_put_index[buf_num]] = value;
        buffer_put_index[buf_num] = (buffer_put_index[buf_num] + 1) % buffer_len[buf_num];
        
        return 1;
}

int get(int buf_num, char *value)
{
        if(buffer_put_index[buf_num] == buffer_get_index[buf_num]) {
                return 0; // Buffer empty
        }
        *value = buffer[buf_num][buffer_get_index[buf_num]];
        buffer_get_index[buf_num] = (buffer_get_index[buf_num] + 1) % buffer_len[buf_num];
        
        return 1;
}
