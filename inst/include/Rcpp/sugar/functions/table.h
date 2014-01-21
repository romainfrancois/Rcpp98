// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; tab-width: 8 -*-
//
// table.h: Rcpp98 R/C++ interface class library -- table match
//
// Copyright (C) 2012 - 2013   Dirk Eddelbuettel, Romain Francois, and Kevin Ushey
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

#ifndef Rcpp__sugar__table_h
#define Rcpp__sugar__table_h

#include <Rcpp/sugar/tools/mapcompare.h>
          
namespace Rcpp{
namespace sugar{

template <typename MAP, typename STORAGE>
class CountInserter {
public:
    CountInserter( MAP& map_ ) : map(map_) {}
    
    inline void operator()( STORAGE value ){
        map[value]++ ;
    }
    
private:
    MAP& map ;
} ; 

template <typename MAP, int RTYPE>
class Grabber{
public:
    Grabber( IntegerVector& res_, CharacterVector& names_ ) : res(res_), names(names_), index(0){}
    
    inline void operator()( typename MAP::value_type pair){
        res[index] = pair.second ;
        names[index++] = internal::r_coerce<RTYPE,STRSXP>(pair.first) ;
    }
    
private:
    IntegerVector& res ;
    CharacterVector& names ;
    int index ;
} ;

template <int RTYPE, typename TABLE_T>        
class Table {
public:
    typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
    
    Table( const TABLE_T& table ): map() {
        std::for_each( table.begin(), table.end(), Inserter(map) ) ;
    }
    
    inline operator IntegerVector() const { 
        int n = map.size() ;
        IntegerVector result = no_init(n) ;
        CharacterVector names = no_init(n) ;
        std::for_each( map.begin(), map.end(), Grabber<MAP, RTYPE>(result, names) ) ;
        result.names() = names ;
        return result ;
    }
    
private:
    typedef std::map<STORAGE, int, MapCompare<STORAGE> > MAP ;
    typedef CountInserter<MAP,STORAGE> Inserter ;
    MAP map ;
};
    
} // sugar

template <int RTYPE, bool NA, typename T>
inline IntegerVector table( const VectorBase<RTYPE,NA,T>& x ){
    return sugar::Table<RTYPE,T>(x.get_ref()) ;
}


} // Rcpp
#endif

