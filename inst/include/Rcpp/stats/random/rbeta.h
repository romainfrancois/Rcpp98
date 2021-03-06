// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; tab-width: 4 -*-
//
// rbeta.h: Rcpp R/C++ interface class library -- 
//
// Copyright (C) 2010 - 2012 Douglas Bates, Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp__stats__random_rbeta_h
#define Rcpp__stats__random_rbeta_h

namespace Rcpp {
namespace stats{
    
    class BetaGenerator : public Generator<double>{
    public: 
        BetaGenerator(double a_, double b_) : a(a_), b(b_){}
        
        inline double operator()() const {
            return ::Rf_rbeta(a, b) ;    
        }
    private:
        double a, b ;
    } ;
    
} // namespace stats

} // Rcpp

#endif
