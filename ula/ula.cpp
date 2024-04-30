#include <systemc.h>

SC_MODULE(ALU) {
    sc_in<sc_uint<32>> operand1;
    sc_in<sc_uint<32>> operand2;
    sc_in<sc_uint<3>> alu_control; // -> Check
    sc_out<sc_uint<32>> result;
    sc_out<bool> zero;

    void alu_process() {
        sc_uint<32> a = operand1.read();
        sc_uint<32> b = operand2.read();
        sc_uint<32> output;

        switch (alu_control.read()) {
            case 0:  
                output = a + b;
                break;
            case 1: 
                output = a - b;
                break;
            case 2:  
                output = a & b; // and
                break;
            case 3:
                output = a | b; // or
                break;
            default:
                output = 0;
                break;
        }

        result.write(output);
        zero.write(output == 0);
    }

    SC_CTOR(ALU) {
        SC_METHOD(alu_process);
        sensitive << operand1 << operand2 << alu_control;
    }
};
