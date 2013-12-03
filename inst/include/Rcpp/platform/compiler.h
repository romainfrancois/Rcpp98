// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; indent-tabs-mode: nil; -*-
//
// compiler.h: Rcpp R/C++ interface class library -- check compiler
//
// Copyright (C) 2012 - 2013  Dirk Eddelbuettel and Romain Francois
//
// This file is part of Rcpp98.
//
// Rcpp98 is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Rcpp98 is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Rcpp98.  If not, see <http://www.gnu.org/licenses/>.

#ifndef Rcpp__platform__compiler_h
#define Rcpp__platform__compiler_h

#undef GOOD_COMPILER_FOR_RCPP
#if defined(__GNUC__) || defined(__SUNPRO_CC) || defined(__clang__) || defined(__INTEL_COMPILER)
#define GOOD_COMPILER_FOR_RCPP
#endif

#ifndef GOOD_COMPILER_FOR_RCPP
# error "This compiler is not supported"
#endif
        
// Check TR1 Headers
#if defined(__INTEL_COMPILER) || (defined(__GNUC__) && !defined(__clang__))
    #if defined(__GLIBCXX__)
        #if GCC_VERSION >= 40400 || ( GCC_VERSION >= 40201 && defined(__APPLE__) )
            #define HAS_TR1_UNORDERED_MAP
            #define HAS_TR1_UNORDERED_SET
        #endif
    #endif
#elif defined(__clang__)
    #if __cplusplus >= 201103L
        #if __has_include(<tr1/unordered_map>)
            #define HAS_TR1_UNORDERED_MAP
        #endif
        #if __has_include(<tr1/unordered_set>)
            #define HAS_TR1_UNORDERED_SET
        #endif
    #endif
#endif
  
#if defined(HAS_TR1_UNORDERED_MAP) && defined(HAS_TR1_UNORDERED_SET)
    #define HAS_TR1
#endif
     
#if defined(HAS_TR1_UNORDERED_MAP)
    #include <tr1/unordered_map>
    #define RCPP_UNORDERED_MAP std::tr1::unordered_map
#else
    #include <map>
    #define RCPP_UNORDERED_MAP std::map
#endif
#if defined(HAS_TR1_UNORDERED_SET)
    #include <tr1/unordered_set>
    #define RCPP_UNORDERED_SET std::tr1::unordered_set
#else
    #include <set>
    #define RCPP_UNORDERED_SET std::set
#endif

#if defined(__GNUC__) || defined(__clang__)
  #define RCPP_HAS_DEMANGLING
#endif

#endif
