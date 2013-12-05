context( "Rcpp API" )
sourceCpp( "cpp/misc.cpp" )

test_that( "Symbol correctly handles various SEXP", {
	res <- symbol_()
	expect_true( res[1L])
	expect_true( res[2L])
	expect_true( res[3L])
	expect_true( res[4L])

	expect_error( symbol_ctor(symbol_ctor))
	expect_error( symbol_ctor(asNamespace("Rcpp98")))
	expect_error( symbol_ctor(1:10))
	expect_error( symbol_ctor(TRUE))
	expect_error( symbol_ctor(1.3))
	expect_error( symbol_ctor(as.raw(1) ))
})

test_that( "Argument can be used in List::create",{
  expect_equal( Argument_(), list( x = 2L, y = 3L ) )
})

test_that( "Rcpp_eval propagates R errors", {
  expect_error( evaluator_error())
  expect_equal( sort(evaluator_ok(1:10)), 1:10)
})

test_that( "exceptions are correctly mapped to conditions", {
	can.demangle <- Rcpp98:::capabilities()[["demangling"]]

	e <- tryCatch(  exceptions_(), "C++Error" = function(e) e )
	expect_true( "C++Error" %in% class(e))

	if( can.demangle ){
		expect_true( "std::range_error" %in% class(e))
	}
	expect_equal( e$message, "boom")

	if( can.demangle ){
		# same with direct handler
		e <- tryCatch(  exceptions_(), "std::range_error" = function(e) e )
		expect_true( "C++Error" %in% class(e))
		expect_true( "std::range_error" %in% class(e))
		expect_equal( e$message, "boom")
	}
	f <- function(){
		try( exceptions_(), silent = TRUE)
		"hello world"
	}
	expect_equal( f(), "hello world")
})

test_that( "has_iterator traits works", {
  has_it <- has_iterator_()
	expect_true( has_it[1L] )
	expect_true( has_it[2L] )
	expect_true( has_it[3L] )
	expect_true( has_it[4L] )
	expect_true( has_it[5L] )

	expect_true( ! has_it[6L] )
	expect_true( ! has_it[7L] )
})

test_that( "areMacrosDefined works", {
  expect_true( Rcpp98:::areMacrosDefined( "__cplusplus" ) )    
})

test_that( "Na_Proxy handles comparison to NA", {
    expect_equal( 
        na_proxy(), 
        rep(c(TRUE,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE) , 2), 
        msg = "Na_Proxy NA == handling"
    )    
})

test_that( "StrechyList correctly builds pairlists",
    expect_equal( 
        stretchy_list(),
        pairlist( "foo", 1L, 3.2 )
    )
    expect_equal( 
        named_stretchy_list(),
        pairlist( a = "foo", b = 1L, c = 3.2 )
    )
})
