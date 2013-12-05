
.setUp <- Rcpp98:::unit_test_setup( "String.cpp" )

test.replace_all <- function(){
    checkEquals( String_replace_all("foobar", "o", "*"), "f**bar")
}
test.replace_first <- function(){
    checkEquals( String_replace_first("foobar", "o", "*"), "f*obar")
}
test.replace_last <- function(){
    checkEquals( String_replace_last("foobar", "o", "*"), "fo*bar")
}

test.String.sapply <- function(){
    res <- test_sapply_string( "foobar", c("o", "a" ), c("*", "!" ) )
    checkEquals( res, "f**b!r" )    
}

test.compare.Strings <- function(){
    res <- test_compare_Strings( "aaa", "aab" )
    target <- list( 
        "a  < b" = TRUE, 
        "a  > b" = FALSE,  
        "a == b" = FALSE,
        "a == a" = TRUE
    )
    checkEquals( res, target )
}
  
