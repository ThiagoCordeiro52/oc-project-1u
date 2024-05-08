#include <systemc.h>
#include "pc.cpp"

SC_MODULE(ProgramCounterTestbench) {
  	// Esse clock deverá ser único
  	// Fazer integração dos fios
    sc_clock clock; 
    sc_signal<bool> reset;
    sc_signal<bool> enable;
    sc_signal<bool> jump;
    sc_signal<sc_uint<32>> jumpAddress;
    sc_signal<sc_uint<32>> pcAddress;

    ProgramCounter pc;

    SC_CTOR(ProgramCounterTestbench) : clock("clock", 10, SC_NS), pc("PC") {
        pc.clock(clock);
        pc.reset(reset);
        pc.enable(enable);
        pc.jump(jump);
        pc.jumpAddress(jumpAddress);
        pc.address(pcAddress);

        reset = 0;
        enable = 1; 

      	// Essas duas funções DEVEM ser sensitive clock para sincronizar
        SC_THREAD(driveInputs);
        sensitive << clock;

        SC_METHOD(monitorOutputs);
        sensitive << clock;
    }

    void driveInputs() {
        reset = 1;
        wait(1, SC_NS);
        reset = 0;

        enable = 1;

        wait(10, SC_NS);

        jump = 1;
        jumpAddress = 0x10; // Endereço fictício
        wait(1, SC_NS);
        jump = 0;

        wait(20, SC_NS);

        sc_stop();
    }

    void monitorOutputs() {
        std::cout << "Time " << sc_time_stamp() << " - Address: " << pcAddress <<std::endl;
    }
};


int sc_main(int argc, char* argv[]) {
    ProgramCounterTestbench testbench("Testbench");

    sc_start();

    return 0;
}

