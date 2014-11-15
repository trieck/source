/* AppController */

#import <Cocoa/Cocoa.h>
#import "Graph.h"
#import "GraphView.h"

@interface AppController :
NSObject {
    IBOutlet GraphView *myView;		// current view
    Graph *graph;					// graph
    Vertex *selected1, *selected2;	// currently selected vertices
}

- (Graph*)graph;
- (void)select:
(Vertex*)v;
- (void)deselect:
(Vertex*)v;
- (void)removeVertex:
(Vertex*)v;
- (void)selection:
(unsigned)flags atPoint:
(NSPoint)pt;

// Action methods
- (IBAction)clearGraph:
(id)sender;
- (IBAction)path:
(id)sender;
- (IBAction)shortestPath:
(id)sender;
- (IBAction)connect:
(id)sender;
- (IBAction)disconnect:
(id)sender;

@end
