//
//  Person.h
//  RaiseMan
//
//  Created by Thomas Rieck on Fri Mar 08 2002.
//  Copyright (c) 2001 Rieck Enterprises. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Person :
NSObject <NSCoding> {
	NSString *personName;
	float expectedRaise;
}
- (NSString *)personName;
- (void)setPersonName:
(NSString *)s;

- (float)expectedRaise;
- (void)setExpectedRaise:
(float)f;

@end
