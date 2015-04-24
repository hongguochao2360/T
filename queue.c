#include "../include/queue.h"




//初始化队列
void queue_init(Queue *s,size_t size, void (*freefn)(void*)){
   s->item = NULL;
   s->elem_size = size;
   s->length = 0;
   s->freefn = freefn;
}

//判断队列为空
int queue_is_empty(Queue *q){
   return q->length==0;
}

//求队列长度
int queue_length(Queue *q){
   return q->length;
}

//获得队列头部元素
void* queue_front(Queue *q){
   QueueNode *n = q->item;
   return (n!=NULL ? n->elem : NULL);
}

//获得队列尾部元素
void* queue_last(Queue *q){
   QueueNode *n = q->item;
   while(n->next!=NULL){
       n = n->next;
   }
   return (n!=NULL ? n->elem : NULL);
}

//弹出（删除）队列头部元素
void queue_pop(Queue *q){
   QueueNode *n = q->item;
   QueueNode *temp;
   if(n==NULL){
       return;
   }
   temp = n->next;

   if(q->freefn!=NULL){
       q->freefn(n->elem);     //释放函数外面动态分配的内存
   }
   free(n->elem);  //释放元素空间
   free(n);        //释放节点空间
   q->length--;    //队列长度减1
   q->item = temp;
}

//元素入队列尾部
void queue_push(Queue *q,void *value){
   QueueNode *n,*nn;
   n = q->item;
   while(n!=NULL && n->next!=NULL){
       n = n->next;
   }
   nn = (QueueNode*)malloc(sizeof(QueueNode));
   nn->next = NULL;
   nn->elem = malloc(q->elem_size);    //为元素申请空间
   memcpy(nn->elem, value, q->elem_size);
   if(q->item==NULL){
       q->item = nn;
   }
   else{
       n->next = nn;
   }
   q->length++;
}

//删除队列
void queue_free(Queue *q){
   QueueNode *n=q->item;
   QueueNode *temp;
   //释放节点n
   while(n!=NULL){
       temp = n->next;
       if(q->freefn!=NULL){
           q->freefn(n->elem);     //释放函数外面动态分配的内存
       }
       free(n->elem);
       free(n);
       n = temp;
   }
   q = NULL;
}

//返回queue 到buffer 的字节数 
//而且queue_length在使用完之后的长度是0
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
   Queue dq;   //double类型队列
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

   Queue cq1;  //字符串类型的队列，字符串不动态分配
   char *s[] = {"John","Smith","Green"};
   initQueue(&cq1, sizeof(char*), NULL);
   pushQueue(&cq1, &s[0]);
   pushQueue(&cq1, &s[1]);
   pushQueue(&cq1, &s[2]);
   printf("front:%s\tback:%s\n", *(char**)frontQueue(&cq1) ,*(char**)backQueue(&cq1));
   popQueue(&cq1);
   printf("front:%s\tback:%s\n\n", *(char**)frontQueue(&cq1) ,*(char**)backQueue(&cq1));
   destoryQueue(&cq1);

   Queue cq2;  //字符串类型队列，动态分配字串内存，这个需要自定义释放函数
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
