/* FIFOライブラリ */

#include "bootpack.h"

#define FLAGS_OVERRUN		0x0001

void fifo32_init(struct FIFO32 *fifo, int size, int *buf)
/* FIFO初始化 */
{
	fifo->size = size;
	fifo->buf = buf;
	fifo->free = size; /* 缓冲区大小 */
	fifo->flags = 0;
	fifo->p = 0; /* 下一个数据写入的位置 */
	fifo->q = 0; /* 下一个数据?出的位置 */
	return;
}

int fifo32_put(struct FIFO32 *fifo, int data)
/* 向FIFO??数据并保存 */
{
	if (fifo->free == 0) {
		/* 溢出 */
		fifo->flags |= FLAGS_OVERRUN;
		return -1;
	}
	fifo->buf[fifo->p] = data;
	fifo->p++;
	if (fifo->p == fifo->size) {
		fifo->p = 0;
	}
	fifo->free--;
	return 0;
}

int fifo32_get(struct FIFO32 *fifo)
/* 从FIFO取一个数据*/
{
	int data;
	if (fifo->free == fifo->size) {
		/* 若缓冲区为空，返回-1 */
		return -1;
	}
	data = fifo->buf[fifo->q];
	fifo->q++;
	if (fifo->q == fifo->size) {
		fifo->q = 0;
	}
	fifo->free++;
	return data;
}

int fifo32_status(struct FIFO32 *fifo)
/* 返回存储的数据个数 */
{
	return fifo->size - fifo->free;
}
