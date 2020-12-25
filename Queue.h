#pragma once
/*
* Program:the Simulation of Bank Business
* Author:Zhang Pinglu
* Date:2020.12.8
* Environment: Vistual Studio 2019
*/
#ifndef _QUEUE_H_
#define _QUEUE_H_

//this head file define a queue structure

#define OK     1
#define ERROR  0
#define OVERFLOW -1


#include<stdio.h>
#include<stdlib.h>

typedef int Status;

typedef struct CustNode
{
    int arrtime;//arriving time
    int durtime;//during time
    int amount;//the money ammount,the postive num represent depositing and negative num represents taking.
    int serveBegin;

    int serveStatus;
    struct CustNode* next;//storing next Node
}CustNode, * PCustNode;


typedef struct Queue
{
    PCustNode front;            //the quene head
    PCustNode rear;             //the quene tail
}Queue, * PQueue;



//Init a empty queue
Status InitQueue(PQueue Q)
{
    Q->front = Q->rear = (PCustNode)malloc(sizeof(CustNode));//apply for space
    if (!Q->front) exit(OVERFLOW);
    Q->front->next = NULL;
    return OK;
}

//Destroy a Queue
Status DestroyQueue(PQueue *Q)
{
    while ((*Q)->front)
    {
        (*Q)->rear = (*Q)->front->next;
        free((*Q)->front);
        (*Q)->front = (*Q)->rear;
    }
    return OK;
}


//add a new node in queue,with a PCustNode as input
Status EnQueue(PQueue *Q, PCustNode e)
{
    PCustNode p = (PCustNode)malloc(sizeof(CustNode));
    p->arrtime = e->arrtime;
    p->durtime = e->durtime;
    p->serveBegin = e->serveBegin;
    p->amount = e->amount;
    p->serveStatus = e->serveStatus;
    p->next = e->next;
    if (!e)  exit(OVERFLOW);
    p->next = NULL;
    (*Q)->rear->next = p;
    (*Q)->rear = p;
    return OK;

}

//pop a node,with a PCustNode as output
Status DeQueue(PQueue *Q, PCustNode *e)
{

    if ((*Q)->front == (*Q)->rear) return ERROR;
    //(*e) = (*Q)->front->next;
    PCustNode p = (*Q)->front->next;
    (*Q)->front->next = p->next;
    if ((*Q)->rear == p) (*Q)->rear = (*Q)->front;
    //free(p);
    return OK;
}

//get the length of queue
int QueueLength(PQueue Q)
{
    PCustNode p;
    int length=0;
    if(Q->front==Q->rear)
        return 0;
    else
    {
        p=Q->front->next;
        while(p)
        {
            length++;
            p=p->next;
        }
    }
    return length;
}


#endif