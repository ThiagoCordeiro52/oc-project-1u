#include "systemc.h"
#include "sysc/utils/sc_vector.h"

SC_MODULE(fetch) { // Ok
    sc_in_clk clock;
    sc_in<sc_uint<32>> input;
    sc_out<sc_uint<32>> output;
    void next();

    SC_CTOR(fetch) {
        SC_METHOD(next);
        sensitive << clock.pos();
    }
};

void fetch::next() {
    output.write(input.read());
}