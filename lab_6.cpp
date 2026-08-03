#include <iostream>
using namespace std;

int main()
{
    int n, timeQuantum;

    cout << "Enter number of processes: ";
    cin >> n;

    int pid[20], arrival[20], burst[20], remaining[20];
    int completion[20], turnaround[20], waiting[20];

    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        cout << "\nProcess " << pid[i] << ":\n";
        cout << "  Enter arrival time: ";
        cin >> arrival[i];
        cout << "  Enter burst time: ";
        cin >> burst[i];
        remaining[i] = burst[i];
    }

    cout << "\nEnter time quantum: ";
    cin >> timeQuantum;

    int currentTime = 0;
    int completed = 0;

    // Simple queue implemented using an array
    int queue[1000];
    int front = 0, rear = 0;
    bool inQueue[20];

    for (int i = 0; i < n; i++)
        inQueue[i] = false;

    // Add any process that has already arrived at time 0
    for (int i = 0; i < n; i++)
    {
        if (arrival[i] <= currentTime && !inQueue[i])
        {
            queue[rear++] = i;
            inQueue[i] = true;
        }
    }

    while (completed < n)
    {
        if (front == rear)
        {
            // Queue is empty, move time forward to next arrival
            currentTime++;
            for (int i = 0; i < n; i++)
            {
                if (arrival[i] <= currentTime && !inQueue[i])
                {
                    queue[rear++] = i;
                    inQueue[i] = true;
                }
            }
            continue;
        }

        int cur = queue[front++];

        if (remaining[cur] > timeQuantum)
        {
            currentTime = currentTime + timeQuantum;
            remaining[cur] = remaining[cur] - timeQuantum;
        }
        else
        {
            currentTime = currentTime + remaining[cur];
            remaining[cur] = 0;
        }

        // After running this process, add any new arrivals (in order)
        for (int i = 0; i < n; i++)
        {
            if (arrival[i] <= currentTime && !inQueue[i])
            {
                queue[rear++] = i;
                inQueue[i] = true;
            }
        }

        if (remaining[cur] == 0)
        {
            completion[cur] = currentTime;
            turnaround[cur] = completion[cur] - arrival[cur];
            waiting[cur] = turnaround[cur] - burst[cur];
            completed++;
        }
        else
        {
            // Not finished, put it back at the end of the queue
            queue[rear++] = cur;
        }
    }

    int totalTurnaround = 0, totalWaiting = 0;
    for (int i = 0; i < n; i++)
    {
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