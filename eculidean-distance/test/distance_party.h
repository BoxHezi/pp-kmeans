//
// Created by shangqi on 2021/4/4.
//

#ifndef ECULIDEAN_DISTANCE_DISTANCE_PARTY_H
#define ECULIDEAN_DISTANCE_DISTANCE_PARTY_H

#include "party.h"

namespace emp {
    template<typename IO>
    class DistanceParty : public Party<IO> {
    private:
        // the share of multiplication triplets
        long x = 0;
        long y = 0;
        long z = 0;

        long e = 0;
        long f = 0;
        // the share of secrets
        long local_share{};
        long remote_share{};
        // the results of addition
        long local_result = 0;
        long remote_result = 0;

    public:
        // OT instance
        IKNP<IO> * ot_Alice = nullptr;
        IKNP<IO> * ot_Bob = nullptr;

        DistanceParty(int party, IO * io_Alice, IO * io_Bob, int input)
                : Party<IO>(party, io_Alice, io_Bob, input) {
            // set the local share by referring to the party
            // ALICE keeps share_0, BOB keeps share_1
            if(this->party == ALICE) {
                local_share = this->share_0;
            } else {
                local_share = this->share_1;
            }
            // setup Oblivious Transfer (OT) instance
            this->ot_Alice = new IKNP<IO>(io_Alice);
            this->ot_Bob = new IKNP<IO>(io_Bob);
            if(this->party == ALICE) {
                this->ot_Alice->setup_send();
                // flush the channel after receiving the OT setup information
                this->ot_Bob->setup_recv();
                fflush(this->io_Bob->stream);
            } else {
                this->ot_Alice->setup_recv();
                fflush(this->io_Alice->stream);
                this->ot_Bob->setup_send();
            }
        }

        /*
         * Share of multiplication protocol has two phase:
         * The first stage is offline phase, which runs OT protocol
         * to generate multiplication triplets.
         * The second stage is online phase, which exchanges the additive
         * share of local secret as the addition protocol
         */
        void share() override {
            /* offline phase
             * Generate three shares <x>, <y> and <z>, where z = x * y.
             * By given the share of x and y (random value selected by each party independently),
             * z can be computed as z = <x>_0 * <y>_0 + <x>_0 * <y>_1 + <x>_1 * <y>_0 + <x>_1 * <y>_1.
             * Each party can easily compute <x>_i * <y>_i locally, and use OT to compute <<x>_0 * <y>_1>_i and
             * <<x>_1 * <y>_0>_i.
             * Thus, each party will have the share of z: <z>_i = <x>_i * <y>_i + <<x>_0 * <y>_1>_i + <<x>_1 * <y>_0>_i
             * without knowing the actual x and y.
             * P.S., the modulo operation is omitted in the above description, but it is still included in the code.
             */
            // randomly generates the share of x and y
            this->shared_prg.random_data((void *) &x, sizeof(int));
            this->shared_prg.random_data((void *) &y, sizeof(int));
            x = this->mod(x);
            y = this->mod(y);
            // local_x * remote_y
            long local_xy = 0;
            // remote_x * local_y
            long remote_xy = 0;
            // process the x in bit
            block block_r[32];
            block block_f_x[32];
            block block_yx[32];
            for (int i = 0; i < 32; ++i) {
                // generate OT pair for x (r and f_x = (x * 2^i + r) mod 2^32)
                long r = 0;
                this->shared_prg.random_data((void*) &r, sizeof(int));
                r = this->mod(r);
                long f_x = this->mod(x << i);
                f_x = this->mod(f_x + r);
                block_r[i] = makeBlock(0, r);
                block_f_x[i] = makeBlock(0, f_x);
                // set local_x * remote_y = the sum of -r
                local_xy = this->mod(local_xy + this->mod(-r));
            }
            // parse y as bits
            bool bool_y[32];
            int_to_bool<int>(bool_y, y, 32);
            // use each bit of y to oblivious transfer x
            if(this->party == ALICE) {
                this->ot_Alice->send(block_r, block_f_x, 32);
                // flush the channel is necessary after sending data via Net I/O
                // otherwise, the message will stay in the local buffer
                fflush(this->io_Alice->stream);
                this->ot_Bob->recv(block_yx, bool_y, 32);
            } else {
                this->ot_Alice->recv(block_yx, bool_y, 32);
                this->ot_Bob->send(block_r, block_f_x, 32);
                fflush(this->io_Bob->stream);
            }
            // compute remote_xy = Sigma(y[i] * x * 2^i + r) = y * x + r
            for (auto & i : block_yx) {
                remote_xy =  this->mod(remote_xy + *((int *)&i));
            }
            // compute z
            z = this->mod(x * y + local_xy + remote_xy);
            // online phase
            if(this->party == ALICE) {
                this->io_Bob->send_data((void *)&this->share_1, sizeof(long));
                fflush(this->io_Bob->stream);
            } else {
                this->io_Alice->send_data((void *)&this->share_0, sizeof(long));
                fflush(this->io_Alice->stream);
            }
        }

