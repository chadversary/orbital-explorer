/*
 * This file is part of the Electron Orbital Explorer. The Electron
 * Orbital Explorer is distributed under the Simplified BSD License
 * (also called the "BSD 2-Clause License"), in hopes that these
 * rendering techniques might be used by other programmers in
 * applications such as scientific visualization, video gaming, and so
 * on. If you find value in this software and use its technologies for
 * another purpose, I would love to hear back from you at bjthinks (at)
 * gmail (dot) com. If you improve this software and agree to release
 * your modifications under the below license, I encourage you to fork
 * the development tree on github and push your modifications. The
 * Electron Orbital Explorer's development URL is:
 * https://github.com/bjthinks/orbital-explorer
 * (This paragraph is not part of the software license and may be
 * removed.)
 *
 * Copyright (c) 2013, Brian W. Johnson
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * + Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * + Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef UTIL_HH
#define UTIL_HH

#include <map>
#include <iostream>
#include <sstream>
#include <stdexcept>

#ifdef __APPLE__
// This is really stupid. Apple's compiler generates a warning when
// using a NULL pointer in this way, so instead we use some arbitrary
// highly-aligned constant.
#define myoffsetof(type, member) (reinterpret_cast<char *>(&(reinterpret_cast<type *>(0x40000000)->member))-reinterpret_cast<char *>(0x40000000))
#else
#define myoffsetof(type, member) offsetof(type, member)
#endif

static const double pi = 3.141592653589793238;

double now();

template <typename T>
inline void clamp(T &x, T low, T high)
{
  if (x < low) x = low;
  if (x > high) x = high;
}

template <class K, class V>
inline std::map<K,V> singleton(const K &k, const V &v)
{
  std::map<K,V> m;
  m.insert(std::make_pair(k,v));
  return m;
}

class Uncopyable
{
public:
  Uncopyable() {}

private:
  Uncopyable(const Uncopyable &); // DO NOT DEFINE
  Uncopyable &operator=(const Uncopyable &); // DO NOT DEFINE
};

class FatalError : public std::runtime_error
{
public:
  FatalError(const char *msg, const char *f, int L)
    : std::runtime_error(msg),
      file(f), line(L)
  {}
  virtual const char *what() const throw()
  {
    std::ostringstream o;
    o << file << ":" << line << ": " << std::runtime_error::what();
    return o.str().c_str();
  }

private:
  const char *file;
  int line;
};

#define FATAL(x) throw FatalError((x), __FILE__, __LINE__)

#endif
