//
//  hxy_tests.m
//  hxy_tests
//
//  Created by Fang Ling on 2023/11/25.
//

#import "hxy_tests.h"

#import "272.c"

#import <XCTest/XCTest.h>
#import <stdio.h>

/* 
 * IO_DATA_PATH:
 * "/.../.../repo/IO Data Volumes/"
 */

@interface hxy_tests : XCTestCase

@end

@implementation hxy_tests

- (void)setUp {
  // Put setup code here. This method is called before the invocation of each
  // test method in the class.
}

- (void)tearDown {
  // Put teardown code here. This method is called after the invocation of each
  // test method in the class.
}

- (void)test_272 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 2 (200-299)/"];
  
  char buf[1024];
  freopen([[path stringByAppendingString: @"272.0.in"] UTF8String], "r", stdin);
  freopen("/dev/null", "a", stdout);
  setbuf(stdout, buf);
  main_272();
  NSString* out = [
    NSString
      stringWithContentsOfFile: [path stringByAppendingString: @"272.0.out"]
      encoding: NSUTF8StringEncoding
      error: nil
  ];
  XCTAssertEqualObjects(
    out,
    [NSString stringWithCString: buf encoding: NSUTF8StringEncoding]
  );
  
  fclose(stdin);
  fclose(stdout);
}

@end
