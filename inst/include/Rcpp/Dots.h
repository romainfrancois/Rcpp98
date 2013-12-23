// Copyright (C) 2013 Romain Francois

#ifndef Rcpp_Dots_h
#define Rcpp_Dots_h

namespace Rcpp{ 
    
    template < template <class> class StoragePolicy>
    class Dots_Impl {
    public:
        typedef Environment_Impl<StoragePolicy> Environment ;
        typedef Promise_Impl<StoragePolicy> Promise ;
        
        Dots_Impl( Environment env){
            SEXP dots = env.find("...") ;
            while(dots != R_NilValue){
                promises.push_back(CAR(dots)) ;
                dots = CDR(dots);
            }
        }
        
        inline int size() const {
            return promises.size() ;    
        }
        
        inline Promise& prom(int i) {
            return promises[i] ;
        }
        
        inline Environment& env(int i){
            return promises[i].environment() ;    
        }
        
    private:
        
        std::vector<Promise> promises ;
    } ;
    
    typedef Dots_Impl<NoProtectStorage> Dots ; 
    
}

#endif
