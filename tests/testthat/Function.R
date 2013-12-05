
.setUp <- Rcpp98:::unit_test_setup( "Function.cpp" )

test.Function <- function(){
    checkEquals( function_( ls ), ls, msg = "Function( CLOSXP )" )
    checkEquals( function_( is.function ), is.function, msg = "Pairlist( BUILTINSXP )" )
    
    checkException( function_(1:10), msg = "Function( INTSXP) " )
    checkException( function_(TRUE), msg = "Function( LGLSXP )" )
    checkException( function_(1.3), msg = "Function( REALSXP) " )
    checkException( function_(as.raw(1) ), msg = "Function( RAWSXP)" )
    checkException( function_(new.env()), msg = "Function not compatible with environment" )
}

test.Function.variadic <- function(){
    checkEquals( function_variadic( sort, sample(1:20) ), 20:1, msg = "calling function" )
    checkException( function_variadic(sort, sort), msg = "Function, R error -> exception" )
}

test.Function.unary.call <- function(){
	checkEquals(
		function_unarycall( lapply( 1:10, function(n) seq(from=n, to = 0 ) ) ),
		2:11 ,
		msg = "unary_call(Function)" )
}

test.Function.binary.call <- function(){
	data <- lapply( 1:10, function(n) seq(from=n, to = 0 ) )
	res <- function_binarycall( data , rep(5L,10) )
	expected <- lapply( data, pmin, 5 )
	checkEquals( res, expected,
		msg = "binary_call(Function)" )
}

