//
//  Entry.h
//  Pente
//
//  Created by Thomas Rieck on 10/4/09.
//  Copyright 2009 Rieck Enterprises. All rights reserved.
//

#import <Cocoa/Cocoa.h>

/* entry types */
enum {
    ET_EMPTY = 0,
    ET_PLAYER_ONE,
    ET_PLAYER_TWO
};

@interface Entry :
NSObject {
    Point pt;
    uint32 type;
}

- (id)initWithCoords :
(uint32_t)x :
(uint32_t)y :
(uint32_t)type;
- (Point) where;
- (uint32_t) type;
- (void) setType :
(uint32_t)type;

@end
