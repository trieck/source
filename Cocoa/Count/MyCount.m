#import "MyCount.h"

@implementation MyCount

- (IBAction)setCount:(id)sender
{
	NSString *input = [inputText stringValue];
	NSString *output = [NSString stringWithFormat:@"%@ has %d letters.",
		input, [input length]];
		
	[outputText setStringValue:output];		
}

@end
