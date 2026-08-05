#include <iostream>
using namespace std;

int main()
{
    int p, r;

    cout << "Enter number of processes: ";
    cin >> p;

    cout << "Enter number of resource types: ";
    cin >> r;

    int allocation[10][10];
    int maxDemand[10][10];
    int need[10][10];
    int available[10];

    cout << "\nEnter Allocation matrix:\n";
    for (int i = 0; i < p; i++)
    {
        cout << " Process " << i << ":\n";
        for (int j = 0; j < r; j++)
        {
            cout << "  Allocation of resource " << j << ": ";
            cin >> allocation[i][j];
        }
    }

    cout << "\nEnter Max matrix:\n";
    for (int i = 0; i < p; i++)
    {
        cout << " Process " << i << ":\n";
        for (int j = 0; j < r; j++)
        {
            cout << "  Max demand of resource " << j << ": ";
            cin >> maxDemand[i][j];
        }
    }

    cout << "\nEnter Available resources:\n";
    for (int j = 0; j < r; j++)
    {
        cout << " Resource " << j << ": ";
        cin >> available[j];
    }

    // Calculate the Need matrix = Max - Allocation
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
        {
            need[i][j] = maxDemand[i][j] - allocation[i][j];
        }
    }

    bool finished[10];
    for (int i = 0; i < p; i++)
        finished[i] = false;

    int safeSequence[10];
    int count = 0;

    int work[10];
    for (int j = 0; j < r; j++)
        work[j] = available[j];

    // Repeat until no more processes can be found, or all are finished
    while (count < p)
    {
        bool foundProcess = false;

        for (int i = 0; i < p; i++)
        {
            if (finished[i])
                continue;

            // Check if this process's need can be satisfied with current work
            bool canRun = true;
            for (int j = 0; j < r; j++)
            {
                if (need[i][j] > work[j])
                {
                    canRun = false;
                    break;
                }
            }

            if (canRun)
            {
                // Process can finish; release its allocated resources back to work
                for (int j = 0; j < r; j++)
                    work[j] = work[j] + allocation[i][j];

                finished[i] = true;
                safeSequence[count] = i;
                count++;
                foundProcess = true;
            }
        }

        // If no process could be run in this pass, no more progress is possible
        if (!foundProcess)
            break;
    }

    if (count == p)
    {
        cout << "\nThe system is in a SAFE state (no deadlock).\n";
        cout << "Safe Sequence: ";
        for (int i = 0; i < count; i++)
        {
            cout << "P" << safeSequence[i];
            if (i != count - 1)
                cout << " -> ";
        }
        cout << endl;
    }
    else
    {
        cout << "\nThe system is in an UNSAFE state (deadlock may occur).\n";
    }

    return 0;
}