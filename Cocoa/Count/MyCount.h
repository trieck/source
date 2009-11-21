/* MyCount */

#import <Cocoa/Cocoa.h>

@interface MyCount :
NSObject {
	IBOutlet id inputText;
	IBOutlet id outputText;
}
- (IBAction)setCount:
(id)sender;
@end
