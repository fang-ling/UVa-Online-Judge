//
//  hxy_tests.m
//  hxy_tests
//
//  Created by Fang Ling on 2023/11/25.
//

#import "hxy_tests.h"

#import "272.h"

#import "340.h"

#import "401.h"

#import "594.h"

#import "10082.h"

#import <XCTest/XCTest.h>
#import <stdio.h>

/* 
 * IO_DATA_PATH:
 * "/.../.../repo/IO Data Volumes/"
 */

@interface hxy_tests : XCTestCase

@end

@implementation hxy_tests
// MARK: - Volume 2

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

// MARK: - Volume 3

- (void)test_340 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 3 (300-399)/"];
  
  char buf[1024];
  freopen(
    [[path stringByAppendingString: @"340.0.in"] UTF8String],
    "r",
    stdin
  );
  freopen("/dev/null", "a", stdout);
  setbuf(stdout, buf);
  main_340();
  NSString* out = [
    NSString
      stringWithContentsOfFile: [path stringByAppendingString: @"340.0.out"]
      encoding: NSUTF8StringEncoding
      error: nil
  ];
  XCTAssertEqual(strncmp(buf, [out UTF8String], strlen([out UTF8String])), 0);
  
  fclose(stdin);
  fclose(stdout);
}

// MARK: - Volume 4

- (void)test_401 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 4 (400-499)/"];
  
  char buf[1024];
  freopen(
    [[path stringByAppendingString: @"401.0.in"] UTF8String],
    "r",
    stdin
  );
  freopen("/dev/null", "a", stdout);
  setbuf(stdout, buf);
  main_401();
  NSString* out = [
    NSString
      stringWithContentsOfFile: [path stringByAppendingString: @"401.0.out"]
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

// MARK: - Volume 5

- (void)test_594 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 5 (500-599)/"];
  
  char buf[1024];
  freopen(
    [[path stringByAppendingString: @"594.0.in"] UTF8String],
    "r",
    stdin
  );
  freopen("/dev/null", "a", stdout);
  setbuf(stdout, buf);
  main_594();
  NSString* out = [
    NSString
      stringWithContentsOfFile: [path stringByAppendingString: @"594.0.out"]
      encoding: NSUTF8StringEncoding
      error: nil
  ];
  XCTAssertEqual(strncmp(buf, [out UTF8String], strlen([out UTF8String])), 0);
  
  fclose(stdin);
  fclose(stdout);
}

// MARK: - Volume 100

- (void)test_10082 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 100 (10000-10099)/"];
  
  char buf[1024];
  freopen(
    [[path stringByAppendingString: @"10082.0.in"] UTF8String],
    "r",
    stdin
  );
  freopen("/dev/null", "a", stdout);
  setbuf(stdout, buf);
  main_10082();
  NSString* out = [
    NSString
      stringWithContentsOfFile: [path stringByAppendingString: @"10082.0.out"]
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
