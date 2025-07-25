/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* Bool.hpp                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: July 19, 2025                                  \ \ \_/__ \_\ \_  __  */
/*                                                       \ \_\/\_\/\____\/\_\ */
/*                                                        \/_/\/_/\/____/\/_/ */
/*===----------------------------------------------------------------------===*/

/*
 * This source file is part of the CoreAlgorithm open source project.
 *
 * Copyright (c) 2024-2025 Fang Ling All Rights Reserved.
 *
 * Use of this source code is governed by the Apache License, Version 2.0
 * that can be found in the LICENSE file in the root of the source tree.
 * This source code may include problem descriptions from some online judges,
 * which have their own licensing terms.
 */

#ifndef Bool_hpp
#define Bool_hpp

#include "../Internal/_CoreAlgorithms.hpp"

/**
 * A value type whose instances are either `true` or `false`.
 */
class Bool {
  private: bool _value;

  /**
   * Creates an instance equal to the given Boolean value.
   *
   * - Parameter value: The Boolean value to copy.
   */
  public: Bool(bool value);

  /**
   * Toggles the Boolean variable's value.
   *
   * Use this method to toggle a Boolean value from `true` to `false` or from
   * `false` to `true`.
   *
   *     var b = Bool(true);
   *
   *     b.toggle()
   *     // b == false
   */
  public: func toggle() -> Void;

  public: operator bool() const;
};

#endif /* Bool_hpp */

/*===----------------------------------------------------------------------===*/
/*         ___                            ___                                 */
/*       /'___\                          /\_ \    __                          */
/*      /\ \__/   __      ___      __    \//\ \  /\_\    ___      __          */
/*      \ \ ,__\/'__`\  /' _ `\  /'_ `\    \ \ \ \/\ \ /' _ `\  /'_ `\        */
/*       \ \ \_/\ \L\.\_/\ \/\ \/\ \L\ \    \_\ \_\ \ \/\ \/\ \/\ \L\ \       */
/*        \ \_\\ \__/.\_\ \_\ \_\ \____ \   /\____\\ \_\ \_\ \_\ \____ \      */
/*         \/_/ \/__/\/_/\/_/\/_/\/___L\ \  \/____/ \/_/\/_/\/_/\/___L\ \     */
/*                                 /\____/                        /\____/     */
/*                                 \_/__/                         \_/__/      */
/*===----------------------------------------------------------------------===*/
