#import "AppController.h"
#import "Edge.h"

@implementation AppController

- (id)init
{
	if (self = [super init]) {
		graph = [[Graph alloc] init];
		selected1 = selected2 = nil;
	}
	return self;
}

- (BOOL)validateMenuItem:(NSMenuItem*)menuItem
{
	if ([menuItem action] == @selector(connect:)) {
		if (selected1 == nil || selected2 == nil)
			return NO;	// no two selected
			
		if ([selected1 isEdge:selected2])
			return NO;	// already an edge
	} else if ([menuItem action] == @selector(disconnect:)) {
		if (selected1 == nil || selected2 == nil)
			return NO;	// no two selected
			
		if (![selected1 isEdge:selected2])
			return NO;	// no edge
	} else if ([menuItem action] == @selector(clearGraph:)) {
		if ([graph vertices] == 0)
			return NO;	// no graph
	} else if ([menuItem action] == @selector(path:)) {
		if (selected1 == nil || selected2 == nil)
			return NO;	// no two selected
	} else if ([menuItem action] == @selector(shortestPath:)) {
		if (selected1 == nil || selected2 == nil)
			return NO;	// no two selected
	}
			
	return YES;
}

- (void)dealloc
{
	[graph release];
	[super dealloc];
}

- (Graph*)graph
{
	return graph;
}

- (void)select:(Vertex*)v
{
	if (selected1 == nil) {			// ensure selected2 is most recent
		if (selected2 != nil)
			selected1 = selected2;
		selected2 = v;
	} else if (selected2 == nil) {
		selected2 = v;
	} else {						// no slot
		[selected2 select];			// deselect most recently selected
		selected2 = v;				// reassign most recently selected
	}
		
	[v select];
}

- (void)deselect:(Vertex*)v
{
	if ([selected1 isEqual:v]) 
		selected1 = nil;
	else if ([selected2 isEqual:v])
		selected2 = nil;
	else return; // not contained
	
	[v select];	// will deselect
}

- (void)removeVertex:(Vertex*)v
{		
	[graph removeVertex:v];
}

- (IBAction)clearGraph:(id)sender
{
	int answer = NSRunAlertPanel(@"Clear Graph", @"Are you sure?",
		@"Clear Graph", @"Cancel", nil);
	
	if (answer == NSAlertDefaultReturn) {
		selected1 = selected2 = nil;
		[graph clear];
		[myView setNeedsDisplay:YES];
	}
}

- (IBAction)connect:(id)sender
{
	[selected1 setEdge:selected2];
	[selected2 setEdge:selected1];
	[myView setNeedsDisplay:YES];
}

- (IBAction)disconnect:(id)sender
{
	[selected1 removeEdge:selected2];
	[selected2 removeEdge:selected1];
	[myView setNeedsDisplay:YES];
}

- (IBAction)path:(id)sender
{
	int p = [graph path:selected1 toVertex:selected2];
	
	NSString *title = @"Find a path";
	NSString *subject;
	
	subject = p ? @"A path exists!" :  @"No path exists!";
	
	NSRunAlertPanel(title, subject, nil, nil, nil);
}

- (IBAction)shortestPath:(id)sender
{
	Edge *edge = [[Edge alloc] initWithVertex:selected1 toVertex:selected2];
	
	[graph bfs:edge];
	
	[edge release];
}

- (void)selection:(unsigned)flags atPoint:(NSPoint)pt
{
	Vertex *vertex = [graph vertex:pt];
	if (vertex == nil) {
		[graph addVertex:pt];
		return;
	}
	
	if (flags & NSShiftKeyMask) {	// is the shift key down?
		if ([vertex selected])		// is the vertex selected?
			[self deselect:vertex];	// deselect it
		[self removeVertex:vertex];	// remove it
	} else {
		if ([vertex selected])		// is the vertex selected?
			[self deselect:vertex];	// deselect it
		else [self select:vertex];	// select it
	}
}

@end
