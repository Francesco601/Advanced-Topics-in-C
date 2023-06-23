/* C++ program to demonstrate  C-SCAN                                         
   Disk Scheduling algorithm. The C-SCAN                                       
 (Circular Elevator) schedling algorithm                                       
 is a modified version of the SCAN disk                                        
 scheduling algorithm that deals with the                                       inefficency of the SCAN algorithm by servicing                                
 the requests more uniformly. Like SCAN, C-SCAN                                
 moves the head from the end servicing all the                                  requests to the other end, However, as soon                                   
 as the head reaches the other end, it immediately                              returns to the beginning of the disk without                                  
 servicing any requests on the return trip and starts                          
servicing again once it reaches the beginning.                                
                                                                               
 It is known as the "Circular Elevator Algorithm"                              
 since it treats the cylinders as a circular list                              
 that wraps around from the final cylinder to the                              
 first one. */                                        

#include <bits/stdc++.h>
using namespace std;


int size = 8;
int disk_size = 200;

void CSCAN(int arr[], int head)
{
        int size=8;
	int seek_count = 0;
	int distance, cur_track;
	vector<int> left, right;
	vector<int> seek_sequence;

	// appending end values
	// which has to be visited
	// before reversing the direction
	left.push_back(0);
	right.push_back(disk_size - 1);

	// tracks on the left of the
	// head will be serviced when
	// once the head comes back
	// to the beginning (left end).
	for (int i = 0; i < size; i++) {
		if (arr[i] < head)
			left.push_back(arr[i]);
		if (arr[i] > head)
			right.push_back(arr[i]);
	}

	// sorting left and right vectors
	std::sort(left.begin(), left.end());
	std::sort(right.begin(), right.end());

	// first service the requests
	// on the right side of the
	// head.
	for (int i = 0; i < right.size(); i++) {
		cur_track = right[i];
		// appending current track to seek sequence
		seek_sequence.push_back(cur_track);

		// calculate absolute distance
		distance = abs(cur_track - head);

		// increase the total count
		seek_count += distance;

		// accessed track is now new head
		head = cur_track;
	}

	// once reached the right end
	// jump to the beginning.
	head = 0;

	// adding seek count for head returning from 199 to 0
	seek_count += (disk_size - 1);

	// Now service the requests again
	// which are left.
	for (int i = 0; i < left.size(); i++) {
		cur_track = left[i];

		// appending current track to seek sequence
		seek_sequence.push_back(cur_track);

		// calculate absolute distance
		distance = abs(cur_track - head);

		// increase the total count
		seek_count += distance;

		// accessed track is now the new head
		head = cur_track;
	}

	cout << "Total number of seek operations = "
		<< seek_count << endl;

	cout << "Seek Sequence is" << endl;

	for (int i = 0; i < seek_sequence.size(); i++) {
		cout << seek_sequence[i] << endl;
	}
}

// Driver code
int main()
{

	// request array
	int arr[8] = { 176, 79, 34, 60, 92, 11, 41, 114 };
	int head = 50;

	cout << "Initial position of head: " << head << endl;
	CSCAN(arr, head);

	return 0;
}
