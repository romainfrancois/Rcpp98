
.setUp <- Rcpp98:::unit_test_setup( "support.cpp" )

test.plus.REALSXP <- function(){
    checkEquals(
        plus_REALSXP(),
        list(NA_real_,NA_real_,NA_real_) ,
        msg = " REALSXP + REALSXP" )
}

test.times.REALSXP <- function(){
    checkEquals(
        times_REALSXP(),
        list(NA_real_,NA_real_,NA_real_) ,
        msg = " REALSXP * REALSXP" )
}

test.divides.REALSXP <- function(){
    checkEquals(
        divides_REALSXP(),
        list(NA_real_,NA_real_,NA_real_) ,
        msg = " REALSXP / REALSXP" )
}

test.minus.REALSXP <- function(){
    checkEquals(
        minus_REALSXP(),
        list(NA_real_,NA_real_,NA_real_) ,
        msg = " REALSXP - REALSXP" )
}

test.functions.REALSXP <- function(){
    checkEquals(
        functions_REALSXP(),
        list( rep(NA_real_, 20L), rep(NA_real_, 6L) ) ,
        msg = "function(NA_REAL)" )
}

