#include <iostream>
using namespace std;

int main()
{
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int pid[20], arrival[20], burst[20];
    int completion[20], turnaround[20], waiting[20];

    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        cout << "\nProcess " << pid[i] << ":\n";
        cout << "  Enter arrival time: ";
        cin >> arrival[i];
        cout << "  Enter burst time: ";
        cin >> burst[i];
    }

    // Sort all processes by arrival time (FCFS order) using simple bubble sort
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arrival[j] > arrival[j + 1])
            {
                // swap arrival
                int temp = arrival[j];
                arrival[j] = arrival[j + 1];
                arrival[j + 1] = temp;

                // swap burst
                temp = burst[j];
                burst[j] = burst[j + 1];
                burst[j + 1] = temp;

                // swap pid
                temp = pid[j];
                pid[j] = pid[j + 1];
                pid[j + 1] = temp;
            }
        }
    }

    int currentTime = 0;
    int totalTurnaround = 0, totalWaiting = 0;

    for (int i = 0; i < n; i++)
    {
        // If CPU is idle before this process arrives, move time forward
        if (currentTime < arrival[i])
            currentTime = arrival[i];

        currentTime = currentTime + burst[i];
        completion[i] = currentTime;

        turnaround[i] = completion[i] - arrival[i];
        waiting[i] = turnaround[i] - burst[i];

        totalTurnaround = totalTurnaround + turnaround[i];
        totalWaiting = totalWaiting + waiting[i];
    }

    cout << "\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << pid[i] << "\t"
             << arrival[i] << "\t"
             << burst[i] << "\t"
             << completion[i] << "\t\t"
             << turnaround[i] << "\t\t"
             << waiting[i] << endl;
    }

    float avgTurnaround = (float)totalTurnaround / n;
    float avgWaiting = (float)totalWaiting / n;

    cout << "\nAverage Turnaround Time = " << avgTurnaround << endl;
    cout << "Average Waiting Time = " << avgWaiting << endl;

    return 0;
}