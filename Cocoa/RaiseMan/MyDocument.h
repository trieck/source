//
//  MyDocument.h
//  RaiseMan
//
//  Created by Thomas Rieck on Wed Mar 06 2002.
//  Copyright (c) 2001 Rieck Enterprises. All rights reserved.
//


#import <Cocoa/Cocoa.h>

@interface MyDocument :
NSDocument {
	NSMutableArray *employees;
	IBOutlet NSTableView *tableView;
	IBOutlet NSButton *deleteButton;
}

// Action methods
- (IBAction)deleteEmployee:
(id)sender;
- (IBAction)newEmployee:
(id)sender;

// Data source methods
- (int)numberOfRowsInTableView:
(NSTableView *)aTableView;
- (id)tableView:
(NSTableView *)aTableView
objectValueForTableColumn:
(NSTableColumn *)aTableColumn
row:
(int)rowIndex;
- (void)tableView:
(NSTableView *)aTableView
setObjectValue:
(id)anObject
forTableColumn:
(NSTableColumn *)aTableColumn
row:
(int)rowIndex;

// Private methods
- (void)createNewEmployee;
- (void)updateUI;

@end
