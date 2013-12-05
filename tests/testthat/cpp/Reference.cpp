#include <Rcpp.h>
using namespace Rcpp ;

// [[Rcpp::export]]
std::string runit_Reference_getId(Reference obj) {
    std::string txt = obj.field("id");
    return txt;
}

