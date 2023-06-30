/* C++ program to implement C-LOOK disk
   scheduling algorithm. C-LOOK is a modified
   version of both the LOOK and SCAN algorithms.
   In the algorithm, the head starts from the first
   request in one direction and moves toward the
   last request at the other end, servicing all
   requests in between, After reaching the last
   request in one end, the head does not reverse
   direction but jumps in the other direction and
   moves toward the remaining requests and satisfies
   them in the same direction it started in. (e.g.
   if it started moving rightward across a cylinder
   it will jump to the other end and move always rightwar
   to service the other requests). The head is allowed
   to move in only one direction. C-LOOK has the best
   performance of all disk scheduling algorithms.
   C-LOOK can handle requests more effectively than
   LOOK and provides uniform waiting and response
   times */

#include <bits/stdc++.h>
using namespace std;
int disk_size = 200;

// Function to perform C-LOOK on the request
// array starting from the given head
void CLOOK(int arr[], int head)
{
        int size=8;
	int seek_count = 0;
	int distance, cur_track;
	vector<int> left, right;
	vector<int> seek_sequence;

	// Tracks on the left of the
	// head will be serviced when
	// once the head comes back
	// to the beginning (left end)
	for (int i = 0; i < size; i++) {
		if (arr[i] < head)
			left.push_back(arr[i]);
		if (arr[i] > head)
			right.push_back(arr[i]);
	}

	// Sorting left and right vectors
	std::sort(left.begin(), left.end());
	std::sort(right.begin(), right.end());

	// First service the requests
	// on the right side of the
	// head
	for (int i = 0; i < right.size(); i++) {
		cur_track = right[i];

		// Appending current track to seek sequence
		seek_sequence.push_back(cur_track);

		// Calculate absolute distance
		distance = abs(cur_track - head);

		// Increase the total count
		seek_count += distance;

		// Accessed track is now new head
		head = cur_track;
	}

	// Once reached the right end
	// jump to the last track that
	// is needed to be serviced in
	// left direction
	seek_count += abs(head - left[0]);
	head = left[0];

	// Now service the requests again
	// which are left
	for (int i = 0; i < left.size(); i++) {
		cur_track = left[i];

		// Appending current track to seek sequence
		seek_sequence.push_back(cur_track);

		// Calculate absolute distance
		distance = abs(cur_track - head);

		// Increase the total count
		seek_count += distance;

		// Accessed track is now the new head
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
	// Request array
	int arr[8] = { 176, 79, 34, 60,
					92, 11, 41, 114 };
	int head = 50;

	cout << "Initial position of head: " << head << endl;

	CLOOK(arr, head);

	return 0;
}


