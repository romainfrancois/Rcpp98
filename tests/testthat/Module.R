
.setUp <- Rcpp98:::unit_test_setup( "Module.cpp" )
    
test.Module <- function(){
    checkEquals( bar( 2L ), 4L )
    checkEquals( foo( 2L, 10.0 ), 20.0 )
    checkEquals( hello(), "hello" )
    
    w <- new( World )
    checkEquals( w$greet(), "hello" )
    w$set( "hello world" )
    checkEquals( w$greet(), "hello world" )
    w$set_ref( "hello world ref" )
    checkEquals( w$greet(), "hello world ref" )
    w$set_const_ref( "hello world const ref" )
    checkEquals( w$greet(), "hello world const ref" )
    w$clear( )
    checkEquals( w$greet(), "" )
}

test.Module.exposed.class <- function(){
    test <- new( Test, 3.0 )
    checkEquals( Test_get_x_const_ref(test), 3.0 )
    checkEquals( Test_get_x_const_pointer(test), 3.0 )
    checkEquals( Test_get_x_ref(test), 3.0 )
    checkEquals( Test_get_x_pointer(test), 3.0 )
    
    checkEquals( attr_Test_get_x_const_ref(test), 3.0 )
    checkEquals( attr_Test_get_x_const_pointer(test), 3.0 )
    checkEquals( attr_Test_get_x_ref(test), 3.0 )
    checkEquals( attr_Test_get_x_pointer(test), 3.0 )
}

test.Module.property <- function(){
    w <- new( Num )
    checkEquals( w$x, 0.0 )
    checkEquals( w$y, 0L )

    w$x <- 2.0
    checkEquals( w$x, 2.0 )

    checkException( { w$y <- 3 } )
}

test.Module.member <- function(){
    w <- new( Number )
    checkEquals( w$x, 0.0 )
    checkEquals( w$y, 0L )

    w$x <- 2.0
    checkEquals( w$x, 2.0 )

    checkException( { w$y <- 3 } )
}

test.Module.Constructor <- function() {
    r <- new( Randomizer, 10.0, 20.0 )
    set.seed(123)
    x10 <- runif(10, 10.0, 20.0)
    set.seed(123)
    checkEquals(r$get(10), x10)
}

test.Module.flexible.semantics <- function( ){
    checkEquals( test_reference( seq(0,10) ), 11L )
    checkEquals( test_const_reference( seq(0,10) ), 11L )
    checkEquals( test_const( seq(0,10) ), 11L )
}

