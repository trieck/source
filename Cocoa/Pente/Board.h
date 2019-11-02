//
//  Board.h
//  Pente
//
//  Created by Thomas Rieck on 9/30/09.
//  Copyright 2009 Thomas A. Rieck. All rights reserved.
//

#import <Cocoa/Cocoa.h>

/* size of board */
#define BOARD_SIZE		(19)
#define BOARD_ENTRIES	(BOARD_SIZE*BOARD_SIZE)

@interface Board :
    NSObject
{
    NSMapTable *rep;
}

- (uint32_t)entry:
    (uint32_t)row :
    (uint32_t)col;
- (void)remove:
    (uint32_t)row :
    (uint32_t)col;
- (void)setEntry:
    (uint32_t)row :
    (uint32_t)col :
    (uint32_t)type;
- (void)clear;
- (NSEnumerator*)enumEntries;
- (NSArray*)empty;

+ (Board*)sharedManager;

@end
