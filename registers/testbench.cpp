#include <systemc.h>
#include "design.cpp"

int sc_main(int argc, char* argv[]) {
    Register reg("register");
    RegisterDatabase regDb("registerDatabase");

    sc_clock clock("clock", 10, SC_NS);
    sc_signal<bool> reset, enable;
    sc_signal<sc_uint<32>> data_in, reg_id, reg_data, regDb_data_out;

    reg.clock(clock);
    reg.reset(reset);
    reg.enable(enable);
    reg.data_in(data_in);
    reg.data_out(reg_data);

    regDb.reg_id(reg_id);
    regDb.data_in(reg_data);
    regDb.data_out(regDb_data_out);

    sc_start(100, SC_NS);
  
    for (int i = 0; i < 5; ++i) {
          sc_uint<32> id = rand() % 10;
          sc_uint<32> data = rand() % 100; 

          reg_id.write(id);
          data_in.write(data);
          enable.write(true);

          // Wait()
          sc_start(10, SC_NS);

          enable.write(false);

          std::cout << "Register values after update " << i + 1 << ":\n";
          for (int j = 0; j < 10; ++j) {
              std::cout << "Register " << j << ": " << regDb.registers[j] << "\n";
          }
          std::cout << std::endl;
      }

    return 0;
}