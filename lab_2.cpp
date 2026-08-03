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
    int frameCount = 0;
    int pageFaults = 0;

    for (int i = 0; i < frameSize; i++)
        frames[i] = -1;

    cout << "\nStep\tPage\tFrames\t\tStatus\n";

    for (int i = 0; i < n; i++)
    {
        int page = ref[i];
        bool hit = false;

        // Check if page is already in frames
        for (int j = 0; j < frameCount; j++)
        {
            if (frames[j] == page)
            {
                hit = true;
                break;
            }
        }

        if (!hit)
        {
            if (frameCount < frameSize)
            {
                // Free space available
                frames[frameCount] = page;
                frameCount++;
            }
            else
            {
                // Find the page that will not be used for the longest time
                int farthest = -1, replaceIndex = -1;

                for (int j = 0; j < frameCount; j++)
                {
                    int k;
                    for (k = i + 1; k < n; k++)
                    {
                        if (frames[j] == ref[k])
                            break;
                    }

                    // If this page is never used again, replace it immediately
                    if (k == n)
                    {
                        replaceIndex = j;
                        break;
                    }

                    // Otherwise track the one used farthest in the future
                    if (k > farthest)
                    {
                        farthest = k;
                        replaceIndex = j;
                    }
                }

                frames[replaceIndex] = page;
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