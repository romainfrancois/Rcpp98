
.setUp <- Rcpp98:::unit_test_setup( "Reference.cpp" )

test.Reference <- function(){
    Instrument <- setRefClass(
       Class="Instrument",
       fields=list("id"="character", "description"="character")
    )
    Instrument$accessors(c("id", "description"))
    
    instrument <- Instrument$new(id="AAPL", description="Apple")
    
    checkEquals( runit_Reference_getId(instrument), "AAPL", msg = ".field" )
}

