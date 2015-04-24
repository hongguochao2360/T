
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
   size_t elem_size;   //Ԫ�ش�С
   size_t length;  //���г���
   void (*freefn)(void *); //�Զ����ڴ��ͷź������ͷ��ⲿ��̬������ڴ�
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