
.setUp <- Rcpp98:::unit_test_setup( "XPtr.cpp" )
    
test.XPtr <- function(){
    xp <- xptr_1()
    checkEquals(typeof( xp ), "externalptr", msg = "checking external pointer creation" )
    
    front <- xptr_2(xp)
    checkEquals( front, 1L, msg = "check usage of external pointer" )
}

