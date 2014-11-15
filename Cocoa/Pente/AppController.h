#import <Cocoa/Cocoa.h>
#import "View.h"
#import "Board.h"
#import "Entry.h"
#import "Machine.h"

@interface AppController :
NSObject {
    IBOutlet View *view;
    Board *board;
    Machine *machine;
}
- (IBAction)newGame:
(id)sender;

- (Point)move;

@end
