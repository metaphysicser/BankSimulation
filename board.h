//
// Created by 86199 on 2020/12/18.
//

#ifndef BANKSIMULATION_BOARD_H
#define BANKSIMULATION_BOARD_H

#include<stdio.h>
#include<stdlib.h>
#include "Queue.h"

// show the initilization board
void init_board()
{
    system("color E");
    printf("\n\n\n\n");
    printf("                              ======================================================================\n");
    printf("                              ||                                                                  ||\n");
    printf("                              ||                 the Simulation of Bank Business                  ||\n");
    printf("                              ||__________________________________________________________________||\n");
    printf("                              ||                                                                  ||\n");
    printf("                              ||              1. select the existing data and param               ||\n");
    printf("                              ||              2. customize the data and param                     ||\n");
    printf("                              ||              3. exit the program                                 ||\n");
    printf("                              ||                                                                  ||\n");
    printf("                              ||__________________________________________________________________||\n");
}

void simulation_board(int time_mow,PQueue *q,int q_num,PQueue wait)
{

    printf("                                                ================                                      \n");
    printf("                                       =================================                              \n");
    printf("                             ==================================================                       \n");
    printf("                     ====================================================================             \n");
    printf("                                                 Current Time:%d                                      \n",time_mow);
    printf("                      server                        client                                            \n");

    for(int i = 0;i<q_num;i++)
    {
        int temp = QueueLength(q[i]);
        printf("                    | [||] ");
        for(int j = 0;j<temp;j++)
        {
            printf("*");
        }
        printf("\n");
    }
    printf("\n");
    printf("                       waiting hall:\n");
    printf("                     ");
    for(int i = 0;i<QueueLength(wait);i++)
    {
        printf("*");
    }
    printf("\n                     ====================================================================             \n");


}

#endif //BANKSIMULATION_BOARD_H
