//
//  Person.m
//  RaiseMan
//
//  Created by Thomas Rieck on Fri Mar 08 2002.
//  Copyright (c) 2001 Rieck Enterprises. All rights reserved.
//

#import "Person.h"

@implementation Person

// init method makes sure that the instance variables are
// initialized to default values
- (id)init
{
	if (self = [super init]) {
		// call accessor methods with default values to
		// initialize the instance variables
		[self setPersonName:@"New Employee"];
		[self setExpectedRaise: 0.0];
	}
	return self;
}

- (id)initWithCoder:(NSCoder *)coder
{
	// does not call designated initializer
	// initWithCoder is an exception to initializer rules
	if (self = [super init]) {
		[self setPersonName:[coder decodeObject]];
		[coder decodeValueOfObjCType:@encode(float) at:&expectedRaise];
	}
	return self;
}

- (NSString *)personName
{
	return personName;
}

- (void)setPersonName:(NSString *)s
{
	[s retain];
	[personName release];
	personName = s;
}

- (float)expectedRaise
{
	return expectedRaise;
}

- (void)setExpectedRaise:(float)f
{
	expectedRaise = f;
}

- (void)dealloc
{
	NSLog(@"Deallocating %@", personName);
	[personName release];
	[super dealloc];
}

- (void)unableToSetNilForKey:(NSString*)key
{
	if ([key isEqual:@"expectedRaise"]) {
		[self setExpectedRaise:0.0];
	} else {
		[super unableToSetNilForKey:key];
	}
}

- (void)encodeWithCoder:(NSCoder *)coder
{
	[coder encodeObject:personName];
	[coder encodeValueOfObjCType:@encode(float) at:&expectedRaise];
}




@end
