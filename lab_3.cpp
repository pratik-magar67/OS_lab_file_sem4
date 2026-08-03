#include <iostream>
using namespace std;

int main()
{
    int n, frameSize;

    cout << "Enter number of pages in reference string: ";
    cin >> n;

    int ref[50];
    cout << "Enter the reference string: ";
    for (int i = 0; i < n; i++)
        cin >> ref[i];

    cout << "Enter number of frames: ";
    cin >> frameSize;

    int frames[10];
    int lastUsed[10]; // stores the step number each frame's page was last used
    int frameCount = 0;
    int pageFaults = 0;

    for (int i = 0; i < frameSize; i++)
    {
        frames[i] = -1;
        lastUsed[i] = -1;
    }

    cout << "\nStep\tPage\tFrames\t\tStatus\n";

    for (int i = 0; i < n; i++)
    {
        int page = ref[i];
        bool hit = false;
        int hitIndex = -1;

        // Check if page is already in frames
        for (int j = 0; j < frameCount; j++)
        {
            if (frames[j] == page)
            {
                hit = true;
                hitIndex = j;
                break;
            }
        }

        if (hit)
        {
            // Update its last used time
            lastUsed[hitIndex] = i;
        }
        else
        {
            if (frameCount < frameSize)
            {
                // Free space available
                frames[frameCount] = page;
                lastUsed[frameCount] = i;
                frameCount++;
            }
            else
            {
                // Find the least recently used page (smallest lastUsed value)
                int minIndex = 0;
                for (int j = 1; j < frameCount; j++)
                {
                    if (lastUsed[j] < lastUsed[minIndex])
                        minIndex = j;
                }
                frames[minIndex] = page;
                lastUsed[minIndex] = i;
            }
            pageFaults++;
        }

        // Print current state
        cout << i + 1 << "\t" << page << "\t";
        for (int j = 0; j < frameCount; j++)
            cout << frames[j] << " ";
        cout << "\t\t" << (hit ? "Hit" : "Fault") << endl;
    }

    cout << "\nTotal number of page faults = " << pageFaults << endl;

    return 0;
}