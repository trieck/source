//
//  LotteryEntry.m
//  lottery
//
//  Created by Thomas Rieck on Sun Mar 03 2002.
//  Copyright (c) 2001 Rieck Enterprises. All rights reserved.
//

#import "LotteryEntry.h"

@implementation LotteryEntry

/* 
 * initialize
 */
- (id)init
{
    [super init];
    firstNumber = random() % 100 + 1;
    secondNumber = random() % 100 + 1;
    return self;
}

/*
 * set entry date
 */
- (void)setEntryDate:(NSCalendarDate *)date
{
    [date retain];
    [entryDate release];
    [date setCalendarFormat:@"%b %d, %Y"];
    entryDate = date;
}

/*
 * return the entry date
 */
- (NSCalendarDate *)entryDate
{
    return entryDate;
}

/*
 * return the first number
 */
- (int)firstNumber
{
    return firstNumber;
}
   
/*
 * return the second number
 */
- (int)secondNumber
{
    return secondNumber;
}

- (void)dealloc
{
    NSLog(@"Destroying %@", self);
    [entryDate release];
    [super dealloc];	
}

- (NSString *)description
{
    return [NSString stringWithFormat:@"%@ = %d and %d",
        entryDate, firstNumber, secondNumber];
}

@end
