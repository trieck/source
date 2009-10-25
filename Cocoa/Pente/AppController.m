#import "AppController.h"
#import "globals.h"

@interface AppController(private)

- (void) stalemate;
- (void) checkCaptures;
- (BOOL) checkWinner;

@end

@implementation AppController
- (IBAction)newGame:(id)sender {
    int answer = NSRunAlertPanel(@"New Game", @"Are you sure?",
								 @"New Game", @"Cancel", nil);
	
	if (answer == NSAlertDefaultReturn) {
		[board clear];
		[view setNeedsDisplay:YES];
	}
}

- (id)init
{
	if (self = [super init]) {
		board = [Board sharedManager];
		machine = [[Machine alloc] init];
	}
	return self;
}

- (void)dealloc
{
	[machine release];
	[board release];
	[super dealloc];
}

-(BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication
{
	return YES;
}

- (Point)move
{
	Point pt = NIL_MOVE;
	
	[self checkCaptures];	
	
	if (![self checkWinner]) {
		if (isNilMove(pt = [machine move])) {
			[self stalemate];
		} else {
			[self checkCaptures];
			[self checkWinner];
		}
	}
	
	return pt;
}

@end

@implementation AppController(private)

- (void) stalemate
{
	int answer = NSRunAlertPanel(@"Stalemate", @"Play Again?",
								 @"Yes", @"No", nil);
	
	if (answer == NSAlertDefaultReturn) {
		[board clear];
		[view setNeedsDisplay:YES];
	}
}

- (void) checkCaptures
{
}

- (BOOL) checkWinner
{
	NSInteger result;
	Vector *vector;
	uint32_t winner;
	
	if ((vector = [machine winner:&winner]) != nil) {
		NSString *text = winner == ET_PLAYER_ONE ?
			@"You Win!" : @"I Win!";
		[view setWinner:vector];
		[view display];
		result = NSRunAlertPanel(text, @"Play Again?",
								 @"New Game", @"Quit", nil);
		if (result == NSAlertDefaultReturn) {
			[board clear];
			[view setWinner:nil];
			[view setNeedsDisplay:YES];
		} else {
			[NSApp terminate:self];	// quit
		}
		
		return YES;
	}
	
	return NO;
}

@end
