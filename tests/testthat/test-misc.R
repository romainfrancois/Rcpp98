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
        rep(c(TRUE,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE) , 2)
    )    
})

test_that( "StrechyList correctly builds pairlists", {
    expect_equal( 
      stretchy_list(),
      pairlist( "foo", 1L, 3.2 ) 
    )
    expect_equal(
      named_stretchy_list(),
      pairlist( a = "foo", b = 1L, c = 3.2 )
    )
})

test_that( "Reference works", {
    Instrument <- setRefClass(
       Class="Instrument",
       fields=list("id"="character", "description"="character")
    )
    Instrument$accessors(c("id", "description"))
    
    instrument <- Instrument$new(id="AAPL", description="Apple")
    
    expect_equal( runit_Reference_getId(instrument), "AAPL" )
})

test_that( "S4 works", {
	setClass("track", representation(x="numeric", y="numeric"))
	tr <- new( "track", x = 2, y = 2 )
	expect_equal( 
	    S4_methods(tr),
		list( TRUE, TRUE, FALSE, 2.0, 2.0 )
	)

	S4_getslots( tr )
	expect_equal( tr@x, 10.0 )
	expect_equal( tr@y, 20.0 )

	expect_error( S4_setslots( tr ))
	expect_error( S4_setslots_2( tr ))

	tr <- new( "track", x = 2, y = 3 )
	expect_equal( S4_get_slot_x( tr ), 2)
	expect_error( S4_get_slot_x( list( x = 2, y = 3 ) ))
	expect_error( S4_get_slot_x( structure( list( x = 2, y = 3 ), class = "track" ) ))

	tr <- S4_ctor( "track" )
	expect_true( inherits( tr, "track" ) )
	expect_equal( tr@x, numeric(0) )
	expect_equal( tr@y, numeric(0) )
	expect_error( S4_ctor( "someclassthatdoesnotexist" ) )
	
	setClass( "Foo", contains = "character", representation( x = "numeric" ) )
	foo <- S4_dotdata( new( "Foo", "bla", x = 10 ) )
	expect_equal( as.character( foo) , "foooo" )
	
})

test_that( "S4 correctly defines is", {
	setClass("track", representation(x="numeric", y="numeric"))
	setClass("trackCurve", representation(smooth = "numeric"), contains = "track")

	tr1 <- new( "track", x = 2, y = 3 )
	tr2 <- new( "trackCurve", x = 2, y = 3, smooth = 5 )

	expect_true( S4_is_track( tr1 ))
	expect_true( S4_is_track( tr2 ))

	expect_true( !S4_is_trackCurve( tr1 ))
	expect_true( S4_is_trackCurve( tr2 ))
})

test_that( "Vector can be constructed from Proxies", {
	setClass("track", representation(x="numeric", y="numeric"))
	setClass("trackCurve", representation(smooth = "numeric"), contains = "track")

	tr1 <- new( "track", x = 2, y = 3 )
	expect_equal( S4_get_slot_x(tr1), 2 )

	x <- 1:10
	attr( x, "foo" ) <- "bar"

	expect_equal( S4_get_attr_x(x), "bar" )

})

test_that( "NA is correctly handled", {
    expect_equal(
        plus_REALSXP(),
        list(NA_real_,NA_real_,NA_real_)
        )
    expect_equal(
        times_REALSXP(),
        list(NA_real_,NA_real_,NA_real_)
        )
    expect_equal(
        divides_REALSXP(),
        list(NA_real_,NA_real_,NA_real_)
        )
    expect_equal(
        minus_REALSXP(),
        list(NA_real_,NA_real_,NA_real_)
        )
    expect_equal(
        functions_REALSXP(),
        list( rep(NA_real_, 20L), rep(NA_real_, 6L) )
        )
})