        // compute the multiplication
        void compute() override {
            long local_e = 0;
            long local_f = 0;
            long remote_e = 0;
            long remote_f = 0;
            if(this->party == ALICE) {
                this->io_Alice->recv_data((void*) &remote_share, sizeof(long));
                // compute <p_i> - <q_i> for each coordinate
                long delta;
                delta = local_share - remote_share;
                // <e>_0 = <delta_ALICE>_0 - <x>_0
                local_e = this->mod(delta - x);
                // <f>_0 = <delta_BOB>_0 - <y>_0
                local_f = this->mod(delta - y);
                // send <e>_0 and <f>_0 to the counter-party
                this->io_Bob->send_data((void *)&local_e, sizeof(long));
                this->io_Bob->send_data((void *)&local_f, sizeof(long));
                fflush(this->io_Bob->stream);
                // receive <e>_1 and <f>_1
                this->io_Alice->recv_data((void*) &remote_e, sizeof(long));
                this->io_Alice->recv_data((void*) &remote_f, sizeof(long));
            } else {
                this->io_Bob->recv_data((void*) &remote_share, sizeof(long));
                // compute <p_i> - <q_i> for each coordinate
                long delta;
                delta = remote_share - local_share;
                // <e>_1 = <delta_ALICE>_1 - <x>_1
                local_e = this->mod(delta - x);
                // <f>_1 = <delta_BOB>_1 - <y>_1
                local_f = this->mod(delta - y);
                // send <e>_1 and <f>_1 to the counter-party
                this->io_Alice->send_data((void *)&local_e, sizeof(long));
                this->io_Alice->send_data((void *)&local_f, sizeof(long));
                fflush(this->io_Alice->stream);
                // receive <e>_0 and <f>_0
                this->io_Bob->recv_data((void*) &remote_e, sizeof(long));
                this->io_Bob->recv_data((void*) &remote_f, sizeof(long));
            }
            // compute e = (<e>_0 + <e>_1) mod 2^32
            this->e = this->mod(local_e + remote_e);
            // compute f = (<f>_0 + <f>_1) mod 2^32
            this->f = this->mod(local_f + remote_f);
            // compute the final result <c>_i = (i - 1) * e * f + f * <x>_i + e * <y>_i + <z>_i
            this->local_result = this->mod((this->party - 1) * e * f + f * x + e * y + z);
        }

        // reveal the final result to the counter-party
        long reveal() override {
            // exchange the local result
            if(this->party == ALICE) {
                this->io_Bob->send_data((void *)&this->local_result, sizeof(long));
                fflush(this->io_Bob->stream);
                this->io_Alice->recv_data((void *)&this->remote_result, sizeof(long));
            } else {
                this->io_Alice->send_data((void *)&this->local_result, sizeof(long));
                fflush(this->io_Alice->stream);
                this->io_Bob->recv_data((void *)&this->remote_result, sizeof(long));
            }
            // return (<c>_0 + <c>_1) mod 2^32 as the final output of the protocol
            return this->mod(local_result + remote_result);
        }
    };

    template<typename IO>
    inline DistanceParty<NetIO> setup_distance_party(int party, IO *io_Alice, IO *io_Bob, int i) {
        return DistanceParty<IO>(party, io_Alice, io_Bob, i);
    }
}

#endif //ECULIDEAN_DISTANCE_DISTANCE_PARTY_H
