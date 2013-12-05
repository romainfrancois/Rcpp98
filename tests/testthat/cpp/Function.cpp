#include <Rcpp.h>
using namespace Rcpp ;

// [[Rcpp::export]]
Function function_(SEXP x){ return Function(x) ; }

// [[Rcpp::export]]
NumericVector function_variadic(Function sort, NumericVector y){
    return sort( y, Named("decreasing", true) ) ;
}

// [[Rcpp::export]]
Environment function_env(Function fun){
    return fun.environment() ;
}

// [[Rcpp::export]]
IntegerVector function_unarycall(List x){
    Function len( "length" ) ;
    IntegerVector output( x.size() ) ;
    std::transform(
        	x.begin(), x.end(),
        	output.begin(),
        	unary_call<IntegerVector,int>(len)
    	) ;
    return output ;
}

// [[Rcpp::export]]
List function_binarycall(List list,IntegerVector vec){
    Function pmin( "pmin" ) ;
    List output( list.size() ) ;
    std::transform(
        	list.begin(), list.end(),
        	vec.begin(),
        	output.begin(),
        	binary_call<IntegerVector,int,IntegerVector>(pmin)
    	) ;
    return output ;
}

// [[Rcpp::export]]
Function function_namespace_env(){
    Environment ns = Environment::namespace_env( "stats" ) ;
    Function fun = ns[".asSparse"] ;  // accesses a non-exported function
    return fun;
}

