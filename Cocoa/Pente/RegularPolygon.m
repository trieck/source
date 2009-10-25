//
//  RegularPolygon.m
//	represents a regular polygon, inscribed in a unit circle with given number of sides
//  Pente
//
//  Created by Thomas Rieck on 10/2/09.
//  Copyright 2009 Rieck Enterprises. All rights reserved.
//

#import "RegularPolygon.h"

@implementation NSBezierPath (Polygons)

+ (NSBezierPath*)polygonWithSides:(uint32_t) sides
{	
	if (sides > 0) {
		float theta = M_PI * 2, angle; 
		NSBezierPath *path = [self bezierPath];
		angle = theta / sides;
		
		[path moveToPoint:NSMakePoint(1.0, 0)];  // start at a point on the circle
		
		while (--sides)  {
			theta -= angle;
			[path lineToPoint: NSMakePoint(cos(theta), sin(theta))];
		}
		
		[path closePath]; 
		
		return path;
	}
	
	return nil;
}

@end

