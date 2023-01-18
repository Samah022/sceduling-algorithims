#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#define MAX_PROCESS 50

/*

Project for CS221- Fundamentals of Operating System.

Supervised by: Dr. Fazilah Haron and Ms. Amal Albalawi.

Group Members: Abeer Jelani, Salwa Shama, Samah Shama, Shatha Faraj, and Leen Khalil.



Description: This is sourse code for implemention of 4 algorithms which are FCFS, RR, 2 multilevel scheduling:

RR & FCFS, and 3 multilevel scheduling: RR1,RR2,& FCFS.



*/

/* -------------------------------------------Defined Structs-------------------------------------------*/

typedef struct
{

    int arriv;

    int burst;

    int start_t;

    int end_t;

    int wait_t;

    int turnaround_t;

    int remaining_t;

    int complete_t;

} proc;

proc p[MAX_PROCESS], Q1[MAX_PROCESS], Q2[MAX_PROCESS], Q3[MAX_PROCESS]; // Three queues

typedef struct
{

    int arriv;

    int burst;

    int wait_t;

    int turnaround_t;

    int remaining_t;

    int complete_t, pointer;

} process;

process Q11[10], Q22[10]; // Two queues

/* -------------------------------------------Defined Variables-------------------------------------------*/

int i; // counter in loop

int j; // counter2 in loop

int s; // use to read from file

int k = 0; // number of process in Q2

int r = 0; // number of process in Q3

int quant; // quantum time in RR

int quant1; // quantum time for the first queue in MLQ

int quant2; // quantum time for the second queue in MLQ

// variables for calculate average for the algorithms

int sum = 0;

int wt = 0, tat = 0;

float avg_wt, avg_tat;

int flag = 0; // to handle errors

int time = 0; // from arrival time of first process to completion of last executed process

int reccount = 0; // use to read from file

int num_process = 0;

// variables for RR algorithms

int temp[MAX_PROCESS];

int counter = 0;

int y;

// NOTE: these variables to handle integration issue for 2 multilevel scheduling :(

int i1 = 0; // counter in loop

int j_1 = 0; // counter2 in loop

int s1 = 0; // counter in do while, the number of completed processes

int r1 = 0; // number of process in Q1 that are already executed

int k1 = 0; // number of process in q2

int m1 = 0; // number of process in Q2 that are already executed

int quant1 = 2; // quantum time for the first queue in MLQ

int flag1 = 0; // flow of countrol of

int time1 = 0; // from arrival time of first process to completion of last executed process

int num_process1 = 0;

// creating file pointer to work with files

FILE *fh;

/* -------------------------------------------Defined Methods-------------------------------------------*/

/* -----------------------sortByArrival_priority------------------------------*/

void sortByArrival_priority()

{

    proc temp1;

    for (i = 0; i < num_process; i++)

    {

        for (j = i + 1; j < num_process; j++)

        {

            if (Q1[i].arriv > Q1[j].arriv)

            {

                temp1 = Q1[i];

                Q1[i] = Q1[j];

                Q1[j] = temp1;
            }
        }
    }

    /*

    for(i=0;i<num_process;i++)

        {

            for(j=i+1;j<num_process;j++)

                {

                    if(Q1[i].arriv==Q1[j].arriv)

                        {

                    if(Q1[i].burst > Q1[j].burst)

                    {

                    temp1=Q1[i];

                                Q1[i]=Q1[j];

                                Q1[j]=temp1;

                }

                        }

                }

        }

    */
}

/* -----------------------sortByArrival_priority------------------------------*/

void sortByArrival_priority1()
{

    proc temp1;

    int i, j;

    for (i = 0; i < num_process; i++)
    {

        for (j = i + 1; j < num_process; j++)
        {

            if (p[i].arriv > p[j].arriv)
            {

                temp1 = p[i];

                p[i] = p[j];

                p[j] = temp1;

                // temp[i]= p[i].burst;
            }
        }
    }

    /*    for(i=0;i<num_process;i++)

       {

           for(j=i+1;j<num_process;j++)

               {

                   if(p[i].arriv==p[j].arriv)

                       {

                   if(p[i].burst > p[j].burst)

                   {

                   temp1=p[i];

                               p[i]=p[j];

                               p[j]=temp1;

                               temp[i]= p[i].burst;

               }

                       }

               }

       }*/

    temp[num_process - 1] = p[num_process - 1].burst;
}

