/* C implementation of Peterson's mutual exclusion
   algorithm with a memory fence and yield lock
   approach. The goal of the improved Peterson's
   algorithm is to reduce the wastage of CPU clock cycles.
   In the solution without memory fence and yield lock,
   when a thread was waiting for its turn, it ended in a
   long while loop that tested the condition millions of
   times per second and thus doing unnecesssary computation.
   The better way is called "yield". The approach taken
   here is a simplified version of the how the Process
   scheduler works in Linux.

   Consider the following borrowed example: there are
   three processes, P1, P2 and P3. Process 3 is such that
   it has a while loop similar to the one in our code,
   doing not do useful computation, and it exits from the
   loop only when P2 finishes its execution. The scheduler
   puts all of them in a round robin queue. Now, say the
   clock speed of the processor is 1000000/sec. and it
   allocates 100 clocks to each process in each iteration,
   Then, first P1 will be run for 100 clocks (0,0001 seconds),
   then P2 (0.0001 seconds) followed by P3 (0.0001 seconds).
   Now, since there are no more processes, this cycle repeats
   until P2 ends and then is followed by P3's execution and
   eventually its termination. 

   This is a complete waste of 100 CPU clock cycles. To
   avoid this, the processes mutually give up the CPU
   time slice, i.e. yield, which essentially end this
   time slice and the scheduler picks up the next process
   to run. Now, we test our condition once, then give up the
   CPU. Considering that our test takes 25 clock cycles, we
   save 75% of our computation in each time slice. Considering
   the processor clock speed at 1MHz, this is a large savings.
   Different OSes provide different functions to achieve this
   functionality. Linux provides sched_yield(). */

   // Note: to compile use: gcc -pthreads -o peterson peterson_yieldlock.c


#include<stdio.h>
#include<pthread.h>
#include "mythreads.h"

int flag[2];
int turn;
const int MAX = 1e9;
int ans = 0;

void lock_init()
{
	// Initialize lock by resetting the desire of
	// both the threads to acquire the locks.
	// And, giving turn to one of them.
	flag[0] = flag[1] = 0;

	turn = 0;
}

// Executed before entering critical section
void lock(int self)
{
	// Set flag[self] = 1 saying you want
	// to acquire lock
	flag[self]=1;

	// But, first give the other thread the
	// chance to acquire lock
	turn = 1-self;

	// Memory fence to prevent the reordering
	// of instructions beyond this barrier.
	__sync_synchronize();

	// Wait until the other thread loses the
	// desire to acquire lock or it is your
	// turn to get the lock.
	while (flag[1-self]==1 && turn==1-self)

		// Yield to avoid wastage of resources.
		sched_yield();
}

// Executed after leaving critical section
void unlock(int self)
{
	// You do not desire to acquire lock in future.
	// This will allow the other thread to acquire
	// the lock.
	flag[self]=0;
}

// A Sample function run by two threads created
// in main()
void* func(void *s)
{
	int i = 0;
	int self = (int *)s;
	printf("Thread Entered: %d\n",self);
	lock(self);

	// Critical section (Only one thread
	// can enter here at a time)
	for (i=0; i<MAX; i++)
		ans++;

	unlock(self);
}

// Driver code
int main()
{
	pthread_t p1, p2;

	// Initialize the lock
	lock_init();

	// Create two threads (both run func)
	Pthread_create(&p1, NULL, func, (void*)0);
	Pthread_create(&p2, NULL, func, (void*)1);

	// Wait for the threads to end.
	Pthread_join(p1, NULL);
	Pthread_join(p2, NULL);

	printf("Actual Count: %d | Expected Count:"
		" %d\n",ans,MAX*2);

	return 0;
}
