//
//  Board.m
//  Pente
//
//  Created by Thomas Rieck on 9/30/09.
//  Copyright 2009 Rieck Enterprises. All rights reserved.
//

#import "Board.h"
#import "Entry.h"

@interface Board(private)
- (NSNumber*)key :(uint32_t)row :(uint32_t)col;
- (Entry*)lookup :(uint32_t)row :(uint32_t)col;
@end

@implementation Board

static Board *sharedBoardManager = nil;

+ (Board*)sharedManager
{
    @synchronized(self) {
        if (sharedBoardManager == nil) {
            [[self alloc] init]; 
        }
    }
    return sharedBoardManager;
}

- (id)init 
{
	if (self = [super init]) {
		rep = [[NSMapTable mapTableWithStrongToStrongObjects] retain];
	}
	return self;
}

+ (id)allocWithZone:(NSZone *)zone
{
    @synchronized(self) {
        if (sharedBoardManager == nil) {
            sharedBoardManager = [super allocWithZone:zone];
            return sharedBoardManager;  // assignment and return on first allocation
        }
    }
    return nil; //on subsequent allocation attempts return nil
}

- (id)copyWithZone:(NSZone *)zone
{
    return self;
}

- (id)retain
{
    return self;
}

- (unsigned)retainCount
{
    return UINT_MAX;  // denotes an object that cannot be released
}

- (void)release
{
    // do nothing
}

- (id)autorelease
{
    return self;
}

- (void)dealloc
{
	[rep removeAllObjects];
	[rep release];
	[super dealloc];
}

- (void)setEntry:(uint32_t)row :(uint32_t)col :(uint32_t)type
{
	Entry *entry;
	NSNumber *key = [self key:row :col];
	
	if ((entry = [rep objectForKey:key]) == nil) {
		entry = [[Entry alloc]initWithCoords: row :col :type];
		[rep setObject:entry forKey:key];
	} else {
		[entry setType: type];
	}
	
}

- (void)clear
{
	[rep removeAllObjects];
}

- (void)remove:(uint32_t)row :(uint32_t)col
{
	NSNumber *key = [self key:row :col];
	[rep removeObjectForKey:key];
}

- (uint32_t) entry :(uint32_t)row :(uint32_t)col
{
	Entry *entry;
	if ((entry = [self lookup :row :col]) != nil) {
		return [entry type];
	}
	
	return ET_EMPTY;
}

- (NSEnumerator*)enumEntries
{
	return [rep objectEnumerator];
}

- (NSArray*)empty
{
	uint32_t i, j;
	NSMutableArray *array = [NSMutableArray array];
	Entry *entry;
	
	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			if ([self entry:i :j] == ET_EMPTY) {
				entry = [[Entry alloc]initWithCoords:i :j :ET_EMPTY];
				[array addObject:entry];
			}
		}
	}
	
	return array;
}

@end

@implementation Board(private)

- (NSNumber*)key :(uint32_t)row :(uint32_t)col
{
	uint32_t index = (row % BOARD_SIZE) * BOARD_SIZE + (col % BOARD_SIZE);
	return [NSNumber numberWithInt:index];
}

- (Entry*)lookup :(uint32_t)row :(uint32_t)col
{
	NSNumber *key = [self key:row :col];
	return [rep objectForKey:key];
}

@end
