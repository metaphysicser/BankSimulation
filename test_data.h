//
// Created by 86199 on 2020/12/11.
//

#ifndef BANKSIMULATION_TEST_DATA_H
#define BANKSIMULATION_TEST_DATA_H

#include<stdio.h>
#include<stdlib.h>
#include "string.h"
#include "Queue.h"
#include <time.h>
#include <math.h>

#define PI 3.141592654

//read the txt to create queue
PQueue read_txt(char path[])
{
    FILE *fp;
    fp = fopen(path,"r");//open the file

    int last_arrive = 0;

    PQueue L1 = (PQueue)malloc(sizeof(Queue));
    InitQueue(L1);


    if(fp==NULL)
    {
        printf("fail to open file");
        printf("\n");
        return NULL;
    }


    char szTest[20] = {0};
    while(!feof(fp))

    {

        memset(szTest,0, sizeof(szTest));

        fgets(szTest,sizeof(szTest) - 1, fp); // get the content

        int index1=0,index2=0,index3 = 0;// the location of space

        for(int i = 0;i<sizeof(szTest);i++)
        {
            if ((szTest[i]=='\n' || szTest[i] == '\000') && index3 == 0)
                index3=i;
            if(szTest[i]==' ')
                if(!index1)
                    index1 = i;
                else if(!index2){
                    index2 = i;

                }
                else{
                    index3 = i;
                    break;
                }
        }
        if (szTest[0] == '\n' || szTest[0] == ' ')
            continue;

        if (index1 == index2 || (index1 ==1 && index2==0))
            break;

        // split the string
        char arrtime[index1];
        strncpy(arrtime,szTest,index1);



        char durtime[index2-index1-1];
        strncpy(durtime,szTest+index1+1,index2-index1-1);

        char amount[index3-index2-1];
        strncpy(amount,szTest+index2+1,index3-index2-1);

        //transform into int
        int arrtime_int;
        arrtime_int = atoi(arrtime);
        int durtime_int;
        durtime_int = atoi(durtime);
        int amount_int;
        amount_int = atoi(amount);

        if(arrtime_int<last_arrive)
        {
            printf("the sequence of the data has problem\n");
            return NULL;
        } else
            last_arrive = arrtime_int;



        CustNode now = {arrtime_int,durtime_int,amount_int,0,0,NULL };
        PCustNode p_now = &now;
        EnQueue(&L1,p_now);
    }

    fclose(fp);//close the file
    return L1;


}

// generate the test data
// total_num: the number of the customer
// path : save path
// closingtime: the bank closing time
// durtime_bound[]: it includes two num of during time, first is downbound and the other is upbound
// amount_bound[]: it includes two num of amount, first is downbound and the other is upbound
// mode:1. evenly distribution 2.Gassion distribution 3.Poisson distribution 4. Random distribution
void generate_data(char path[],int total_num,int closingtime,int durtime_bound[],
                   int amount_bound[],int mode[])
{
    // check the input whether is valid
    if (durtime_bound[0]>=durtime_bound[1]|| amount_bound[0]>=amount_bound[1])
    {
        printf("There is some problem with the params\n");
        return;
    }
    if (mode[0]<1 || mode[0]>3||mode[1]<1 || mode[1]>3||mode[2]<1 || mode[2]>3)
    {
        printf("There is some problem with the params\n");
        return;
    }

    FILE *file;
    file = fopen(path,"w+");
    srand((unsigned)time(NULL));
    static double U, V;
    static int phase = 0;
    double z;

    int arr[total_num];
    int last = 0;

    for(int i = 0;i<total_num;i++)
    {
        int Lambda = closingtime / total_num;
        int  k = 0;
        long double p = 1.0;
        long double l = exp(-Lambda);

        //printf("%1.5Lf\n", l);
        while(p>=l)
        {
            double u = (float)(rand() %100)/100;
            p *= u;
            k++;
        }
        last += k-1;
        arr[i] = last;
    }

    for(int j=0;j<9;j++)//sort the data
        for(int i=0;i<9-j;i++)
            if(arr[i]>arr[i+1])
            {int t=arr[i];arr[i]=arr[i+1];arr[i+1]=t;}


    for(int i = 0;i<total_num;i++)
    {
        if(mode[0]==1)
        {
            int arrtime = closingtime/total_num*i;
            char arr_str[10];
            itoa(arrtime,arr_str,10);
            fputs(arr_str,file);
            fputs(" ",file);

        }
        else if (mode[0]==2)
        {

            char arr_str[10];
            itoa(arr[i],arr_str,10);
            fputs(arr_str,file);
            fputs(" ",file);
        }

     if(mode[1]==1)
        {
            int x;
            x =durtime_bound[0] + (rand()%(durtime_bound[1]-durtime_bound[0]));
            char dur_str[10];

            itoa(x,dur_str,10);
            fputs(dur_str,file);
            fputs(" ",file);

        }
        else if(mode[1]==2)
        {
            if(phase == 0){
                U = rand() / (RAND_MAX + 1.0);
                V = rand() / (RAND_MAX + 1.0);
                z = sqrt(-2.0 * log(U))* sin(2.0 * PI * V);
                }
            else{
                z = sqrt(-2.0 * log(U)) * cos(2.0 * PI * V);
                }
            phase = 1 - phase;

            int av = (durtime_bound[0]+durtime_bound[1])/2;
            int x = av+ z*av*1/2;

            char dur_str[10];
            if(x<=0)
                x = 1;

            itoa(x,dur_str,10);
            fputs(dur_str,file);
            fputs(" ",file);
        }

        if(mode[2]==1)
        {
            int x;
            x =amount_bound[0] + (rand()%(amount_bound[1]-amount_bound[0]));
            char amount_str[10];

            itoa(x,amount_str,10);
            fputs(amount_str,file);
            fputs("\n",file);

        }
        else if(mode[2]==2)
        {
            if(phase == 0){
                U = rand() / (RAND_MAX + 1.0);
                V = rand() / (RAND_MAX + 1.0);
                z = sqrt(-2.0 * log(U))* sin(2.0 * PI * V);
            }
            else{
                z = sqrt(-2.0 * log(U)) * cos(2.0 * PI * V);
            }
            phase = 1 - phase;

            int av = (amount_bound[0]+amount_bound[1])/2;
            int x = av+ z*av*1/2;

            char dur_str[10];

            itoa(x,dur_str,10);
            fputs(dur_str,file);
            fputs(" ",file);
            fputs("\n",file);
        }





    }
    fclose(file);
    return;


}

#endif //BANKSIMULATION_TEST_DATA_H
