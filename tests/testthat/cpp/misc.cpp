#include <Rcpp.h>
using namespace Rcpp ;
using namespace std;
#include <iostream>
#include <fstream>

// [[Rcpp::export]]
SEXP symbol_(){
    return LogicalVector::create( 
        Symbol( Rf_install("foobar") ) == Rf_install("foobar"), 
        Symbol( Rf_mkChar("foobar") ) == Rf_install("foobar"), 
        Symbol( Rf_mkString("foobar") ) == Rf_install("foobar"), 
        Symbol( "foobar" ) == Rf_install("foobar") 
    ) ;
}

// [[Rcpp::export]]
Symbol symbol_ctor(SEXP x){ return Symbol(x); }

// [[Rcpp::export]]
List Argument_(){
    Argument x("x"), y("y");
    return List::create( x = 2, y = 3 );
}

// [[Rcpp::export]] 
SEXP evaluator_error(){
    return Rcpp_eval( Rf_lang2( Rf_install("stop"), Rf_mkString( "boom" ) ) ) ;
}

// [[Rcpp::export]]
SEXP evaluator_ok(SEXP x){
    return Rcpp_eval( Rf_lang2( Rf_install("sample"), x ) ) ;
}

// [[Rcpp::export]]
void exceptions_(){
    throw std::range_error("boom") ;
}

// [[Rcpp::export]]
LogicalVector has_iterator_( ){
    return LogicalVector::create( 
        (bool)Rcpp::traits::has_iterator< std::vector<int> >::value, 
        (bool)Rcpp::traits::has_iterator< std::list<int> >::value, 
        (bool)Rcpp::traits::has_iterator< std::deque<int> >::value, 
        (bool)Rcpp::traits::has_iterator< std::set<int> >::value, 
        (bool)Rcpp::traits::has_iterator< std::map<std::string,int> >::value, 
        (bool)Rcpp::traits::has_iterator< std::pair<std::string,int> >::value, 
        (bool)Rcpp::traits::has_iterator< Rcpp::Symbol >::value 
        );
}

// [[Rcpp::export]]
LogicalVector na_proxy(){
    CharacterVector s("foo") ;
    return LogicalVector::create( 
        NA_REAL    == NA, 
        NA_INTEGER == NA,
        NA_STRING  == NA,
        true       == NA, 
        false      == NA, 
        1.2        == NA, 
        12         == NA,
        "foo"      == NA,
        s[0]       == NA, 
        
        NA         == NA_REAL, 
        NA         == NA_INTEGER,
        NA         == NA_STRING,
        NA         == true, 
        NA         == false,
        NA         == 1.2  , 
        NA         == 12   ,
        NA         == "foo", 
        NA         == s[0]
        ) ;
}      

// [[Rcpp::export]]
StretchyList stretchy_list(){
    StretchyList out ;
    out.push_back( 1 ) ;
    out.push_front( "foo" ) ;
    out.push_back( 3.2 ) ;
    return out;
}

// [[Rcpp::export]]
StretchyList named_stretchy_list(){
    StretchyList out ;
    out.push_back( _["b"] = 1 ) ;
    out.push_front( _["a"] = "foo" ) ;
    out.push_back( _["c"] = 3.2 ) ;
    return out;
}

// [[Rcpp::export]]
std::string runit_Reference_getId(Reference obj) {
    std::string txt = obj.field("id");
    return txt;
}

