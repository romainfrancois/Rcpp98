// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; tab-width: 8 -*-
/* :tabSize=4:indentSize=4:noTabs=false:folding=explicit:collapseFolds=1: */
//
// is_module_object.h: Rcpp R/C++ interface class library -- 
//
// Copyright (C) 2013 Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp__traits__is_module_object__h
#define Rcpp__traits__is_module_object__h

namespace Rcpp{
namespace traits{
      
	template <typename T> struct is_module_object : 
		public integral_constant<bool,
			same_type< typename r_type_traits<T>::r_category, r_type_module_object_tag >::value                ||
			same_type< typename r_type_traits<T>::r_category, r_type_module_object_pointer_tag >::value        ||
			same_type< typename r_type_traits<T>::r_category, r_type_module_object_const_pointer_tag >::value  ||
			same_type< typename r_type_traits<T>::r_category, r_type_module_object_reference_tag >::value      ||
			same_type< typename r_type_traits<T>::r_category, r_type_module_object_const_reference_tag >::value
		>{} ;

} // traits
} // Rcpp

#endif
