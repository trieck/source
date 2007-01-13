#import <Foundation/Foundation.h>
#import "LotteryEntry.h"

int main (int argc, const char * argv[]) {
    NSMutableArray *array;
    NSCalendarDate *now;
    LotteryEntry *entry;
    int i;
    
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    
    now = [[NSCalendarDate alloc] init];
    
    srandom(time(NULL));
    array = [[NSMutableArray alloc] init];
    
    for (i = 0; i < 10; i++) {
        entry = [[LotteryEntry alloc] init];
        
        // create a date / time object that is one week from now
        [entry setEntryDate: [now dateByAddingYears:0 
            months:0 days:(i * 7) hours:0 minutes:0
            seconds:0]];
            
        [array addObject: entry];
        
        [entry release];
    }
    
    NSLog(@"array = %@", array);
    
    [array release];
    [now release];
    [pool release];
    
    return 0;
}
