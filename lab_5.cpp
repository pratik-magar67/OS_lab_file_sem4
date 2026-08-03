#include <iostream>
using namespace std;

int main()
{
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int pid[20], arrival[20], burst[20];
    int completion[20], turnaround[20], waiting[20];
    bool done[20];

    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        cout << "\nProcess " << pid[i] << ":\n";
        cout << "  Enter arrival time: ";
        cin >> arrival[i];
        cout << "  Enter burst time: ";
        cin >> burst[i];
        done[i] = false;
    }

    int currentTime = 0;
    int completed = 0;
    int totalTurnaround = 0, totalWaiting = 0;

    while (completed < n)
    {
        // Find the process with the shortest burst time among those
        // that have arrived by currentTime and are not yet completed
        int idx = -1;
        int minBurst = 9999;

        for (int i = 0; i < n; i++)
        {
            if (!done[i] && arrival[i] <= currentTime)
            {
                if (burst[i] < minBurst)
                {
                    minBurst = burst[i];
                    idx = i;
                }
            }
        }

        if (idx == -1)
        {
            // No process has arrived yet, move time forward
            currentTime++;
            continue;
        }

        // Run the selected process to completion
        currentTime = currentTime + burst[idx];
        completion[idx] = currentTime;
        turnaround[idx] = completion[idx] - arrival[idx];
        waiting[idx] = turnaround[idx] - burst[idx];

        totalTurnaround = totalTurnaround + turnaround[idx];
        totalWaiting = totalWaiting + waiting[idx];

        done[idx] = true;
        completed++;
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