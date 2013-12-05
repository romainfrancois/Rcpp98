#include <Rcpp.h>
using namespace Rcpp ;

// [[Rcpp::export]]
List plus_REALSXP(){
    return List::create(
        NA_REAL + NA_REAL,
        NA_REAL + 1.0,
        1.0 + NA_REAL
    );
}

// [[Rcpp::export]]
List times_REALSXP(){
    return List::create(
        NA_REAL * NA_REAL,
        NA_REAL * 1.0,
        1.0 * NA_REAL
    );
}

// [[Rcpp::export]]
List divides_REALSXP(){
    return List::create(
       NA_REAL / NA_REAL,
       NA_REAL / 1.0,
       1.0 / NA_REAL
       );
}

// [[Rcpp::export]]
List minus_REALSXP(){
    return List::create(
       NA_REAL - NA_REAL,
       NA_REAL - 1.0,
       1.0 - NA_REAL
       );
}

// [[Rcpp::export]]
List functions_REALSXP(){
    return List::create(
        NumericVector::create(
           exp( NA_REAL ),
           acos( NA_REAL ),
           asin( NA_REAL ),
           atan( NA_REAL ),
           ceil( NA_REAL ),
           cos( NA_REAL ),
           cosh( NA_REAL ),
           floor( NA_REAL ),
           log( NA_REAL ),
           log10( NA_REAL ),
           sqrt( NA_REAL),
           sin( NA_REAL ),
           sinh( NA_REAL ),
           tan( NA_REAL ),
           tanh( NA_REAL ),
           fabs( NA_REAL ),
           Rf_gammafn( NA_REAL),
           Rf_lgammafn( NA_REAL ),
           Rf_digamma( NA_REAL ),
           Rf_trigamma( NA_REAL )
        ) , NumericVector::create(
           Rf_tetragamma( NA_REAL) ,
           Rf_pentagamma( NA_REAL) ,
           expm1( NA_REAL ),
           log1p( NA_REAL ),
           Rcpp::internal::factorial( NA_REAL ),
           Rcpp::internal::lfactorial( NA_REAL )
        )
     );
}
