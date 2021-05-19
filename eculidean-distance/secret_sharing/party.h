//
// Created by shangqi on 2021/1/28.
//

#ifndef SECRET_SHARING_PARTY_H
#define SECRET_SHARING_PARTY_H

#include "emp-tool/emp-tool.h"
#include "emp-ot/emp-ot.h"

/*
 * The base class of Semi-Honest 2PC Party
 */
namespace emp {
    template<typename IO>
    class Party {
    protected:
        long private_input{};   // The private input of this party
        long share_0{};         // The additive share for ALICE
        long share_1{};         // The additive share for BOB

        // The secret sharing field is 2^32
        const static long BASE = 1;
        const static long MOD = (BASE << 32);

        // The mod operation, % in C++ does not work
        // because it computes "reminder" instead of "modulus"
        static long mod(long a) {
            return (a % MOD + MOD) % MOD;
        }

    public:
        int party{};        // Party ID; 1: ALICE, 2: BOB
        PRG shared_prg;     // Random generator

        IO* io_Alice = nullptr;     // the channel for ALICE
        IO* io_Bob = nullptr;       // the channel for BOB

        Party(int party , IO * io_Alice, IO * io_Bob, int input) {
            // initialise the party parameter
            this->party = party;
            this->io_Alice = io_Alice;
            this->io_Bob = io_Bob;
            this->private_input = input;

            // generate a random number as share_0
            shared_prg.random_data((void *) &share_0, sizeof(int));
            // compute (input - share_0) mod 2^32 as share_1
            share_1 = mod(private_input - share_0);
        }

        // functions to be implemented for the MPC protocol
        virtual void share() = 0;
        virtual void compute() = 0;
        virtual long reveal() = 0;
    };
}

#endif //SECRET_SHARING_ADDITIVE_PARTY_H
