#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int waiting;
    int response;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);


    struct Process *p = (struct Process*)malloc(n * sizeof(struct Process));

    for (int i = 0; i < n; i++) {
        (p+i)->pid = i + 1;
        printf("Enter Arrival Time of P%d: ", (p+i)->pid);
        scanf("%d", &(p+i)->arrival);
        printf("Enter Burst Time of P%d: ", (p+i)->pid);
        scanf("%d", &(p+i)->burst);
    }


    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((p+i)->arrival > (p+j)->arrival) {
                struct Process temp = *(p+i);
                *(p+i) = *(p+j);
                *(p+j) = temp;
            }
        }
    }


    int currentTime = 0;
    float totalTAT = 0, totalWT = 0, totalRT = 0;

    for (int i = 0; i < n; i++) {
        if (currentTime < (p+i)->arrival) {
            currentTime = (p+i)->arrival; // CPU waits if process not arrived
        }
        (p+i)->completion = currentTime + (p+i)->burst;
        (p+i)->turnaround = (p+i)->completion - (p+i)->arrival;
        (p+i)->waiting = (p+i)->turnaround - (p+i)->burst;
        (p+i)->response = (p+i)->waiting; // same in FCFS
        currentTime = (p+i)->completion;


        totalTAT += (p+i)->turnaround;
        totalWT  += (p+i)->waiting;
        totalRT  += (p+i)->response;
    }


    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               (p+i)->pid, (p+i)->arrival, (p+i)->burst,
               (p+i)->completion, (p+i)->turnaround,
               (p+i)->waiting, (p+i)->response);
    }


    printf("\nAverage Turnaround Time = %.2f", totalTAT/n);
    printf("\nAverage Waiting Time    = %.2f", totalWT/n);
    printf("\nAverage Response Time   = %.2f\n", totalRT/n);

    free(p);
    return 0;
}