/* -----------------------sortByArrival_priority------------------------------*/

void sortByArrival_priority2()
{

    process temp11;

    int i1, j_1;

    for (i1 = 0; i1 < num_process1; i1++)
    {

        for (j_1 = i1 + 1; j_1 < num_process1; j_1++)
        {

            if (Q11[i1].arriv > Q11[j_1].arriv)
            {

                temp11 = Q11[i1];

                Q11[i1] = Q11[j_1];

                Q11[j_1] = temp11;
            }
        }
    }

    /*

    for(i1=0;i1<num_process1;i1++)

    {

        for(j_1=i+1;j_1<num_process;j_1++)

            {

                if(Q11[i1].arriv==Q11[j_1].arriv)

                    {

                if(Q11[i1].burst > Q11[j_1].burst)

                {

                temp11=Q11[i1];

                            Q11[i1]=Q11[j_1];

                            Q11[j_1]=temp11;

            }

                    }

            }

    }

    */
}

/* --------------------------------------------------------------------------------------------------*/

/* -------------------------------------------FCFS Methods-------------------------------------------*/

/* --------------------------------------------------------------------------------------------------*/

/* -----------------------calc_StartEndTime-----------------------------*/

void calc_StartEndTime(proc p[])
{

    for (int i = 0; i < num_process; i++)
    {

        if (i == 0)
        {

            p[0].start_t = 0;

            p[0].end_t = p[0].burst;
        }
        else
        {

            p[i].start_t = p[i - 1].end_t;

            p[i].end_t = p[i - 1].end_t + p[i].burst;
        }
    }
}

/*-------------------------calc_Time-------------------------------------*/

void calc_Time(proc p[])
{

    printf("\nProcess No \t\t Burst Time \t\t Turnaround Time \t\t Waiting Time ");

    for (int i = 0; i < num_process; i++)
    {

        if (i == 0)
        {

            p[0].wait_t = 0;

            p[0].turnaround_t = p[0].burst;
        }
        else
        {

            p[i].wait_t = p[i].start_t - p[i].arriv;

            p[i].turnaround_t = p[i].end_t - p[i].arriv;
        }
    }

    for (int i = 0; i < num_process; i++)
    {

        printf("\nProcess No[%d] \t\t %d\t\t\t\t %d\t\t\t %d", i + 1, p[i].burst, p[i].turnaround_t, p[i].wait_t);
    }
}

/*-------------------------------calc_AvgTime_FCFS-----------------------*/

void calc_AvgTime_FCFS(proc p[])
{

    int tot_wait_t = 0,

        tot_turnaround_t = 0;

    for (int i = 0; i < num_process; i++)
    {

        tot_wait_t += p[i].wait_t;

        tot_turnaround_t += p[i].turnaround_t;
    }

    printf("\nAverage Turn Around Time: %6.1f", (float)tot_turnaround_t / num_process);

    printf("\nAverage Waiting Time    : %6.1f \n", (float)tot_wait_t / num_process);

    fprintf(fh, "\nFCFS algorithim");

    fprintf(fh, "\nAverage Turn Around Time: %6.1f", (float)tot_turnaround_t / num_process);

    fprintf(fh, "\nAverage Waiting Time    : %6.1f \n", (float)tot_wait_t / num_process);
}

/*---------------------------------FCFS Algo-----------------------------*/

void FCFS_ALgo(proc p[])
{

    calc_StartEndTime(p);

    calc_Time(p);

    calc_AvgTime_FCFS(p);
}

/* --------------------------------------------------------------------------------------------------*/

/* --------------------------------------------RR Methods-------------------------------------------*/

/* --------------------------------------------------------------------------------------------------*/

/*-------------------------------RR------------------------------------*/

