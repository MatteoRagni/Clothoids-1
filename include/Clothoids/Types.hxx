/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *    _       _       __  __     _   _                                             *
 *   /_\  _ _| |_ ___|  \/  |___| |_(_)___ _ _                                     *
 *  / _ \| ' \  _/ -_) |\/| / _ \  _| / _ \ ' \                                    *
 * /_/ \_\_||_\__\___|_|  |_\___/\__|_\___/_||_|                                   *
 *                           SRL - CONFIDENTIAL                                    *
 *                                                                                 *
 * Copyright 2022 AnteMotion SRL                                                   *
 *   All Rights Reserved.                                                          *
 *                                                                                 *
 * NOTICE:  All information contained herein is, and remains the property of       *
 * AnteMotion SRL and its suppliers, if any. The intellectual and technical        *
 * concepts contained herein are proprietary to AnteMotion SRL and its suppliers.  *
 * Dissemination of this information or reproduction of this material is strictly  *
 * forbidden unless prior written permission is obtained from AnteMotion SRL       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once

#include <istream>
#include <ostream>

#ifndef G2LIB_DEFAULT_REAL_TYPE
#define G2LIB_DEFAULT_REAL_TYPE double
#endif

#ifndef G2LIB_DEFAULT_INT_TYPE
#define G2LIB_DEFAULT_INT_TYPE int
#endif

#ifndef G2LIB_DEFAULT_OSTREAM_TYPE
#define G2LIB_DEFAULT_OSTREAM_TYPE std::basic_ostream<char>
#endif


#ifndef G2LIB_DEFAULT_ISTREAM_TYPE
#define G2LIB_DEFAULT_ISTREAM_TYPE std::basic_istream<char>
#endif

namespace G2lib {
  typedef G2LIB_DEFAULT_OSTREAM_TYPE ostream_type;
  typedef G2LIB_DEFAULT_ISTREAM_TYPE istream_type;
  typedef G2LIB_DEFAULT_REAL_TYPE real_type;
  typedef G2LIB_DEFAULT_INT_TYPE int_type;
}
