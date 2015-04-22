
#ifndef _QUEUE_H_
#define _QUEUE_H_

#ifdef _WIN32
	#include <Windows.h>
#endif
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct mynode{
       struct mynode* next;
       void *elem;
}QueueNode;

typedef struct{
   QueueNode* item;
   size_t elem_size;   //元素大小
   size_t length;  //队列长度
   void (*freefn)(void *); //自定义内存释放函数，释放外部动态申请的内存
}Queue;

#ifdef _cplusplus
extern "C"
{
#endif
void queue_init(Queue *s,size_t size, void (*freefn)(void*));
int queue_is_empty(Queue *q);
int queue_length(Queue *q);
void* queue_front(Queue *q);
void* queue_last(Queue *q);
void queue_pop(Queue *q);
void queue_push(Queue *q,void *value);
void queue_free(Queue *q);
long queue_to_buffer(Queue *q,void *buffer);
long queue_byte_length(Queue *q);
#ifdef _cplusplus
}
#endif



#endif