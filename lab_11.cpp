#include <iostream>
using namespace std;

int main()
{
    int n, totalCylinders, head, direction;

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

    cout << "Enter head movement direction (0 = towards lower cylinders, 1 = towards higher cylinders): ";
    cin >> direction;

    // Simple bubble sort of the request array
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (request[j] > request[j + 1])
            {
                int temp = request[j];
                request[j] = request[j + 1];
                request[j + 1] = temp;
            }
        }
    }

    // Split sorted requests into those left of head and right of head
    int left[50], right[50];
    int leftCount = 0, rightCount = 0;

    for (int i = 0; i < n; i++)
    {
        if (request[i] < head)
            left[leftCount++] = request[i];
        else
            right[rightCount++] = request[i];
    }

    int totalSeekTime = 0;
    int currentPos = head;

    cout << "\nSeek Sequence: " << currentPos;

    if (direction == 1)
    {
        // Move towards higher cylinders first, servicing requests on the way
        for (int i = 0; i < rightCount; i++)
        {
            totalSeekTime = totalSeekTime + abs(currentPos - right[i]);
            currentPos = right[i];
            cout << " -> " << currentPos;
        }

        // Go all the way to the last cylinder (end of disk)
        if (currentPos != totalCylinders - 1)
        {
            totalSeekTime = totalSeekTime + abs(currentPos - (totalCylinders - 1));
            currentPos = totalCylinders - 1;
            cout << " -> " << currentPos;
        }

        // Reverse direction, service remaining requests from highest to lowest
        for (int i = leftCount - 1; i >= 0; i--)
        {
            totalSeekTime = totalSeekTime + abs(currentPos - left[i]);
            currentPos = left[i];
            cout << " -> " << currentPos;
        }
    }
    else
    {
        // Move towards lower cylinders first, servicing requests on the way
        for (int i = leftCount - 1; i >= 0; i--)
        {
            totalSeekTime = totalSeekTime + abs(currentPos - left[i]);
            currentPos = left[i];
            cout << " -> " << currentPos;
        }

        // Go all the way to cylinder 0 (start of disk)
        if (currentPos != 0)
        {
            totalSeekTime = totalSeekTime + abs(currentPos - 0);
            currentPos = 0;
            cout << " -> " << currentPos;
        }

        // Reverse direction, service remaining requests from lowest to highest
        for (int i = 0; i < rightCount; i++)
        {
            totalSeekTime = totalSeekTime + abs(currentPos - right[i]);
            currentPos = right[i];
            cout << " -> " << currentPos;
        }
    }

    cout << "\n\nTotal Seek Time = " << totalSeekTime << endl;
    cout << "Final position of Read/Write head = " << currentPos << endl;

    return 0;
}