//
//  hxy_tests.m
//  hxy_tests
//
//  Created by Fang Ling on 2023/11/25.
//

#import "hxy_tests.h"

#import "100.h"
#import "101.h"
#import "113.h"
#import "133.h"
#import "136.h"
#import "156.h"

#import "201.h"
#import "202.h"
#import "207.h"
#import "213.h"
#import "220.h"
#import "221.h"
#import "227.h"
#import "230.h"
#import "232.h"
#import "253.h"
#import "272.h"
#import "299.h"

#import "340.h"

#import "400.h"
#import "401.h"
#import "455.h"
#import "458.h"
#import "489.h"
#import "492.h"
#import "494.h"

#import "508.h"
#import "509.h"
#import "511.h"
#import "512.h"
#import "540.h"
#import "594.h"

#import "814.h"
#import "815.h"

#import "1225.h"

#import "1339.h"
#import "1368.h"

#import "1583.h"
#import "1584.h"
#import "1585.h"
#import "1586.h"
#import "1587.h"
#import "1588.h"
#import "1589.h"
#import "1590.h"
#import "1591.h"
#import "1592.h"
#import "1593.h"
#import "1594.h"
#import "1595.h"
#import "1596.h"
#import "1597.h"

#import "10018.h"
#import "10035.h"
#import "10038.h"
#import "10055.h"
#import "10071.h"
#import "10082.h"

#import "10300.h"
#import "10340.h"
#import "10391.h"

#import "10474.h"

#import "10763.h"
#import "10783.h"

#import "10815.h"

#import "10935.h"
#import "10970.h"

#import "11172.h"

#import "11292.h"

#import "11332.h"
#import "11388.h"

#import "11498.h"

#import "11547.h"

#import "11703.h"
#import "11727.h"

#import "11809.h"

#import "12096.h"

#import "12100.h"
#import "12108.h"

#import "12289.h"

#import "12412.h"

#import "12504.h"

#import "12626.h"

#import "12720.h"

#import "13178.h"

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

- (void)test_1 {
  general_test(main_100, 1, 100, 3);
  general_test(main_101, 1, 101, 5);
  general_test(main_113, 1, 113, 4);
  general_test(main_133, 1, 133, 3);
  general_test(main_136, 1, 136, 1);
  general_test(main_156, 1, 156, 3);
}

// MARK: - Volume 2

