//
//  RegularPolygon.h
//	represents a regular polygon, inscribed in a unit circle with given number of sides
//  Pente
//
//  Created by Thomas Rieck on 10/2/09.
//  Copyright 2009 Rieck Enterprises. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSBezierPath (Polygons)

+ (NSBezierPath *) polygonWithSides:
    (uint32_t) sides;

@end
