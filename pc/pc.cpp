#include <systemc.h>

SC_MODULE(ProgramCounter) {
    sc_in<bool> clock;             
    sc_in<bool> reset;              
    sc_in<bool> enable;             
    sc_in<bool> jump;               
    sc_in<sc_uint<32>> jumpAddress; 

    sc_out<sc_uint<32>> address;    

    sc_uint<32> counter;

    SC_CTOR(ProgramCounter) : counter(0) {
        SC_METHOD(counterProcess);
        sensitive << clock.pos();

        SC_METHOD(resetProcess);
        sensitive << reset;
    }

    void counterProcess() {
        if (reset.read()) {
            counter = 0;
        } else if (enable.read()) {
            if (jump.read()) {
                counter = jumpAddress.read(); 
            } else {
                counter = counter + 1;      
            }
        }
        address.write(counter); 
    }

    void resetProcess() {
        if (reset.read()) {
            counter = 0;
        }
    }
};
