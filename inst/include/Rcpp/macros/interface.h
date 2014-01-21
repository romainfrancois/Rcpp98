// Copyright (C) 2013 - 2014 Romain Francois
  
#ifndef Rcpp_macros_interface_h
#define Rcpp_macros_interface_h

#define RCPP_GENERATE_CTOR_ASSIGN(__CLASS__)                                   \
typedef StoragePolicy<__CLASS__> Storage ;                                     \
typedef AttributeProxyPolicy<__CLASS__> AttributePolicy ;                      \
RCPP_CTOR_ASSIGN(__CLASS__)

#define RCPP_CTOR_ASSIGN(__CLASS__)                                            \
__CLASS__( const __CLASS__& other ){                                           \
    Storage::copy__(other) ;                                                   \
}                                                                              \
__CLASS__& operator=(const __CLASS__& rhs) {                                   \
    return Storage::copy__(rhs) ;                                              \
}                                                                              \
template <typename Proxy>                                                      \
__CLASS__( const GenericProxy<Proxy>& proxy ){                                 \
    Storage::set__( proxy.get() ) ;                                            \
}
    
#define RCPP_API_CLASS(__CLASS__)                                              \
template < template <class> class StoragePolicy > class __CLASS__ :            \
    public StoragePolicy<__CLASS__<StoragePolicy> >,                           \
    public SlotProxyPolicy<__CLASS__<StoragePolicy> >,                         \
    public AttributeProxyPolicy<__CLASS__<StoragePolicy> >,                    \
    public RObjectMethods< __CLASS__<StoragePolicy> >
   
#endif
