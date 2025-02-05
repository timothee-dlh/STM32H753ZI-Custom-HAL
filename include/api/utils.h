#ifndef UTILS_H
#define UTILS_H

#define SHIFT(x) (1UL << x)

#define FREQ 65000000L

void spin(volatile uint32_t count);

int reg_buf(int buf_num, int len);
int put(int buf_num, char value);
int get(int buf_num, char *value);

#endif
