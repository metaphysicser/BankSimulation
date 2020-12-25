/*
* Program:the Simulation of Bank Business
* Author:Zhang Pinglu
* Date:2020.12.8
* Environment: Clion
*/

//This file define the struture of the Node,representing the customer in Bank Business
//the time unit is a minute
//the money unit is yuan

#include<stdio.h>
#include<stdlib.h>
#include "Queue.h"
#include "test_data.h"
#include "board.h"
#include<io.h>
#include "dirent.h"
#include "Simulation.h"

//the access to the program
void main_program()
{
          while(1)
     {
         init_board();//show the menu board

         int a = 0;//receive the selection of user
         printf("which function do you wannan carry out?\n");
         scanf("%d",&a);

         if(a==3)//exit the program
         {
             printf("Goodbye!");
             exit(0);
         }
         else if(a==2)// generate the data self
         {
             int type = 0;//judge the validity of input
             int mode[3];// the mode of generating data

             int total_num = 0;//the customer number
             printf("please input the number of the total customers\n");
             type = scanf("%d",&total_num);
             fflush(stdin);

             if(total_num<0 || !type)//check the validity
             {
                 printf("some wrong with your input,please input positive number\n");
                 system("Pause");
                 system("cls");
                 continue;
             }


             int closing_time = 0;//the lasting time of bank
             printf("please input the lasting time of bank\n");
             type = scanf("%d",&closing_time);
             fflush(stdin);
             if(closing_time<0 || !type)//check the validity
             {
                 printf("some wrong with your input,please input positive number\n");
                 system("Pause");
                 system("cls");
                 continue;
             }


             printf("which mode do you want to generate line data\n1.Evenly distribution\n2.Poisson distribution\n");
             type = scanf("%d",&mode[0]);
             fflush(stdin);
             if(mode[0]<0 || mode[0]>2 || !type)
             {
                 printf("some wrong with your input,please input 1 or 0\n");
                 system("Pause");
                 system("cls");
                 continue;
             }


             int during_bound[2];// the bound of during time in dealing with business
             printf("please input the down board of every customers' during time\n");
             type = scanf("%d",&during_bound[0]);
             fflush(stdin);
             if(during_bound[0]<0 || !type)//check the validity
             {
                 printf("some wrong with your input.\n");
                 system("Pause");
                 system("cls");
                 continue;
             }
             printf("please input the upper board of every customers' during time\n");
             type = scanf("%d",&during_bound[1]);
             fflush(stdin);
             if(during_bound[1]<0 || !type)
             {
                 printf("some wrong with your input.\n");
                 system("Pause");
                 system("cls");
                 continue;
             }



             printf("which mode do you want to generate during time\n1.Random distribution\n2.Gaussian distribution\n");
             type = scanf("%d",&mode[1]);
             fflush(stdin);
             if(mode[1]<0|| mode[1]>2 || !type)
             {
                 printf("some wrong with your input.\n");
                 system("Pause");
                 system("cls");
                 continue;
             }




             int amount_bound[2];
             printf("please input the down board of every customers' business amount\n");
             type = scanf("%d",&amount_bound[0]);
             fflush(stdin);
             if(!type)
             {
                 printf("some wrong with your input.\n");
                 system("Pause");
                 system("cls");
                 continue;
             }
             printf("please input the upper board of every customers' business amount\n");
             type = scanf("%d",&amount_bound[1]);
             fflush(stdin);
             if(!type)
             {
                 printf("some wrong with your input.\n");
                 system("Pause");
                 system("cls");
                 continue;
             }




             printf("which mode do you want to generate business amount\n1.Random distribution\n2.Gaussian distribution\n");
             type = scanf("%d",&mode[2]);
             fflush(stdin);
             if(mode[2]<0|| mode[2]>2 || !type)
             {
                 printf("some wrong with your input.\n");
                 system("Pause");
                 system("cls");
                 continue;
             }


             int q_num = 0;// the number of line
             printf("How many servers do you want?\n");
             type = scanf("%d",&q_num);
             fflush(stdin);
             if(q_num <0 || !type)
             {
                 printf("some wrong with your input.\n");
                 system("Pause");
                 system("cls");
                 continue;
             }

             int saving = 0;// the initial capitial of bank
             printf("How much savings do initial bank have?\n");
             type = scanf("%d",&saving);
             fflush(stdin);
             if(!type)
             {
                 printf("some wrong with your input.\n");
                 system("Pause");
                 system("cls");
                 continue;
             }



             int flag;//whether show the process
             printf("Do you want to show the process?\nif you want,please input 1, or input 0\n");
             type = scanf("%d",&flag);
             fflush(stdin);
             if(flag<0|| flag>1 || !type)
             {
                 printf("some wrong with your input.\n");
                 system("Pause");
                 continue;
             }

             generate_data("../test_data/current.txt",total_num,closing_time,during_bound,amount_bound,mode);//generate the data
             PQueue L1 = read_txt("../test_data/current.txt");
             if(L1)
             {
                 simulation(q_num,closing_time,saving,&L1,flag);//simulate
             }

         }
         else if(a==1)
         {
             //show the dir of test_data file
             int i = 0;
             DIR *dir = NULL;
             struct dirent *entry;

             if((dir = opendir("../test_data/"))==NULL)
             {
                 printf("opendir failed!");

             }
             else
             {
                 while(entry=readdir(dir))
                 {
                     i++;
                     if(i != 1&& i != 2)
                       printf("filename%d = %s\n",i-2,entry->d_name);  //输出文件或者目录的名称

                 }
                 closedir(dir);


                 printf("tips:\n1.test1 has the data of high people density\n2.test2 has the data of low density\n3.the lasting time is defined as 600 min and captial is 10000 yuan\n");
                 printf("\nplease select a txt file as simulation data\n");


                 char s[10];//the file selected
                 scanf("%s",s);
                 fflush(stdin);
                 char file[] = "../test_data/";
                 strcat(file,s);

                 int type  = 0;//the number of receiving value sucessfully
                 int flag = 0;
                 printf("Do you want to show the process?\nif you want,please input 1, or input 0\n");
                 type = scanf("%d",&flag);
                 fflush(stdin);
                 if(flag < 0||flag>1|| !type)
                 {
                     printf("some wrong with your input.\n");
                     system("Pause");
                     system("cls");
                     continue;
                 }



                 int q_num = 0;//the line number
                 printf("how many servers do you want?\n");
                 type = scanf("%d",&q_num);
                 fflush(stdin);
                 if(q_num < 0|| !type)
                 {
                     printf("some wrong with your input.\n");
                     system("Pause");
                     system("cls");
                     continue;
                 }


                 PQueue L1 = read_txt(file);//get the data placed before
                 if(L1)
                 {

                     simulation(q_num,600,1000,&L1,flag);

                 }
                 system("pause");
             }
         }
         else//the param is wrong
         {

             printf("sorry,there is some wrong with your input");
             system("pause");
         }
         fflush(stdin);
         system("cls");
     }
}

int main() {
      main_program();
      return 0;
}