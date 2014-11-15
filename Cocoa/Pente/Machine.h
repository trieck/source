//
//  Machine.h
//  Pente
//
//  Created by Thomas Rieck on 9/30/09.
//  Copyright 2009 Thomas A. Rieck. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "Board.h"
#import "Vector.h"

@interface Machine :
NSObject {
    /* all initially feasible vectors */
    NSMutableArray *vectors;
    Board *board;
}

- (Point)move;
- (Vector*)winner:
(uint32_t *)type;

@end
