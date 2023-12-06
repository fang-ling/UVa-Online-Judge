//
//  hxy_tests.m
//  hxy_tests
//
//  Created by Fang Ling on 2023/11/25.
//

#import "hxy_tests.h"

#import "100.h"

#import "227.h"
#import "232.h"
#import "272.h"

#import "340.h"

#import "401.h"
#import "455.h"

#import "594.h"

#import "1225.h"

#import "1583.h"
#import "1584.h"
#import "1585.h"
#import "1586.h"

#import "10055.h"
#import "10071.h"
#import "10082.h"

#import "11292.h"

#import "12720.h"

#import <XCTest/XCTest.h>
#import <stdio.h>

#define var __auto_type

/*
 * IO_DATA_PATH:
 * "/.../.../repo/IO Data Volumes/"
 */

@interface hxy_tests : XCTestCase

@end

@implementation hxy_tests

// MARK: - Volume 1

- (void)test_100 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 1 (100-199)/"];
  for (var i = 0; i < 3; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"100.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_100();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"100.%d.out", i]
      ]
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    var sol = [
      NSString
      stringWithContentsOfFile: @"/tmp/hxy.out"
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    XCTAssertEqualObjects(sol, out);
  }
}

// MARK: - Volume 2

- (void)test_227 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 2 (200-299)/"];
  for (var i = 0; i < 4; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"227.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_227();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"227.%d.out", i]
      ]
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    var sol = [
      NSString
      stringWithContentsOfFile: @"/tmp/hxy.out"
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    XCTAssertEqualObjects(sol, out);
  }
}

- (void)test_232 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 2 (200-299)/"];
  for (var i = 0; i < 2; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"232.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_232();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"232.%d.out", i]
      ]
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    var sol = [
      NSString
      stringWithContentsOfFile: @"/tmp/hxy.out"
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    XCTAssertEqualObjects(sol, out);
  }
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
  for (var i = 0; i < 1; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"401.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_401();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"401.%d.out", i]
      ]
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    var sol = [
      NSString
      stringWithContentsOfFile: @"/tmp/hxy.out"
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    XCTAssertEqualObjects(sol, out);
  }
}

- (void)test_455 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 4 (400-499)/"];
  for (var i = 0; i < 2; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"455.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_455();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"455.%d.out", i]
      ]
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    var sol = [
      NSString
      stringWithContentsOfFile: @"/tmp/hxy.out"
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    XCTAssertEqualObjects(sol, out);
  }
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

// MARK: - Volume 12

- (void)test_1225 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 12 (1200-1299)/"];
  for (var i = 0; i < 1; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"1225.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_1225();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"1225.%d.out", i]
      ]
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    var sol = [
      NSString
      stringWithContentsOfFile: @"/tmp/hxy.out"
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    XCTAssertEqualObjects(sol, out);
  }
}

// MARK: - Volume 15

- (void)test_1583 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 15 (1500-1599)/"];
  for (var i = 0; i < 1; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"1583.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_1583();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"1583.%d.out", i]
      ]
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    var sol = [
      NSString
      stringWithContentsOfFile: @"/tmp/hxy.out"
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    XCTAssertEqualObjects(sol, out);
  }
}

- (void)test_1584 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 15 (1500-1599)/"];
  for (var i = 0; i < 1; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"1584.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_1584();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"1584.%d.out", i]
      ]
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    var sol = [
      NSString
      stringWithContentsOfFile: @"/tmp/hxy.out"
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    XCTAssertEqualObjects(sol, out);
  }
}

- (void)test_1585 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 15 (1500-1599)/"];
  for (var i = 0; i < 1; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"1585.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_1585();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"1585.%d.out", i]
      ]
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    var sol = [
      NSString
      stringWithContentsOfFile: @"/tmp/hxy.out"
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    XCTAssertEqualObjects(sol, out);
  }
}

- (void)test_1586 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 15 (1500-1599)/"];
  for (var i = 0; i < 1; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"1586.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_1586();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"1586.%d.out", i]
      ]
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    var sol = [
      NSString
      stringWithContentsOfFile: @"/tmp/hxy.out"
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    XCTAssertEqualObjects(sol, out);
  }
}

// MARK: - Volume 100

- (void)test_10055 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 100 (10000-10099)/"];
  for (var i = 0; i < 3; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"10055.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_10055();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"10055.%d.out", i]
      ]
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    var sol = [
      NSString
      stringWithContentsOfFile: @"/tmp/hxy.out"
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    XCTAssertEqualObjects(sol, out);
  }
}

- (void)test_10071 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 100 (10000-10099)/"];
  for (var i = 0; i < 1; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"10071.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_10071();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"10071.%d.out", i]
      ]
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    var sol = [
      NSString
      stringWithContentsOfFile: @"/tmp/hxy.out"
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    XCTAssertEqualObjects(sol, out);
  }
}

- (void)test_10082 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 100 (10000-10099)/"];
  for (var i = 0; i < 1; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"10082.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_10082();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"10082.%d.out", i]
      ]
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    var sol = [
      NSString
      stringWithContentsOfFile: @"/tmp/hxy.out"
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    XCTAssertEqualObjects(sol, out);
  }
}

// MARK: - Volume 112

- (void)test_11292 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 112 (11200-11299)/"];
  for (var i = 0; i < 5; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"11292.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_11292();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"11292.%d.out", i]
      ]
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    var sol = [
      NSString
      stringWithContentsOfFile: @"/tmp/hxy.out"
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    XCTAssertEqualObjects(sol, out);
  }
}

// MARK: - Volume 127

- (void)test_12720 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 127 (12700-12799)/"];
  for (var i = 0; i < 2; i += 1) {
    freopen(
      [[path 
        stringByAppendingString: [NSString stringWithFormat: @"12720.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/12720.out", "w", stdout);
    main_12720();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"12720.%d.out", i]
      ]
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    var sol = [
      NSString
      stringWithContentsOfFile: @"/tmp/12720.out"
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    XCTAssertEqualObjects(sol, out);
  }
}

@end
