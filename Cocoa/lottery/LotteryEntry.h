//
//  LotteryEntry.h
//  lottery
//
//  Created by Thomas Rieck on Sun Mar 03 2002.
//  Copyright (c) 2001 Rieck Enterprises. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface LotteryEntry :
NSObject {
	NSCalendarDate *entryDate;
	int firstNumber;
	int secondNumber;
}
- (void)setEntryDate:
(NSCalendarDate *)date;
- (NSCalendarDate *)entryDate;
- (int)firstNumber;
- (int)secondNumber;

@end
