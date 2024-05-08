#include <systemc.h>

SC_MODULE(BIT_ADDER) {
    sc_in<sc_logic> a, b, cin;
    sc_out<sc_logic> sum, cout;

    SC_CTOR(BIT_ADDER) {
        SC_METHOD(process);
        sensitive << a << b << cin;
    }

    void process() {
        sc_logic aXORb = a.read() ^ b.read();         
        sc_logic aANDb = a.read() & b.read();         
        sc_logic cinANDaXORb = cin.read() & aXORb;    

        sum = aXORb ^ cin.read();
        cout = aANDb | cinANDaXORb;   // carry out                 
    }
};
