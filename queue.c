#include "../include/queue.h"




//��ʼ������
void queue_init(Queue *s,size_t size, void (*freefn)(void*)){
   s->item = NULL;
   s->elem_size = size;
   s->length = 0;
   s->freefn = freefn;
}

//�ж϶���Ϊ��
int queue_is_empty(Queue *q){
   return q->length==0;
}

//����г���
int queue_length(Queue *q){
   return q->length;
}

//��ö���ͷ��Ԫ��
void* queue_front(Queue *q){
   QueueNode *n = q->item;
   return (n!=NULL ? n->elem : NULL);
}

//��ö���β��Ԫ��
void* queue_last(Queue *q){
   QueueNode *n = q->item;
   while(n->next!=NULL){
       n = n->next;
   }
   return (n!=NULL ? n->elem : NULL);
}

//������ɾ��������ͷ��Ԫ��
void queue_pop(Queue *q){
   QueueNode *n = q->item;
   QueueNode *temp;
   if(n==NULL){
       return;
   }
   temp = n->next;

   if(q->freefn!=NULL){
       q->freefn(n->elem);     //�ͷź������涯̬������ڴ�
   }
   free(n->elem);  //�ͷ�Ԫ�ؿռ�
   free(n);        //�ͷŽڵ�ռ�
   q->length--;    //���г��ȼ�1
   q->item = temp;
}

//Ԫ�������β��
void queue_push(Queue *q,void *value){
   QueueNode *n,*nn;
   n = q->item;
   while(n!=NULL && n->next!=NULL){
       n = n->next;
   }
   nn = (QueueNode*)malloc(sizeof(QueueNode));
   nn->next = NULL;
   nn->elem = malloc(q->elem_size);    //ΪԪ������ռ�
   memcpy(nn->elem, value, q->elem_size);
   if(q->item==NULL){
       q->item = nn;
   }
   else{
       n->next = nn;
   }
   q->length++;
}

//ɾ������
void queue_free(Queue *q){
   QueueNode *n=q->item;
   QueueNode *temp;
   //�ͷŽڵ�n
   while(n!=NULL){
       temp = n->next;
       if(q->freefn!=NULL){
           q->freefn(n->elem);     //�ͷź������涯̬������ڴ�
       }
       free(n->elem);
       free(n);
       n = temp;
   }
   q = NULL;
}

//����queue ��buffer ���ֽ��� 
//����queue_length��ʹ����֮��ĳ�����0
long queue_to_buffer(Queue *q,void *buffer){
	long count = 0;
	unsigned char *tmp_buffer = (unsigned char*)buffer;
	while(!queue_is_empty(q)){
		memcpy(tmp_buffer,q->item->elem,q->elem_size);
		queue_pop(q);
		tmp_buffer = tmp_buffer + q->elem_size;
		count += q->elem_size;
	}
	return count;
}

long queue_byte_length(Queue *q){
	return q->elem_size * q->length;
}

/*
int main()
{
   Queue dq;   //double���Ͷ���
   double f;
   initQueue(&dq,sizeof(double), NULL);

   f = 21.3;
   pushQueue(&dq, &f);
   f = 32.5;
   pushQueue(&dq, &f);
   f = 49.8;
   pushQueue(&dq, &f);
   printf("size:%d\n",sizeQueue(&dq));

   printf("front:%f\tback:%f\n", *(double*)frontQueue(&dq) ,*(double*)backQueue(&dq));

   popQueue(&dq);
   printf("front:%f\tback:%f\n", *(double*)frontQueue(&dq) ,*(double*)backQueue(&dq));
   printf("size:%d\n",sizeQueue(&dq));

   popQueue(&dq);
   printf("size:%d\n\n",sizeQueue(&dq));
   destoryQueue(&dq);

   Queue cq1;  //�ַ������͵Ķ��У��ַ�������̬����
   char *s[] = {"John","Smith","Green"};
   initQueue(&cq1, sizeof(char*), NULL);
   pushQueue(&cq1, &s[0]);
   pushQueue(&cq1, &s[1]);
   pushQueue(&cq1, &s[2]);
   printf("front:%s\tback:%s\n", *(char**)frontQueue(&cq1) ,*(char**)backQueue(&cq1));
   popQueue(&cq1);
   printf("front:%s\tback:%s\n\n", *(char**)frontQueue(&cq1) ,*(char**)backQueue(&cq1));
   destoryQueue(&cq1);

   Queue cq2;  //�ַ������Ͷ��У���̬�����ִ��ڴ棬�����Ҫ�Զ����ͷź���
   char *ds;
   initQueue(&cq2, sizeof(char*), charfree);
   ds = strdup("Lucy");
   pushQueue(&cq2, &ds);
   ds = strdup("Tim");
   pushQueue(&cq2, &ds);
   ds = strdup("Ball");
   pushQueue(&cq2, &ds);
   printf("front:%s\tback:%s\n", *(char**)frontQueue(&cq2) ,*(char**)backQueue(&cq2));
   popQueue(&cq2);
   printf("front:%s\tback:%s\n\n", *(char**)frontQueue(&cq2) ,*(char**)backQueue(&cq2));
   destoryQueue(&cq2);

   return 0;
}
*/
