//
// Created by shangqi on 2021/1/29.
//
#include <iostream>

#include "secret_sharing/secret_sharing.h"

using namespace emp;
using namespace std;


int main(int argc, char** argv) {
    // create channel
    int port, party;
    parse_party_and_port(argv, &party, &port);
    // each party occupies a port to communicate with its counter-party
    auto * io_Alice = new NetIO(party==ALICE ? nullptr : "127.0.0.1", port);
    auto * io_Bob = new NetIO(party==BOB ? nullptr : "127.0.0.1", port + 1);
    // setup parties, the private input is the third parameter
    auto entity = setup_multiplication_party(party, io_Alice, io_Bob, atoi(argv[3]));
    entity.share();
    entity.compute();
    cout << entity.reveal() << endl;
    delete io_Alice;
    delete io_Bob;
}