- (void)test_2 {
  general_test(main_201, 2, 201, 5);
  general_test(main_202, 2, 202, 5);
  general_test(main_207, 2, 207, 2);
  general_test(main_213, 2, 213, 6);
  general_test(main_220, 2, 220, 2);
  general_test(main_221, 2, 221, 2);
  general_test(main_227, 2, 227, 4);
  general_test(main_230, 2, 230, 4);
  general_test(main_232, 2, 232, 2);
  general_test(main_253, 2, 253, 3);
  general_test(main_272, 2, 272, 1);
  general_test(main_299, 2, 299, 6);
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

- (void)test_4 {
  general_test(main_400, 4, 400, 5);
  general_test(main_401, 4, 401, 1);
  general_test(main_455, 4, 455, 2);
  general_test(main_458, 4, 458, 3);
  general_test(main_489, 4, 489, 6 - 3); /* remove original cases: 1, 2, 5 */
  general_test(main_492, 4, 492, 8);
  general_test(main_494, 4, 494, 8);
}

// MARK: - Volume 5

- (void)test_5 {
  general_test(main_508, 5, 508, 1);
  general_test(main_509, 5, 509, 3);
  general_test(main_511, 5, 511, 1);
  general_test(main_512, 5, 512, 2);
  general_test(main_540, 5, 540, 4);
  general_test(main_594, 5, 594, 1);
}

// MARK: - Volume 8

- (void)test_8 {
  general_test(main_814, 8, 814, 3);
  general_test(main_815, 8, 815, 4);
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

// MARK: - Volume 13

- (void)test_1339 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 13 (1300-1399)/"];
  for (var i = 0; i < 2; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"1339.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_1339();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"1339.%d.out", i]
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

- (void)test_1368 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 13 (1300-1399)/"];
  for (var i = 0; i < 2; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"1368.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_1368();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"1368.%d.out", i]
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

- (void)test_15 {
  general_test(main_1583, 15, 1583, 1);
  general_test(main_1584, 15, 1584, 1);
  general_test(main_1585, 15, 1585, 1);
  general_test(main_1586, 15, 1586, 1);
  general_test(main_1587, 15, 1587, 4);
  general_test(main_1588, 15, 1588, 3);
  general_test(main_1589, 15, 1589, 6);
  general_test(main_1590, 15, 1590, 3);
  general_test(main_1591, 15, 1591, 2);
  general_test(main_1592, 15, 1592, 5);
  general_test(main_1593, 15, 1593, 4);
  general_test(main_1594, 15, 1594, 4);
  general_test(main_1595, 15, 1595, 7);
  general_test(main_1596, 15, 1596, 4);
  general_test(main_1597, 15, 1597, 5);
}

// MARK: - Volume 100

- (void)test_10018 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 100 (10000-10099)/"];
  for (var i = 0; i < 4; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"10018.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_10018();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"10018.%d.out", i]
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

- (void)test_10035 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 100 (10000-10099)/"];
  for (var i = 0; i < 4; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"10035.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_10035();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"10035.%d.out", i]
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

- (void)test_10038 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 100 (10000-10099)/"];
  for (var i = 0; i < 5; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"10038.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_10038();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"10038.%d.out", i]
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

// MARK: - Volume 103

- (void)test_103 {
  general_test(main_10300, 103, 10300, 5);
  general_test(main_10340, 103, 10340, 4);
  general_test(main_10391, 103, 10391, 8);
}

// MARK: - Volume 104

- (void)test_10474 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 104 (10400-10499)/"];
  for (var i = 0; i < 2; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"10474.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_10474();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"10474.%d.out", i]
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

// MARK: - Volume 107

- (void)test_107 {
  general_test(main_10763, 107, 10763, 8);
  general_test(main_10783, 107, 10783, 5);
}

// MARK: - Volume 108

- (void)test_10815 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 108 (10800-10899)/"];
  for (var i = 0; i < 9; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"10815.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_10815();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"10815.%d.out", i]
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

// MARK: - Volume 109

- (void)test_109 {
  general_test(main_10935, 109, 10935, 5);
  general_test(main_10970, 109, 10970, 4);
}

// MARK: - Volume 111

- (void)test_11172 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 111 (11100-11199)/"];
  for (var i = 0; i < 4; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"11172.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_11172();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"11172.%d.out", i]
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

// MARK: - Volume 113

- (void)test_113 {
  general_test(main_11332, 113, 11332, 6);
  general_test(main_11388, 113, 11388, 4);
}

// MARK: - Volume 114

- (void)test_11498 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 114 (11400-11499)/"];
  for (var i = 0; i < 5; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"11498.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_11498();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"11498.%d.out", i]
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

// MARK: - Volume 115

- (void)test_11547 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 115 (11500-11599)/"];
  for (var i = 0; i < 3; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"11547.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_11547();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"11547.%d.out", i]
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

// MARK: - Volume 117

- (void)test_117 {
  general_test(main_11703, 117, 11703, 3);
  general_test(main_11727, 117, 11727, 5);
}

// MARK: - Volume 118

- (void)test_11809 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 118 (11800-11899)/"];
  for (var i = 0; i < 4; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"11809.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_11809();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"11809.%d.out", i]
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

// MARK: - Volume 120

- (void)test_12096 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 120 (12000-12099)/"];
  for (var i = 0; i < 3; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"12096.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_12096();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"12096.%d.out", i]
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

// MARK: - Volume 121

- (void) test_121 {
  general_test(main_12100, 121, 12100, 6);
  general_test(main_12108, 121, 12108, 2);
}

// MARK: - Volume 122

- (void) test_122 {
  general_test(main_12289, 122, 12289, 3);
}

// MARK: - Volume 124

- (void)test_12412 {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString: @"Volume 124 (12400-12499)/"];
  for (var i = 0; i < 2; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [NSString stringWithFormat: @"12412.%d.in", i]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    main_12412();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"12412.%d.out", i]
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

// MARK: - Volume 125

- (void) test_125 {
  general_test(main_12504, 125, 12504, 3);
}

// MARK: - Volume 126

- (void) test_126 {
  general_test(main_12626, 126, 12626, 4);
}

// MARK: - Volume 127

- (void) test_12720 {
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
    freopen("/tmp/hxy.out", "w", stdout);
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
      stringWithContentsOfFile: @"/tmp/hxy.out"
      encoding: NSUTF8StringEncoding
      error: nil
    ];
    XCTAssertEqualObjects(sol, out);
  }
}

// MARK: - Volume 131

- (void)test_131 {
  general_test(main_13178, 131, 13178, 4);
}

void general_test(void (*test_main)(void), int volume, int problem, int cases) {
  NSString* path = @IO_DATA_PATH;
  path = [path stringByAppendingString:
          [
            NSString stringWithFormat:
            @"Volume %d (%d00-%d99)/",
            volume,
            volume,
            volume
          ]
  ];
  for (var i = 0; i < cases; i += 1) {
    freopen(
      [[path
        stringByAppendingString: [
          NSString stringWithFormat: @"%d.%d.in", problem, i
        ]
       ] UTF8String
      ],
      "r",
      stdin
    );
    freopen("/tmp/hxy.out", "w", stdout);
    test_main();
    fclose(stdin);
    fclose(stdout);
    var out = [
      NSString
      stringWithContentsOfFile: [
        path stringByAppendingString:
          [NSString stringWithFormat: @"%d.%d.out", problem, i]
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

@end
