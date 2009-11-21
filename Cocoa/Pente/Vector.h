//
//  Vector.h
//  Pente
//
//  Created by Thomas Rieck on 9/30/09.
//  Copyright 2009 Rieck Enterprises. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#define VSIZE	(5)

@interface Vector :
NSObject {
	Point v[VSIZE];
}

- (Point)entry:
(uint32_t)index;
- (void)setEntry:
(uint32_t)index :
(uint32_t)m :
(uint32_t)n;

@end
