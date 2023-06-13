/* C implementation of Best Fit algorithm in
   memory management. Best fit allocates the
   process to a partition which is the smallest
   sufficient partition among all the available
   partitions. First we input memory blocks and
   processes with sizes. Then we initalize all
   memory blocks as free. In step three, we start
   by picking each process and find the minimum
   block size that can be assigned to the current
   process (i.e. find min(blockSize[1],blockSize[2],
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

// Function to allocate memory to blocks as per Best Fit algorithm
void bestFit(int blockSize[], int m, int processSize[], int n)
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
		int bestIdx = -1;
		for (int j = 0; j < m; j++)
		{
			if (blockSize[j] >= processSize[i])
			{
				if (bestIdx == -1)
					bestIdx = j;
				else if (blockSize[bestIdx] > blockSize[j])
					bestIdx = j;
			}
		}

		// If we could find a block for current process
		if (bestIdx != -1)
		{
			// allocate block j to p[i] process
			allocation[i] = bestIdx;

			// Reduce available memory in this block.
			blockSize[bestIdx] -= processSize[i];
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

	bestFit(blockSize, m, processSize, n);

	return 0 ;
}
