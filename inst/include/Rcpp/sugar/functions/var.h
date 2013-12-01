// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; tab-width: 8 -*-
//
// var.h: Rcpp R/C++ interface class library -- var
//
// Copyright (C) 2011 Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp__sugar__var_h
#define Rcpp__sugar__var_h

namespace Rcpp{
namespace sugar{

template <int RTYPE, bool NA, typename T>
class Var : public Lazy< typename Rcpp::traits::storage_type<RTYPE>::type , Var<RTYPE,NA,T> > {
public:
	typedef typename Rcpp::VectorBase<RTYPE,NA,T> VEC_TYPE ;
	typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
		                                             
	Var( const VEC_TYPE& object_ ) : object(object_){}
	
	STORAGE get() const{
	    STORAGE m = mean(object).get() ;
		Minus_Vector_Primitive<RTYPE,NA,T> mm( object, m) ;
		STORAGE ssq  = sum( pow(mm,2.0) ).get() ;
	    return ssq / (object.size() - 1 ) ;    
	}
	
private:
	const VEC_TYPE& object ;
} ;

} // sugar

template <bool NA, typename T>
inline sugar::Var<REALSXP,NA,T> var( const VectorBase<REALSXP,NA,T>& t){
	return sugar::Var<REALSXP,NA,T>( t ) ;
}


} // Rcpp
#endif