void RR(proc p[])
{

    printf("\nProcess No \t\t Burst Time \t\t Turnaround Time \t\t Waiting Time ");

    int y; // number of process

    // temp is the remaining time

    // sum is current time

    for (sum = 0, i = 0; y != 0;)

    {

        if (temp[i] <= quant && temp[i] > 0) // if the remaining time between 0 and quantum time

        {

            sum = sum + temp[i];

            temp[i] = 0; // assign remaining time to 0

            counter = 1;
        }

        else if (temp[i] > 0) // if the remaining time is greater than quantum time

        {

            temp[i] = temp[i] - quant;

            sum = sum + quant;
        }

        if (temp[i] == 0 && counter == 1) // enter block if the first condtion is met

        {

            y--; // decrement the process no.

            printf("\nProcess No[%d] \t\t %d\t\t\t\t %d\t\t\t %d", i + 1, p[i].burst, sum - p[i].arriv, sum - p[i].arriv - p[i].burst);

            wt = wt + sum - p[i].arriv - p[i].burst;

            tat = tat + sum - p[i].arriv;

            counter = 0;
        }

        if (i == num_process - 1) // the last process

        {

            i = 0;
        }

        else if (p[i + 1].arriv <= sum) // move to next process

        {

            i++;
        }

        else // if arrival time to the next process is greater than current time

        {

            i = 0;
        }
    }
}

/*-------------------------------calc_AvgTime_RR------------------------------------*/

void calc_AvgTime_RR(proc p[])
{

    // represents the average waiting time and Turn Around time

    avg_wt = wt * (1.0 / num_process);

    avg_tat = tat * (1.0 / num_process);

    printf("\nAverage Turn Around Time: %6.1f", avg_tat);

    printf("\nAverage Waiting Time: %6.1f \n", avg_wt);

    fprintf(fh, "\nRR algorithim");

    fprintf(fh, "\nAverage Turn Around Time: %6.1f", avg_tat);

    fprintf(fh, "\nAverage Waiting Time: %6.1f \n", avg_wt);
}

/*---------------------------------RR Algo-------------------------------------------*/

void RR_ALgo(proc p[])
{

    RR(p);

    calc_AvgTime_RR(p);
}

/* --------------------------------------------------------------------------------------------------*/

/* -------------------------------------3 multilevel scheduling ------------------------------------*/

/* --------------------------------------------------------------------------------------------------*/

/*-----------------------calc_AvgTime_3 level MLQ-------------------------------------*/

void calc_AvgTime_level_3_MLQ()
{

    int tot_wait_t = 0,

        tot_turnaround_t = 0;

    for (int i = 0; i < num_process; i++)
    {

        tot_wait_t += Q1[i].wait_t;

        tot_turnaround_t += Q1[i].turnaround_t;

        tot_wait_t += Q2[i].wait_t;

        tot_turnaround_t += Q2[i].turnaround_t;

        tot_wait_t += Q3[i].wait_t;

        tot_turnaround_t += Q3[i].turnaround_t;
    }

    printf("\nAverage Turn Around Time: %6.1f", (float)tot_turnaround_t / num_process);

    printf("\nAverage Waiting Time    : %6.1f \n", (float)tot_wait_t / num_process);

    fprintf(fh, "\n3 multilevel scheduling algorithim");

    fprintf(fh, "\nAverage Turn Around Time: %6.1f", (float)tot_turnaround_t / num_process);

    fprintf(fh, "\nAverage Waiting Time: %6.1f \n", (float)tot_wait_t / num_process);
}

/*---------------------------------3 level MLQ--------------------------------------*/

