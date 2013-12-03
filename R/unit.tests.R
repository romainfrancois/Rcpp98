# Copyright (C) 2010 - 2013 Dirk Eddelbuettel and Romain Francois
#
# This file is part of Rcpp98.
#
# Rcpp98 is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# Rcpp98 is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Rcpp98.  If not, see <http://www.gnu.org/licenses/>.

unit_test_setup <- function(file, packages = NULL) {
    function(){
        if( !is.null(packages) ){
            for( p in packages ){
                suppressMessages( require( p, character.only = TRUE ) )
            }
        }
        if (!exists("pathRcppTests")) pathRcppTests <- getwd()
        sourceCpp(file.path(pathRcppTests, "cpp", file ))
    }
}

