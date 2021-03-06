/*
* Copyright 2002,2008 Brian Bergstrand.
*
* Redistribution and use in source and binary forms, with or without modification, 
* are permitted provided that the following conditions are met:
*
* 1.	Redistributions of source code must retain the above copyright notice, this list of
*     conditions and the following disclaimer.
* 2.	Redistributions in binary form must reproduce the above copyright notice, this list of
*     conditions and the following disclaimer in the documentation and/or other materials provided
*     with the distribution.
* 3.	The name of the author may not be used to endorse or promote products derived from this
*     software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
* AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
* THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* $Id: BBNetUpdateAskController.m 1529 2008-03-17 15:46:55Z brian $
*/

#import "BBNetUpdateAskController.h"

static BBNetUpdateAskController *gInstance = nil;

@implementation BBNetUpdateAskController

+ (void)askUser:(NSString*)appName delagate:(BBNetUpdateVersionCheckController*)delagate
{
   if (!gInstance) {
      gInstance = [[BBNetUpdateAskController alloc] initWithWindowNibNameAndAppName:@"BBNetUpdateAsk"
         appName:appName];
      if (!gInstance) {
         NSBeep();
         return;
      }
      
      [gInstance setWindowFrameAutosaveName:@"BBNetUpdateAsk"];
   }
   
   gInstance->_delagate = delagate;
   
   [[gInstance window] makeKeyAndOrderFront:nil];
}

- (IBAction)cancel:(id)sender
{
   [[NSUserDefaults standardUserDefaults]
      setBool:(NSOnState == [boxDontAskAgain state]) forKey:@"BBNetUpdateDontAskConnect"];
   [_delagate close];
   
   [super close];
}

- (IBAction)connect:(id)sender
{
   [[NSUserDefaults standardUserDefaults]
      setBool:(NSOnState == [boxDontAskAgain state]) forKey:@"BBNetUpdateDontAskConnect"];
   [super close];
   
   [_delagate connect:self];
}

- (void)windowDidLoad
{
    [[self window] setTitle:[NSString stringWithFormat:@"%@ %@",
        [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleName"],
        NSLocalizedString(@"Software Update", @"")]];
}

- (id)initWithWindowNibNameAndAppName:(NSString*)nib appName:(NSString*)appName
{
   NSString *question;
   id instance = [super initWithWindowNibName:nib];
   
   if (!instance)
      return (nil);
   
   // Load the window
   (void)[super window];
   
   if (!appName)
      appName = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleName"];
   
   // Set our text fields
   question = [NSString stringWithFormat:
      NSLocalizedString(@"Check For Update?", @""),
      appName];
   
   [fieldTitle setStringValue:
      NSLocalizedString(@"Do you want to check the Internet for a new version of %@?", @"")];
   [fieldQuestion setStringValue:question];
   
   return (instance);
}

@end
