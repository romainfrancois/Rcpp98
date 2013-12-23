// Copyright (C) 2013 Romain Francois

#ifndef Rcpp_NamedDots_h
#define Rcpp_NamedDots_h

namespace Rcpp{ 
    
    template < template <class> class StoragePolicy>
    class NamedDots_Impl {
    public:
        typedef Environment_Impl<StoragePolicy> Environment ;
        typedef Promise_Impl<StoragePolicy> Promise ;
        
        NamedDots_Impl( Environment env ){
            SEXP dots = env.find("...") ;
            while(dots != R_NilValue){
                promises.push_back(CAR(dots)) ;
                dots = CDR(dots);
            }
        }
        
        inline int size() const {
            return promises.size() ;    
        }
        
        inline Promise& promise(int i) {
            return promises[i] ;
        }
        
        inline Environment environment(int i){
            return promises[i].environment() ;    
        }
        
    private:
        
        std::vector<Promise> promises ;
    } ;
    
    typedef NamedDots_Impl<NoProtectStorage> Dots ; 
    
}

#endif
