Rcpp98: Alternative implementation of the Rcpp API. 
====================================

## What is this

`Rcpp98` is an alternative implementation of the `Rcpp` api. Here are some of the 
motivation for it. 

 - switching to a new name frees me from the hypothetical dependency problem. 
   This gives me latitude to make important disruptive changes rapidly, 
   whereas in `Rcpp` even if manage to negociate such changes, I sometimes have to wait
   for a year and go through a long deprecation period, ... Life is too short for that
 - Emphasis on C++98. `Rcpp98`
   does not contain code that attempts to use C++11 or later. If you are 
   interested in C++11, my recommendation would be to use `Rcpp11`, my 
   `Rcpp` implementation focused on C++11 features. 
 - Cleaner code. For example `Rcpp98` does not contain the classes that `Rcpp` has
   to deal with times and dates. A better set of classes will be designed and
   introduced later. 

## Installation

Until `Rcpp98` is released to CRAN, you can install it from github. 

```R
install.packages("devtools")
devtools::install_github("romainfrancois/Rcpp98")
```

