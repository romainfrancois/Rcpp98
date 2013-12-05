
.setUp <- Rcpp98:::unit_test_setup( "wstring.cpp" )

test.CharacterVector_wstring <- function(){
    res <- CharacterVector_wstring()
    checkEquals( res, c("foobar", "foobar" ) )
}

test.wstring_return <- function(){
    checkEquals( wstring_return(), "foo" )
}

test.wstring_param <- function(){
    checkEquals( wstring_param( "foo", "bar" ), "foobar" )
}

test.wrap_vector_wstring <- function(){
    checkEquals( wrap_vector_wstring( ), c("foo", "bar" ) )
}

