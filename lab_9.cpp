#include <iostream>
using namespace std;

int main()
{
    int m, n;

    cout << "Enter number of memory blocks: ";
    cin >> m;

    int blockSize[20];
    cout << "Enter size of each block:\n";
    for (int i = 0; i < m; i++)
    {
        cout << "  Block " << i + 1 << ": ";
        cin >> blockSize[i];
    }

    cout << "\nEnter number of processes: ";
    cin >> n;

    int processSize[20];
    cout << "Enter size of each process:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "  Process " << i + 1 << ": ";
        cin >> processSize[i];
    }

    int allocation[20]; // allocation[i] = block number allotted to process i (-1 = not allotted)
    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    // For each process, find the first block that is large enough (First Fit)
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                allocation[i] = j;
                blockSize[j] = blockSize[j] - processSize[i]; // reduce remaining space
                break;                                        // stop at the first block that fits
            }
        }
    }

    cout << "\nProcess\tSize\tBlock Allotted\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << "\t" << processSize[i] << "\t";
        if (allocation[i] != -1)
            cout << "Block " << allocation[i] + 1 << endl;
        else
            cout << "Not Allotted" << endl;
    }

    return 0;
}