/* C implementation of the
   Second Chance Algorithm for
   page replacement. The basic
   is idea is the same as FIFO
   replacement, except that when
   a page has been selected, its
   reference bit is inspected.
   If the value is 0, we replace
   the page, If its reference bit
   is set to 1, the page is given
   a second chance and we move on
   to select the next FIFO page.

   When a page gets a second chance, its
   reference bit is cleared, and its arrival
   time is reset to the current time. A page
   that is given a second chance will not
   ve replaced until all other pages have been
   replaced (or given second chances). */


#include<stdio.h>
#include<stdlib.h>

#define MAX_FRAMES 3 // set maximum number of frames


typedef struct {  // define Frame structure with
     int page;     // crucial reference bit
    int reference_bit;
} Frame;

// function to find the index of a page in the frame table.
int getPageIndex(Frame frames[], int page, int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i].page == page) {
            return i;
        }
    }
    return -1;
}
// function to locate the victim page to be
// replaced based on the second chance algorithm
int getVictimPage(Frame frames[], int n, int reference_bits[]) {
    int i = 0;

    while (1) {
        if (frames[i].reference_bit == 0) {
            return i;
        }

        frames[i].reference_bit = 0;
        i = (i + 1) % n;
    }
}

// display the current state of the frames
void displayFrames(Frame frames[], int n) {
    printf("Frames: ");
    for (int i = 0; i < n; i++) {
        if (frames[i].page == -1) {
            printf(" -");
        } else {
            printf(" %d", frames[i].page);
        }
    }
    printf("\n");
}

// iterate through array of pages and check if the page
// is present in the frame table. If not present, we
// find victim page and replace with current page. If
// present, update reference bit and display frames
void simulate(int page_faults[], int pages[], int n, int frames) {
    Frame *frame_table = (Frame*) malloc(frames * sizeof(Frame));
    int *reference_bits = (int*) malloc(frames * sizeof(int));

    for (int i = 0; i < frames; i++) {
        frame_table[i].page = -1;
        frame_table[i].reference_bit = 0;
        reference_bits[i] = 0;
    }

    int next_frame = 0;
    int page_fault_count = 0;

    for (int i = 0; i < n; i++) {
        printf("Reference: %d\n", pages[i]);
        int page_index = getPageIndex(frame_table, pages[i], frames);

        // If page is not present in frames
        if (page_index == -1) {
            int victim_page = getVictimPage(frame_table, frames, reference_bits);
            frame_table[victim_page].page = pages[i];
            frame_table[victim_page].reference_bit = 1;
            reference_bits[victim_page] = 1;
            page_fault_count++;
            displayFrames(frame_table, frames);
        } else {
            reference_bits[page_index] = 1;
            displayFrames(frame_table, frames);
        }
    }

    *page_faults = page_fault_count;
    free(frame_table);
    free(reference_bits);
}
// driver code
int main() {
    int n;
    printf("Enter number of pages: ");
    scanf("%d", &n);

    int *pages = (int*) malloc(n * sizeof(int));

    printf("Enter the page references: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    int page_faults;  // counter for total page faults
    simulate(&page_faults, pages, n, MAX_FRAMES);

    printf("Total page faults: %d\n", page_faults);

    free(pages);
    return 0;
}
