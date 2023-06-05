/* C implementation of the Optimimal Page  Replacement Algorithm.
   In a computer operating  system that used paging for virtual
   memory management, page replacement algorithms decide which memory
   pages to page out (swap out) or write to disk when a page of memory needs
   to be allocated. Page replacemant happens when a requested page is not
   in memory (page fault) and a free page cannot be used to satsify the
   allocation, either because there are none, or because the number of
   free pages is below some thresholds.The goal of all PRA is to reduce the
   number of page faults. In an optiminal page replacemet  algorithm
   the OS replaces the page that will not be used for the longest period
   of time in the future. The idea is simple: 1) if referenced page is
   already present, increment the hit count. 2) If the page is not present,
   find a page that is never referenced in the future. If such a page exists.,
   replace this page with new page. If not such page exists, find a page that
   is references farthest in the future. Replace this page with new page.

   The time complexity of the algorithm depends on the number of page
   references and the number of frames. Worst case complexity is
   O(pn * fn^2) which occurs when all page references are unique and
   there are no empty frames available. In this case, for each page
   reference, we may have to iterate through all the frames to check if
   the page is present, and then iterate through all the remaining references
   to find the page that will not be needed for the longest period of time
   in the future. In practice, however, the algorithm performs much better
   than its worse case scenario, as it is rare to have all page references
   unique, and the number of frames is usually limited. */
   


#include<stdio.h>
int main()
{
    int no_of_frames, no_of_pages, frames[10], pages[30], temp[10], flag1, flag2, flag3, i, j, k, pos, max, faults = 0;
    printf("Enter number of frames: ");
    scanf("%d", &no_of_frames);
    
    printf("Enter number of pages: ");
    scanf("%d", &no_of_pages);
    
    printf("Enter page reference string: ");
    
    for(i = 0; i < no_of_pages; ++i){
        scanf("%d", &pages[i]);
    }
    
    for(i = 0; i < no_of_frames; ++i){
        frames[i] = -1;
    }
    
    for(i = 0; i < no_of_pages; ++i){
        flag1 = flag2 = 0;
        
        for(j = 0; j < no_of_frames; ++j){
            if(frames[j] == pages[i]){
                   flag1 = flag2 = 1;
                   break;
               }
        }
        
        if(flag1 == 0){
            for(j = 0; j < no_of_frames; ++j){
                if(frames[j] == -1){
                    faults++;
                    frames[j] = pages[i];
                    flag2 = 1;
                    break;
                }
            }    
        }
        
        if(flag2 == 0){
         flag3 =0;
        
            for(j = 0; j < no_of_frames; ++j){
             temp[j] = -1;
            
             for(k = i + 1; k < no_of_pages; ++k){
             if(frames[j] == pages[k]){
             temp[j] = k;
             break;
             }
             }
            }
            
            for(j = 0; j < no_of_frames; ++j){
             if(temp[j] == -1){
             pos = j;
             flag3 = 1;
             break;
             }
            }
            
            if(flag3 ==0){
             max = temp[0];
             pos = 0;
            
             for(j = 1; j < no_of_frames; ++j){
             if(temp[j] > max){
             max = temp[j];
             pos = j;
             }
             }            
            }
frames[pos] = pages[i];
faults++;
        }
        
        printf("\n");
        
        for(j = 0; j < no_of_frames; ++j){
            printf("%d\t", frames[j]);
        }
    }
    
    printf("\n\nTotal Page Faults = %d", faults);
    
    return 0;
}
