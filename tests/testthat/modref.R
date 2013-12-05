
.setUp <- Rcpp98:::unit_test_setup( "modref.cpp" )     
    
test.modRef <- function() {
    ww = new(World)
    wg = World$new()
    
    checkEquals(ww$greet(), wg$greet())
    wgg <- wg$greet()
    
    ww$set("Other")
    
    ## test independence of ww, wg
    checkEquals(ww$greet(), "Other")
    checkEquals(wg$greet(), wgg)
    
    World$methods(twice = function() paste(greet(), greet()))
    
    checkEquals(ww$twice(), paste(ww$greet(), ww$greet()))

}

