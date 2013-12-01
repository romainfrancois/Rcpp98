// Copyright (C) 2013    Romain Francois
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

#ifndef Rcpp_api_meat_as_h
#define Rcpp_api_meat_as_h

namespace Rcpp{ 
namespace internal{
     
    inline void* as_module_object_internal(SEXP obj){
        Environment env(obj) ;
        SEXP xp = env.get(".pointer") ;
        return R_ExternalPtrAddr(xp );   
    }
        
}
}

#endif
