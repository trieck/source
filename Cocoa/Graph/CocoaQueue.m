//
//  CocoaQueue.m
//  Graph
//
//  Created by Thomas Rieck on Sun Mar 31 2002.
//  Copyright (c) 2001 Rieck Enterprises. All rights reserved.
//

#import "CocoaQueue.h"

@implementation CocoaQueue

- (id)init
{
	if (self = [super init]) {
		myQueue = qalloc();
	}
	
	return self;
}

- (void)dealloc
{
	if (myQueue) qfree(myQueue);
	[super dealloc];
}

- (void)addObject:(id)anObject
{
	[anObject retain];
	qput(myQueue, anObject);
}

- (id)removeObject
{
	id object = qget(myQueue);
	[object release];
	return object;
}

- (BOOL)isEmpty
{
	return qempty(myQueue) ? YES : NO;
}

@end
