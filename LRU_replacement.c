// C program implementation of
// Least Recently Used (LRU) algorithm
// for page replacement in operating systems.
// The LRU algorithm is a Greedy Algorithm where
// the page to be replaced is least recently used. The
// idea is based on locality of reference.
// Time complexity of set and map operations is O(1)
// and the worst-casecomplexity is O(n) but O(n) is
// the dominant term. Space complexity is O(capacity)
// which is a constant and depends on the size of the input array
// and the size of the memory buffer.

#include<stdio.h>
 
int findLRU(int time[], int n){
    int i, minimum = time[0], pos = 0;
 
    for(i = 1; i < n; ++i) {
      if(time[i] < minimum) {
          minimum = time[i];
           pos = i;  
      } 
    } 
return pos;
}  
 
int main()
{
    int no_of_frames, no_of_pages;
    int frames[10], pages[30], counter = 0, time[10];
    int flag1, flag2, i, j, pos, faults = 0;

     printf("Enter number of frames: ");
     scanf("%d", &no_of_frames);
    
     printf("Enter number of pages: ");
     scanf("%d", &no_of_pages);
     
     printf("Enter reference string separated by spaces: ");
     for(i = 0; i < no_of_pages; ++i)
        scanf("%d", &pages[i]);
    
    
      for(i = 0; i < no_of_frames; ++i)
          frames[i] = -1;
    
    
      for(i = 0; i < no_of_pages; ++i){
         flag1 = flag2 = 0;
    
       for(j = 0; j < no_of_frames; ++j){
          if(frames[j] == pages[i]){
           counter++;
          time[j] = counter;
          flag1 = flag2 = 1;
          break;
	  } //end if
       } //end for
    
        if(flag1 == 0){
            for(j = 0; j < no_of_frames; ++j){
            if(frames[j] == -1){
               counter++;
               faults++;
               frames[j] = pages[i];
               time[j] = counter;
              flag2 = 1;
              break;
	    } //end if
	    } //end for
	} //end if
    
         if(flag2 == 0){
              pos = findLRU(time, no_of_frames);
              counter++;
             faults++;
             frames[pos] = pages[i];
             time[pos] = counter;
	 } //end if
    
     printf("\n");
    
     for(j = 0; j < no_of_frames; ++j)
           printf("%d\t", frames[j]);
     
      } // end for
     printf("\n\nTotal Page Faults = %d", faults);
    
      return 0;
} // end main
