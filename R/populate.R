# Copyright (C) 2010 - 2011 John Chambers, Dirk Eddelbuettel and Romain Francois
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

populate <- function( module, env ){
    
    # make sure the module is loaded
    module <- Module( module, mustStart = TRUE )
    
    storage <- get( "storage", as.environment(module ) )
    symbols <- ls( storage )
    
    is_ns <- isNamespace( env )
    for( x in symbols ){
        forceAssignInNamespace( x, storage[[x]], env )
    }
}

