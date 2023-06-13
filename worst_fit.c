/* C implementation of Worst Fit algorithm in
   memory management. Worst fit allocates the
   process to a partition which is the largest
    among all the available partitions. First
   we input memory blocks and processes with sizes.
   Then we initalize all memory blocks as free.
   In step three, we start by picking each process
   and find the maximum  block size that can be
   assigned to the current process (i.e. find
   max(blockSize[1],blockSize[2],
   ...blockSize[n]) > processSize[current]. If found,
   then assign it to the current proces. If not, then
   leave that process and keep checking for further
   processes. The time complexity is O(n^2) because
   there are two loops to process the memory blocks
   and processes.The outer loop is used to iterate
   through the processes and the inner to iterate
   through the memory blocks. Space complexity is
   O(n) since it requires an array of length n to
   store the block allocation for each process. */
   
#include <stdio.h>
#include <stdlib.h>

// Function to allocate memory to blocks as per Worst Fit algorithm
void worstFit(int blockSize[], int m, int processSize[], int n)
{
	// Stores block id of the block allocated to a process
	int allocation[n];

	// Initially no block is assigned to any process
	for (int i = 0; i < n; i++)
		allocation[i] = -1;

	// pick each process and find suitable blocks
	// according to its size ad assign to it
	for (int i = 0; i < n; i++)
	{
		// Find the best fit block for current process
		int wstIdx = -1;
		for (int j = 0; j < m; j++)
		{
			if (blockSize[j] >= processSize[i])
			{
				if (wstIdx == -1)
					wstIdx = j;
				else if (blockSize[wstIdx] < blockSize[j])
					wstIdx = j;
			}
		}

		// If we could find a block for current process
		if (wstIdx != -1)
		{
			// allocate block j to p[i] process
			allocation[i] = wstIdx;

			// Reduce available memory in this block.
			blockSize[wstIdx] -= processSize[i];
		}
	}

	printf("\nProcess No.\tProcess Size\tBlock no.\n");
	for (int i = 0; i < n; i++)
	{
              printf("%d\t\t%d\t\t",i+1,processSize[i]);
              if(allocation[i] != -1)
                 printf("%d\n",allocation[i] + 1);
               else		  
		  printf("Not allocated\n");
	}
}

// Driver Method
int main()
{
	int blockSize[] = {100, 500, 200, 300, 600};
	int processSize[] = {212, 417, 112, 426};
	int m = sizeof(blockSize) / sizeof(blockSize[0]);
	int n = sizeof(processSize) / sizeof(processSize[0]);

	worstFit(blockSize, m, processSize, n);

	return 0 ;
}
