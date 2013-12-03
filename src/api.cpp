// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; indent-tabs-mode: nil; -*-
// jedit: :folding=explicit:
//
// api.cpp: Rcpp R/C++ interface class library -- Rcpp api
//
// Copyright (C) 2012 - 2013  Dirk Eddelbuettel and Romain Francois
//
// This file is part of Rcpp98.
//
// Rcpp98 is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Rcpp98 is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Rcpp98.  If not, see <http://www.gnu.org/licenses/>.
  
#define COMPILING_RCPP98

#include <Rcpp.h>

using namespace Rcpp ;

#include "internal.h" 
#include <R_ext/PrtUtil.h>

#ifdef RCPP_HAS_DEMANGLING
#include <cxxabi.h>
#endif
     
#if defined(__GNUC__)
    #if defined(WIN32) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__CYGWIN__) || defined(__sun)
    #else
        #include <execinfo.h>
        
        static std::string demangler_one( const char* input){
            static std::string buffer ;
            buffer = input ;
            buffer.resize( buffer.find_last_of( '+' ) - 1 ) ;
            buffer.erase(
                buffer.begin(), 
                buffer.begin() + buffer.find_last_of( ' ' ) + 1
            ) ;
            return demangle( buffer) ;
        }

    #endif
#endif


namespace Rcpp {
     
    namespace internal{
        namespace {
            unsigned long RNGScopeCounter = 0;
        }
        
        // [[Rcpp::register]]
        unsigned long enterRNGScope() {       
            if (RNGScopeCounter == 0) GetRNGstate();       
            RNGScopeCounter++;
            return RNGScopeCounter ;
        }
        
        // [[Rcpp::register]]
        unsigned long exitRNGScope() {
            RNGScopeCounter--;
            if (RNGScopeCounter == 0) PutRNGstate();
            return RNGScopeCounter ;
        }
        
        // [[Rcpp::register]]
        char* get_string_buffer(){
            static char buffer[MAXELTSIZE];
            return buffer ;    
        }

    }
    
    // [[Rcpp::register]]
    const char * type2name(SEXP x) {
        switch (TYPEOF(x)) {
        case NILSXP:	return "NILSXP";
        case SYMSXP:	return "SYMSXP";
        case RAWSXP:	return "RAWSXP";
        case LISTSXP:	return "LISTSXP";
        case CLOSXP:	return "CLOSXP";
        case ENVSXP:	return "ENVSXP";
        case PROMSXP:	return "PROMSXP";
        case LANGSXP:	return "LANGSXP";
        case SPECIALSXP:	return "SPECIALSXP";
        case BUILTINSXP:	return "BUILTINSXP";
        case CHARSXP:	return "CHARSXP";
        case LGLSXP:	return "LGLSXP";
        case INTSXP:	return "INTSXP";
        case REALSXP:	return "REALSXP";
        case CPLXSXP:	return "CPLXSXP";
        case STRSXP:	return "STRSXP";
        case DOTSXP:	return "DOTSXP";
        case ANYSXP:	return "ANYSXP";
        case VECSXP:	return "VECSXP";
        case EXPRSXP:	return "EXPRSXP";
        case BCODESXP:	return "BCODESXP";
        case EXTPTRSXP:	return "EXTPTRSXP";
        case WEAKREFSXP:	return "WEAKREFSXP";
        case S4SXP:		return "S4SXP";
        default:
        return "<unknown>";
        }
    }
    
    
} // namespace Rcpp

// [[Rcpp::register]]  
std::string demangle( const std::string& name ){
    #ifdef RCPP_HAS_DEMANGLING
        std::string real_class ;
        int status =-1 ;
        char *dem = 0;
        dem = abi::__cxa_demangle(name.c_str(), 0, 0, &status);
        if( status == 0 ){
            real_class = dem ;
            free(dem);
        } else {
            real_class = name ;
        }
        return real_class ;
    #else
        return name ;
    #endif    
}
    
// [[Rcpp::register]]
const char* short_file_name(const char* file){
    std::string f(file) ;
    size_t index = f.find("/include/") ;
    if( index != std::string::npos ){ 
        f = f.substr( index + 9 ) ;
    }
    return f.c_str() ;
}
    
// [[Rcpp::internal]]
SEXP as_character_externalptr(SEXP xp){
    char buffer[20] ;
    snprintf( buffer, 20, "%p", (void*)EXTPTR_PTR(xp) ) ;
    return Rcpp::wrap( (const char*)buffer ) ;
}
    
// [[Rcpp::internal]]
SEXP rcpp_capabilities(){
    return LogicalVector::create( 
        _["variadic templates"] = false,
        _["initializer lists"]  = false,
        _["exception handling"] = true,
        _["Rcpp modules"]       = true,
        #if defined(RCPP_HAS_DEMANGLING)
        _["demangling"]         = true,
        #else
        _["demangling"]         = false,
        #endif
        _["long long"]          = false 
        ) ;
}

// [[Rcpp::register]]
SEXP stack_trace( const char* file, int line ){
    #if defined(__GNUC__)
        #if defined(WIN32) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__CYGWIN__) || defined(__sun)
            // Simpler version for Windows and *BSD 
            List trace = List::create( 
                _[ "file"  ] = file, 
                _[ "line"  ] = line, 
                _[ "stack" ] = "C++ stack not available on this system"
            ) ;
            trace.attr("class") = "Rcpp_stack_trace" ;
            return trace ;
        #else // ! (defined(WIN32) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__CYGWIN__) || defined(__sun)
        
            /* inspired from http://tombarta.wordpress.com/2008/08/01/c-stack-traces-with-gcc/  */ 
            const size_t max_depth = 100;
            size_t stack_depth;
            void *stack_addrs[max_depth];
            char **stack_strings;
            
            stack_depth = backtrace(stack_addrs, max_depth);
            stack_strings = backtrace_symbols(stack_addrs, stack_depth);
            
            std::string current_line ;
            
            CharacterVector res( stack_depth - 1) ;
            std::transform( 
                stack_strings + 1, stack_strings + stack_depth, 
                res.begin(), 
                demangler_one 
            ) ;
            free(stack_strings); // malloc()ed by backtrace_symbols
            
            List trace = List::create( 
                _["file" ] = file, 
                _["line" ] = line, 
                _["stack"] = res
            ) ;
            trace.attr("class") = "Rcpp_stack_trace" ;
            return trace ;
        #endif 
    #else /* !defined( __GNUC__ ) */
	    return R_NilValue ;
	#endif 
}
// }}}

