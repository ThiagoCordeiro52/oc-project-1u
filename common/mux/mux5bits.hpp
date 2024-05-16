#include <systemc.h>

SC_MODULE(MUX) {
    sc_in<sc_uint<5>> operand1;
    sc_in<sc_uint<5>> operand2;
    sc_in<sc_uint<5>> operand3;
    sc_out<sc_uint<5>> result;
    sc_out<bool> zero;

    void mux_process() {
        sc_uint<5> a = operand1.read();
        sc_uint<5> b = operand2.read();
        sc_uint<5> s = operand3.read();
        sc_uint<5> output;

        switch (operand3.read()) {
            case 0:  
                output = a;
                break;
            case 1: 
                output = b;
                break;
            default:
                output = 0;
                break;
        }

        result.write(output);
        zero.write(output == 0);
    }

    SC_CTOR(MUX) {
        SC_METHOD(mux_process);
        sensitive << operand1 << operand2 << operand3;
    }
};