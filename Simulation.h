//
// Created by zpl on 2020/12/25.
//

#ifndef BANKSIMULATION_SIMULATION_H
#define BANKSIMULATION_SIMULATION_H
#include<stdio.h>
#include<stdlib.h>
#include "Queue.h"
#include "test_data.h"
#include "board.h"
#include <conio.h>
#include <windows.h>
#include<io.h>
#include "dirent.h"


/*Args:q_num is the num of server
 *     closetime is the duration of Bank
 *     capitial is the start captial
 *     wait is the waiting queue
 *     flag: whether show proceed
 *
*/
void simulation(int q_num,int closetime,int captial,PQueue* wait,int flag)
{


    double time_total = 0;// the sum of all customer waiting time
    double served_num = 0;//the number of people has been served finally
    double  time_serving_time = 0;//the served time totally
    double line_length = 0;// the line length
    int customers_num = QueueLength(*wait);//all customers coming

    PQueue q[q_num];
    for(int i = 0;i<q_num;i++)
    {
        q[i] = (PQueue)malloc(sizeof(Queue));
        InitQueue(q[i]);
    }

    PQueue wait_in_hall = (PQueue)malloc(sizeof(Queue));//the line can't take back money
    InitQueue(wait_in_hall);

    PCustNode p = (*wait)->front->next;
    PCustNode *tool_node;
    int time_now = 0;//the current time


    while(time_now!=closetime)//if time has consumed ,the business will end
    {
        if(flag!=0)//show the process
        {
            system("cls");
            simulation_board(time_now,q,q_num,wait_in_hall);
            //Sleep(0);
        } else
        {
            system("cls");
            printf("Simulating now, please wait for a while(%d/%d)\n",time_now,closetime);
        }


        for(int i = 0;i<q_num;i++) {
            line_length += QueueLength(q[i]);//used for computing avg length
        }
        while(p&&p->arrtime==time_now)
        {

            if (p&&p->arrtime == time_now)//one customer arrives at the Bank
            {
                int min = 1000;
                int min_num = 0;
                for(int i = 0;i<q_num;i++)
                {

                    if(QueueLength(q[i])<min)//find the shortest queue
                    {
                        min = QueueLength(q[i]);
                        min_num = i;
                    }
                }

                EnQueue(&q[min_num],p);
                p = p->next;
            }
        }

        for(int i = 0;i<q_num;i++)//visit all queue to serve
        {
            PCustNode temp = q[i]->front->next;//the serving customer in this queue

            if (temp&&temp->serveStatus==0)// begin serve queue line
            {
                temp->serveStatus =1;
                temp->serveBegin = time_now;
            }

            if(temp&&temp->serveBegin==time_now)
            {
                if (temp->amount>0)//deposit money
                {
                    captial+=temp->amount;
                    //DeQueue(&q[i],tool_node);
                }
                else//take money
                {
                    if(captial>temp->amount)
                    {
                        captial+=temp->amount;
                        //DeQueue(&q[i],tool_node);
                    }
                    else
                    {
                        DeQueue(&q[i],tool_node);
                        temp->serveBegin = 0;
                        EnQueue(&wait_in_hall,temp);//queuing in waiting queue
                    }

                }
            }

            if (temp && (temp->serveBegin+temp->durtime)==time_now)//finish the business
            {
                time_total += temp->serveBegin - temp->arrtime +temp->durtime;
                time_serving_time += temp->durtime;
                served_num++;

                DeQueue(&q[i],tool_node);

                PCustNode temp1 = wait_in_hall->front;
                PCustNode temp2 = wait_in_hall->front->next;


                while (temp2&&temp1)
                {
                    if (temp2->amount<captial)
                    {
                        captial -= temp2->amount;
                        temp1->next = temp2->next;
                        temp2->next = q[i]->front->next;
                        q[i]->front->next = temp2;
                        temp2->serveBegin = time_now;

                    }
                    temp2 = temp2->next;
                    temp1 = temp1->next;
                }
            }

        }
        time_now++;

    }
    //all business has finished


    while(p)//the people still wait in the hall
    {
        int dur = closetime-p->arrtime;
        if(dur>0)
            time_total+= dur;

        p = p->next;
    }
    for(int i = 0;i<q_num;i++)//people wait in the line
    {
        p = q[i]->front->next;
        while(p)
        {
            int dur = closetime-p->arrtime;
            if(dur>0)
                time_total+= dur;

            p = p->next;
        }
    }
    if(served_num==0)
        served_num = 1;
    printf("the average waiting time per customer is %.2f min\n",time_total / customers_num);
    printf("the average serving time per server is %.2f min\n",time_serving_time / q_num);
    printf("the remaining  is %d yuan\n",captial);
    printf("the total of customer is %d \n",customers_num);
    printf("the total of served people is %.f \n",served_num);
    printf("the avg of line length is %.2f \n",line_length/(q_num*closetime));
    system("Pause");




}

#endif //BANKSIMULATION_SIMULATION_H
