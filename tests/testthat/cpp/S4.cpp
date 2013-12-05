#include <Rcpp.h>
using namespace Rcpp ;

// [[Rcpp::export]]
List S4_methods( RObject y ){
    List res(5) ;
    res[0] = y.isS4() ;
    res[1] = y.hasSlot("x") ;
    res[2] = y.hasSlot("z") ;
    res[3] = y.slot("x") ;
    res[4] = y.slot("y") ;
    return res ;        
}

// [[Rcpp::export]]
void S4_getslots( S4 y){
    y.slot( "x" ) = 10.0 ;
    y.slot( "y" ) = 20.0 ;
}      

// [[Rcpp::export]]
void S4_setslots( S4 y ){
    y.slot( "foo" ) = 10.0 ;
}

// [[Rcpp::export]]
void S4_setslots_2( S4 y){
    y.slot( "foo" ) ;    
}

// [[Rcpp::export]]
S4 S4_ctor( std::string cl){
    return S4( cl );    
}

// [[Rcpp::export]]
bool S4_is_track(S4 tr){
    return tr.is("track") ;
}

// [[Rcpp::export]]
bool S4_is_trackCurve(S4 tr){
    return tr.is("trackCurve") ;
}

// [[Rcpp::export]]
NumericVector S4_get_slot_x(S4 o){
    NumericVector res( o.slot("x") );
    return res ;    
}

// [[Rcpp::export]]
CharacterVector S4_get_attr_x(IntegerVector o){
    CharacterVector res( o.attr("foo") ) ;
    return res ;
}

// [[Rcpp::export]]
S4 S4_dotdata(S4 foo){
    foo.slot( ".Data" ) = "foooo" ;
    return foo ;
}