void level_3_MLQ()
{

    time = Q1[0].arriv;

    printf("Process in first queue following RR with time quantum=%d \n", quant1);

    printf("\nProcess NO\t\tBurst\t\tWaiting\t\tTurnaround\tComplete");

    for (int i = 0; i < num_process; i++)
    {

        if (Q1[i].remaining_t <= quant1)
        {

            if (time < Q1[i].arriv)
            {

                time = Q1[i].arriv;
            }

            time += Q1[i].burst; // from arrival time of first process to completion of this process/

            Q1[i].wait_t = time - Q1[i].arriv - Q1[i].burst; // amount of time process has been waiting in the first queue/

            Q1[i].turnaround_t = time - Q1[i].arriv; // amount of time to execute the process/

            printf("\nProcess NO[%d]\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, Q1[i].burst, Q1[i].wait_t, Q1[i].turnaround_t, time);
        }

        else
        { // process moves to queue 2 with qt=25/

            if (time < Q1[i].arriv)
            {

                time = Q1[i].arriv;
            }

            time += quant1;

            Q1[i].remaining_t -= quant1;

            Q2[k].remaining_t = Q1[i].remaining_t;

            Q2[k].burst = Q1[i].burst;

            Q2[k].arriv = Q1[i].arriv;

            k = k + 1;
        }
    }

    printf("\nProcess in second queue following RR with time quantum=%d \n", quant2);

    printf("\nProcess NO\t\tBurst\t\tWaiting\t\tTurnaround\tComplete \n");

    for (int i = 0; i < k; i++)
    {

        if (Q2[i].remaining_t <= quant2)
        {

            time += Q2[i].remaining_t; // from arrival time of first process +burst of this process/

            Q2[i].wait_t = time - Q2[i].arriv - quant1 - Q2[i].remaining_t; // amount of time process has been waiting in the ready queue/

            Q2[i].turnaround_t = time - Q2[i].arriv; // amount of time to execute the process/

            printf("\nProcess NO[%d]\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, Q2[i].burst, Q2[i].wait_t, Q2[i].turnaround_t, time);
        }

        else
        { // process moves to queue 3 with FCFS/

            Q3[r].arriv = Q2[i].arriv;

            time += quant2;

            Q2[i].remaining_t -= quant2;

            Q3[r].remaining_t = Q2[i].remaining_t;

            Q3[r].burst = Q2[i].burst;

            r = r + 1;
        }
    }

    printf("\nProcess in third queue following FCFS\n ");

    printf("\nProcess NO\t\tBurst\t\tWaiting\t\tTurnaround\tComplete\n");

    for (int i = 0; i < r; i++)

    {

        if (i == 0)

            Q3[i].complete_t = Q3[i].remaining_t + time;

        else

            Q3[i].complete_t = Q3[i - 1].complete_t + Q3[i].remaining_t;
    }

    for (int i = 0; i < r; i++)
    {

        Q3[i].turnaround_t = Q3[i].complete_t - Q3[i].arriv;

        Q3[i].wait_t = Q3[i].turnaround_t - Q3[i].burst;
        printf("\n Process NO[%d]\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, Q3[i].burst, Q3[i].wait_t, Q3[i].turnaround_t, Q3[i].complete_t);
    }

    calc_AvgTime_level_3_MLQ();
}

/* --------------------------------------------------------------------------------------------------*/

/* -------------------------------------2 multilevel scheduling ------------------------------------*/

/* --------------------------------------------------------------------------------------------------*/

/*-----------------------RR_MLV2--------------------------------------*/

void RR_MLV2(process Q11[], process Q22[])
{

    if (Q11[r1].remaining_t <= quant1)
    {

        time1 += Q11[r1].burst; // from arrival time of first process to completion of this process/

        Q11[r1].pointer = time1; // <---- this added

        Q11[r1].wait_t = time1 - Q11[r1].arriv - Q11[r1].burst; // amount of time process has been waiting in the first queue/

        Q11[r1].turnaround_t = time1 - Q11[r1].arriv; // amount of time to execute the process /

        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\n", r1, Q11[r1].burst, Q11[r1].wait_t, Q11[r1].turnaround_t, time1);
    }
    else
    { // process moves to queue 2 with qt=2

        time1 += quant1;

        Q11[r1].pointer = time1; // <---- this added

        Q11[r1].remaining_t -= quant1;

        Q22[k1].remaining_t = Q11[r1].remaining_t;

        Q22[k1].burst = Q11[r1].burst;

        Q22[k1].arriv = Q11[r1].arriv;

        k1 = k1 + 1; // number of process in Q2
    }

    r1++; // to be ready to next iteration
}

/*-----------------------FCFS_MLV2------------------------------------*/

void FCFS_MLV2(process Q11[], process Q22[])
{

    int j = 0;

    do
    {

        printf("\nProcess in second queue FCFS_MLV2 ");

        printf("\nProcess\t\tBT\t\tWT\t\tTAT\t\tCT");

        if (j_1 == 0)
        {

            Q22[j_1].complete_t = Q22[j_1].remaining_t + time1;

            time1 = Q22[j_1].complete_t; //??
        }
        else
        {

            if (flag1 == 1)
            {

                Q22[j_1].complete_t = Q11[r1 - 1].pointer + Q22[j_1].remaining_t;

                flag1 = 0;
            }

            else
            {

                Q22[j_1].complete_t = Q22[j_1 - 1].complete_t + Q22[j_1].remaining_t;
            }
        }

        Q22[j_1].turnaround_t = Q22[j_1].complete_t - Q22[j_1].arriv;

        Q22[j_1].wait_t = Q22[j_1].turnaround_t - Q22[j_1].burst;

        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\n", j, Q22[j_1].burst, Q22[j_1].wait_t, Q22[j_1].turnaround_t, Q22[j_1].complete_t);

        j_1++;

    } while ((Q22[j_1].pointer < Q11[r1].arriv) && (j_1 < k1));
}

void FCFS2(process Q11[], process Q22[])
{

    do
    {

        printf("\nProcess in second queue following FCFS_MLV2 ");

        printf("\nProcess\t\tBT\t\tWT\t\tTAT\t\tCT");

        if (j_1 == 0)
        {

            Q22[j_1].complete_t = Q22[j_1].remaining_t + time1;
        }
        else
        {

            if (flag1 == 1)
            {


                Q22[j_1].complete_t = Q11[r1 - 1].pointer + Q22[j_1].remaining_t;

                flag1 = 0;
            }

            else
            {

                Q22[j_1].complete_t = Q22[j_1 - 1].complete_t + Q22[j_1].remaining_t;
            }
        }

        Q22[j_1].turnaround_t = Q22[j_1].complete_t - Q22[j_1].arriv;

        Q22[j_1].wait_t = Q22[j_1].turnaround_t - Q22[j_1].burst;

        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\n", j_1, Q22[j_1].burst, Q22[j_1].wait_t, Q22[j_1].turnaround_t, Q22[j_1].complete_t);

        j_1++;

    } while ((j_1 < k1));
}

/*---------------calc_AvgTime_2 level MLQ---------------------------*/

void calc_AvgTime_level_2_MLQ(process Q11[], process Q22[])
{

    int tot_wait_t = 0,

        tot_turnaround_t = 0;

    for (int i1 = 0; i1 < num_process1; i1++)
    {

        tot_wait_t += Q11[i1].wait_t;

        tot_turnaround_t += Q11[i1].turnaround_t;

        tot_wait_t += Q22[i1].wait_t;

        tot_turnaround_t += Q22[i1].turnaround_t;
    }

    printf("\nAverage Turn Around Time: %6.1f", (float)tot_turnaround_t / num_process1);

    printf("\nAverage Waiting Time    : %6.1f \n", (float)tot_wait_t / num_process1);

    fprintf(fh, "\n2 multilevel scheduling algorithim");

    fprintf(fh, "\nAverage Turn Around Time: %6.1f", (float)tot_turnaround_t / num_process1);

    fprintf(fh, "\nAverage Waiting Time    : %6.1f \n", (float)tot_wait_t / num_process1);
}

/*--------------------------2 level MLQ------------------------------*/

void MLV2(process Q11[], process Q22[])
{

    time1 = Q11[0].arriv;

    printf("\nProcess\t\tBurst\t\tWaiting\t\tTurnaround\tComplete");

    do
    {

        RR_MLV2(Q11, Q22);

        if (Q11[r1].arriv > Q11[r1 - 1].pointer && (k1 != 0))
        { // will not call FCFS_MLV2 until arrive time greater than finish time

            FCFS_MLV2(Q11, Q22); // if the arrive time to next process greater than current time

            flag1 = 1;

            m1++;
        }

        s1++;

    } while (s1 < num_process1);

    if (k1 != m1) // will not call FCFS_MLV2 until there are some process not executed yet

        FCFS2(Q11, Q22);

    calc_AvgTime_level_2_MLQ(Q11, Q22);
}

/* -------------------------------------------Read File Method-------------------------------------------*/

void readFile_1()
{

    /* Define a proc structure */

    FILE *filehandle;

    char lyne[100];

    char *item;

    int current_line = 0;

    int i;

    /* Here comes the actions! */

    /* open file */

    filehandle = fopen("test1.txt", "r");

    /* Read file line by line */

    while (fgets(lyne, 99, filehandle))
    {

        if (current_line == 0)
        {

            item = strtok(lyne, " ");

            num_process = atoi(item);

            num_process1 = num_process;

            current_line++;
        }
        else
        {

            if (i < num_process)
            {

                printf("%s", lyne);

                item = strtok(lyne, " ");

                p[i].arriv = atoi(item);

                Q1[i].arriv = p[i].arriv;

                Q11[i].arriv = p[i].arriv;

                item = strtok(NULL, " ");

                p[i].burst = atoi(item);

                temp[i] = p[i].burst;

                Q1[i].burst = p[i].burst;

                Q1[i].remaining_t = Q1[i].burst;

                Q11[i].burst = p[i].burst;

                Q11[i].remaining_t = Q11[i].burst;

                i++;
            }

            else
            {

                if (i == num_process)
                {

                    item = strtok(lyne, " ");

                    quant = atoi(item);

                    i++;
                }

                else if (i == num_process + 1)
                {

                    item = strtok(lyne, " ");

                    quant1 = atoi(item);

                    i++;
                }
                else if (i == num_process + 2)
                {

                    item = strtok(lyne, " ");

                    quant2 = atoi(item);

                    i++;
                }

                else
                {

                    break;
                }
            }
        }
    }

    /* Close file */

    fclose(filehandle);
}

/*-----------------------------------Main-------------------------------------------------*/

int main(int argc)
{

    // opening file in writing mode

    fh = fopen("output.txt", "w");

    // exiting program

    if (fh == NULL)
    {

        printf("Error opening file.!\n");

        exit(1);
    }

    int choice;

    while (flag == 0)
    { //<--- handel error if the user enters incorrect choice not 1 0r 2

        printf("Enteractivly: Press 1 \n");

        printf("File: Press 2 \n");

        scanf("%d", &choice); // 1.ask the user between enter inputs manually or from file

        if ((choice == 1) || (choice == 2))

            flag = 1;
    }

    flag = 0;

    /*-----------------------------Manually---------------------------------------*/

    if (choice == 1)
    {

        printf("            Schedulling algorithms		\n");

        printf("Total number of process: ");

        scanf("%d", &num_process);

        y = num_process; // 2.Assign the number of process to variable y

        num_process1 = num_process;

        // Use for loop to enter the details of the process like Arrival time and the Burst Time

        for (i = 0; i < num_process; i++)
        {

            printf("\nEnter the Arrival and Burst time of the Process[%d]\n", (i + 1));

            printf("Arrival time is: "); // Accept arrival time

            scanf("%d", &p[i].arriv);

            Q1[i].arriv = p[i].arriv;

            Q11[i].arriv = p[i].arriv;

            printf("Burst time is: "); // Accept the Burst time

            scanf("%d", &p[i].burst);

            Q1[i].burst = p[i].burst;

            Q11[i].burst = p[i].burst;

            Q1[i].remaining_t = Q1[i].burst;

            Q11[i].remaining_t = Q11[i].burst;

            temp[i] = p[i].burst; // store the burst time in temp array
        }

        sortByArrival_priority(); // <-----handel error if the processes not enter in correct order

        sortByArrival_priority1(); // <-----handel error if the processes not enter in correct order

        sortByArrival_priority2(); // <-----handel error if the processes not enter in correct order

        // Accept the Time qunat

        printf("Enter the Time Quantum for RR: ");

        scanf("%d", &quant);

        while (flag == 0)
        { // <------ handel error if quant2 < quant1

            printf("Enter the Time Quantum for RR1 of MLQ: ");

            scanf("%d", &quant1);

            printf("Enter the Time Quantum for RR2 of MLQ: ");

            scanf("%d", &quant2);

            if (quant1 <= quant2)

                flag = 1;
        }

        flag = 0;

        /*---------------------------------Calls algorithms ---------------------------------------*/

        printf("\n		FCFS scheduling algorithm		\n");

        FCFS_ALgo(p);

        printf("\n		RR scheduling algorithm			\n");

        RR_ALgo(p);

        printf("\n		3 level MLQ scheduling algorithm		\n");

        level_3_MLQ();

        printf("\n		2 level MLQ scheduling algorithm		\n");

        MLV2(Q11, Q22);
    }

    /*---------------------------------Read from file---------------------------------------*/

    else
    {

        printf("\n		FCFS scheduling algorithm		\n");

        readFile_1();

        sortByArrival_priority1(); // <-----handel error if the processes not enter in correct order

        FCFS_ALgo(p);

        printf("\n		RR scheduling algorithm			\n");

        readFile_1();

        sortByArrival_priority1(); // <-----handel error if the processes not enter in correct order

        RR_ALgo(p);

        printf("\n		3 level MLQ scheduling algorithm		\n");

        readFile_1();

        sortByArrival_priority(); // <-----handel error if the processes not enter in correct order

        level_3_MLQ(Q1, Q2, Q3);

        printf("\n		2 level MLQ scheduling algorithm		\n");

        readFile_1();

        sortByArrival_priority2(); // <-----handel error if the processes not enter in correct order

        MLV2(Q11, Q22);
    }

    fclose(fh);

    return 0;
}
