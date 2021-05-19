//
// Created by shangqi on 2021/1/28.
//

#ifndef SECRET_SHARING_ADDITIVE_PARTY_H
#define SECRET_SHARING_ADDITIVE_PARTY_H

/*
 * The implementation of additive sharing scheme
 */
namespace emp {
    template<typename IO>
    class AdditiveParty : public Party<IO> {
    private:
        // the share of secrets
        long local_share = 0;
        long remote_share = 0;
        // the results of addition
        long local_result = 0;
        long remote_result = 0;
    public:
        AdditiveParty(int party, IO* io_Alice, IO* io_Bob, int input) : Party<IO>(party, io_Alice, io_Bob, input) {
            // set the local share by referring to the party
            // ALICE keeps share_0, BOB keeps share_1
            if(this->party == ALICE) {
                local_share = this->share_0;
            } else {
                local_share = this->share_1;
            }
        }

        // share the additive share of local secret to the counter-party
        void share() override {
            if(this->party == ALICE) {
                // ALICE sends share_1 to BOB
                this->io_Bob->send_data((void *)&this->share_1, sizeof(long));
                // flush the channel is necessary after sending data via Net I/O
                // otherwise, the message will stay in the local buffer
                fflush(this->io_Bob->stream);
            } else {
                // BOB sends share_0 to ALICE
                this->io_Alice->send_data((void *)&this->share_0, sizeof(long));
                fflush(this->io_Alice->stream);
            }
        }

        // compute the addition of shares
        void compute() override {
            // receive the remote share from the corresponding channel
            if(this->party == ALICE) {
                this->io_Alice->recv_data((void*) &remote_share, sizeof(long));
            } else {
                this->io_Bob->recv_data((void*) &remote_share, sizeof(long));
            }
            // compute the <c>_i (local result) = (<a>_i (local_share) + <b>_i (remote_share)) mod 2^32
            local_result = this->mod(local_share + remote_share);
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
    inline AdditiveParty<NetIO> setup_additive_party(int party, IO *io_Alice, IO *io_Bob, int i) {
        return AdditiveParty<IO>(party, io_Alice, io_Bob, i);
    }
}
#endif //SECRET_SHARING_ADDITIVE_PARTY_H
