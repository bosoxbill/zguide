//
//  Demonstrate identities as used by the request-reply pattern.  Run this
//  program by itself.
//
// Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>

#include <zmq.hpp>
#include "zhelpers.hpp"

int main () {
    zmq::context_t context(1);

    //  First allow 0MQ to set the identity
    zmq::socket_t sink(context, ZMQ_XREP);
    sink.bind( "inproc://example");

    zmq::socket_t anonymous(context, ZMQ_REQ);
    anonymous.connect( "inproc://example");
    
	s_send (anonymous, "XREP uses a generated UUID");
    s_dump (sink);

    zmq::socket_t identified (context, ZMQ_REQ);
    identified.setsockopt( ZMQ_IDENTITY, "Hello", 5);
    identified.connect( "inproc://example");
    
    s_send (identified, "XREP socket uses REQ's socket identity");
    s_dump (sink);

    return 0;
}
