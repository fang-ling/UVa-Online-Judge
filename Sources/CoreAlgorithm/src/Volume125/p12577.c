/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p12577.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: December 10, 2024                              \ \ \_/__ \_\ \_  __  */
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

/*
 * 12577 Hajj-e-Akbar
 *
 * Labayk Allahuma Labayk. Labayk La shareeka laka Labayk. Innal hamda wannimata
 * laka wal mulk. La shareeka Lak
 *
 * (Here I am at your service, oh Lord, here I am - here I am. No partner do you
 * have. Here I am. Truly, the praise and the favor are yours, and the dominion.
 * No partner do you have.)
 *
 * These are the words chanted by some two million people from world heading, as
 * if pulled by a magnet, to one single spot on Earth. As has happened every
 * year for 14 centuries, Muslim pilgrims gather in Makkah to perform rituals
 * based on those conducted by the Prophet Muhammad during his last visit to the
 * city.
 *
 * Performing these rituals, known as the Hajj, is the fifth pillar of Islam and
 * the most significant manifestation of Islamic faith and unity. Undertaking
 * the Hajj at least once is a duty for Muslims who are physically and
 * financially able to make the journey to Makkah. The emphasis on financial
 * ability is meant to ensure that a Muslim takes care of his family first. The
 * requirement that a Muslim be healthy and physically capable of undertaking
 * the pilgrimage is intended to exempt those who cannot endure the rigors of
 * extended travel.
 *
 * The pilgrimage is the religious high point of a Muslim’s life and an event
 * that every Muslim dreams of undertaking. Umrah, the lesser pilgrimage, can be
 * undertaken at any time of the year; Hajj, however, is performed during a
 * five-day period from the ninth through the thirteenth of Dhu Al-Hijjah, the
 * twelfth month of the Muslim lunar calendar.
 *
 * It is generally presumed that the Hajj performed on Friday is called
 * 'Hajj-e-Akbar' and it is a superior kind of Hajj as compared with the Hajj
 * performed on other days of the week.
 *
 * But, the correct meaning of the term, as explained by a large number of the
 * commentators of the Holy Quran is that the Umrah, which can be performed at
 * any time throughout the year, was generally called 'Hajj-e-Asghar' (the minor
 * Hajj). In order to distinguish hajj from Umrah the former was named
 * 'Hajj-e-Akbar' (the greater hajj). Therefore, each and every hajj is
 * Hajj-e-Akbar, no matter whether it is performed on Friday or on any other
 * day. The word 'Akbar' (greater) is used only to distinguish it from Umrah
 * which is a minor Hajj.
 *
 * Input:
 * There will be several lines in the input terminated with a line containing a
 * single '*'. This last line should not be processed. Each of the lines will
 * contain either Hajj or Umrah.
 *
 * Output:
 * For each line of the input, output either 'Hajj-e-Akbar' or 'Hajj-e-Asghar'
 * in separate lines without quotations. For exact format refer to the sample.
 *
 * Solution:
 * Print 'Hajj-e-Akbar' if the input is 'Hajj', otherwise,
 * print 'Hajj-e-Asghar'.
 */

#include "Volume125/p12577.h"

Void p12577_main() {
  Int8 buffer[8];

  var case_number = 1;
  while (scanf("%s", buffer) == 1 && buffer[0] != '*') {
    let count = strlen(buffer);

    printf("Case %d: Hajj-e-%s\n", case_number, count < 5 ? "Akbar" : "Asghar");
    case_number += 1;
  }
}

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
