#include <iostream>
using namespace std;

int main()
{
    int n, totalCylinders, head;

    cout << "Enter total number of cylinders (disk size): ";
    cin >> totalCylinders;

    cout << "Enter current head position: ";
    cin >> head;

    cout << "Enter number of pending requests: ";
    cin >> n;

    int request[50];
    cout << "Enter the request queue:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "  Request " << i + 1 << ": ";
        cin >> request[i];
    }

    int totalSeekTime = 0;
    int currentPos = head;

    cout << "\nSeek Sequence: " << currentPos;

    // FCFS: service requests strictly in the order they arrived
    for (int i = 0; i < n; i++)
    {
        totalSeekTime = totalSeekTime + abs(currentPos - request[i]);
        currentPos = request[i];
        cout << " -> " << currentPos;
    }

    cout << "\n\nTotal Seek Time = " << totalSeekTime << endl;
    cout << "Final position of Read/Write head = " << currentPos << endl;

    return 0;
}