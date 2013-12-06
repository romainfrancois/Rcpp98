
context( "Modules" )

test_that( "R classes can extend C++ classes", {

    td <- tempfile()
    cwd <- getwd()
    dir.create( td )
    file.copy( system.file( "unitTests", "testRcppClass", package = "Rcpp98" ) , td, recursive = TRUE)
    setwd( td )
    on.exit( { setwd( cwd) ; unlink( td, recursive = TRUE ) } )
    R <- shQuote( file.path( R.home( component = "bin" ), "R" ))
    cmd <- paste( R , "CMD build testRcppClass" )
    system( cmd )
    dir.create( "templib" )
    install.packages( "testRcppClass_0.1.tar.gz", "templib", repos = NULL, type = "source" )            
    
    require( "testRcppClass", "templib", character.only = TRUE )

    v <- stdNumeric$new()
    data <- as.numeric(1:10)
    v$assign(data)
    v$set(3L, v$at(3L) + 1)
    
    data[[4]] <- data[[4]] +1
    
    expect_equal( v$as.vector(), data )
    
    ## a few function calls
    expect_equal( bar(2), 4)
    expect_equal( foo(2,3), 6)

})

