#include <Rcpp.h>
using namespace Rcpp ;

class World {
public:
    World() : foo(1), msg("hello") {}
    void set(std::string msg_) { this->msg = msg_; }
    std::string greet() { return msg; }
    
    int foo ;
    double bar ;

private:
    std::string msg;
};

void clearWorld( World* w ){
    w->set( "" );
}

RCPP_MODULE(yada){
	class_<World>( "World" )
        .default_constructor()
        
        .method( "greet", &World::greet )
        .method( "set", &World::set )
        .method( "clear", &clearWorld )
        
        .field( "foo", &World::foo )
        .field_readonly( "bar", &World::bar )
	;

}

