//
//  CocoaQueue.h
//  Graph
//
//  Created by Thomas Rieck on Sun Mar 31 2002.
//  Copyright (c) 2001 Rieck Enterprises. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "queue.h"

@interface CocoaQueue :
    NSObject
{

    struct queue *myQueue;
}

- (id)init;
- (void)dealloc;
- (void)addObject:
    (id)anObject;
- (id)removeObject;
- (BOOL)isEmpty;

@end
