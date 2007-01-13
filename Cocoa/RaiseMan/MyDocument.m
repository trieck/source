//
//  MyDocument.m
//  RaiseMan
//
//  Created by Thomas Rieck on Wed Mar 06 2002.
//  Copyright (c) 2001 Rieck Enterprises. All rights reserved.
//

#import "MyDocument.h"
#import "Person.h"

@implementation MyDocument

- (id)init
{
	if (self = [super init]) {
		employees = [[NSMutableArray alloc] init];
		[self createNewEmployee];
	}
	return self;
}

- (void)createNewEmployee
{
	Person *newEmployee = [[Person alloc] init];
	[employees addObject:newEmployee];
	[newEmployee release];
}

- (IBAction)newEmployee:(id)sender
{
	[self createNewEmployee];
	[self updateChangeCount:NSChangeDone];
	[self updateUI];
}

- (IBAction)deleteEmployee:(id)sender
{
	int row = [tableView selectedRow];
	if (row != -1) {
		[employees removeObjectAtIndex:row];
		[self updateChangeCount:NSChangeDone];
		[self updateUI];
	} else {
		NSBeep();
	}
}

- (void)updateUI
{
	[tableView reloadData];
	[deleteButton setEnabled: ([employees count] > 1)];
}

- (int)numberOfRowsInTableView:(NSTableView *)aTableView
{
	return [employees count];
}

- (id)tableView:(NSTableView *)aTableView
	objectValueForTableColumn:(NSTableColumn *)aTableColumn
	row:(int)rowIndex
{
	NSString *identifier = [aTableColumn identifier];
	Person *person = [employees objectAtIndex:rowIndex];
	return [person valueForKey:identifier];
}

- (void)tableView:(NSTableView *)aTableView
	setObjectValue:(id)anObject
	forTableColumn:(NSTableColumn*)aTableColumn
	row:(int)rowIndex
{
	NSString *identifier = [aTableColumn identifier];
	Person *person = [employees objectAtIndex:rowIndex];
	[person takeValue:anObject forKey:identifier];
	[self updateChangeCount:NSChangeDone];
}

- (NSString *)windowNibName
{
    // Override returning the nib file name of the document
    // If you need to use a subclass of NSWindowController or if your document supports multiple NSWindowControllers, 	// you should remove this method and override -makeWindowControllers instead.
    return @"MyDocument";
}

- (void)windowControllerDidLoadNib:(NSWindowController *) aController
{
    [super windowControllerDidLoadNib:aController];
	[self updateUI];
}

- (NSData *)dataRepresentationOfType:(NSString *)aType
{
	[tableView deselectAll:nil];
    return [NSArchiver archivedDataWithRootObject:employees];
}

- (BOOL)loadDataRepresentation:(NSData *)data ofType:(NSString *)aType
{
	// release the old array
	[employees release];
	employees = [[NSUnarchiver unarchiveObjectWithData:data] retain];
	
	// Update UI in case this is a revert
	[self updateUI];
	
    return YES;
}

- (void)dealloc
{
	[employees release];
	[super dealloc];
}

@end
