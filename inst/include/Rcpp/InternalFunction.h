// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; tab-width: 8 -*-
//
// InternalFunction.h: Rcpp R/C++ interface class library -- exposing C++ functions
//
// Copyright (C) 2010 - 2013 Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp_InternalFunction_h
#define Rcpp_InternalFunction_h

#include <RcppCommon.h>

#include <Rcpp/grow.h>

namespace Rcpp{ 

    RCPP_API_CLASS(InternalFunction_Impl) {
    public:
    
        RCPP_GENERATE_CTOR_ASSIGN(InternalFunction_Impl) 
            
        #include <Rcpp/generated/InternalFunction__ctors.h>	
    		
    private:
    	
        inline void set( SEXP xp){
            Environment RCPP = Environment::Rcpp98_namespace() ;
            Function intf = RCPP["internal_function"] ;
            Storage::set__( intf( xp ) ) ; 
        }
    	
    };

    typedef InternalFunction_Impl<PreserveStorage> InternalFunction ;
    
} // namespace Rcpp

#endif
