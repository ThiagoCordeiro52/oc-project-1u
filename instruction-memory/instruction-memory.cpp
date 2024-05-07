#include <systemc.h>

#define INSTRUCTION_MEMORY_SIZE 1024

SC_MODULE(InstructionMemory)
{
  sc_in<bool> clock;
  sc_in<sc_uint<32>> address_in;
  sc_out<sc_uint<32>> instruction_out;

  sc_uint<32> instruction_memory[INSTRUCTION_MEMORY_SIZE];

  SC_CTOR(InstructionMemory)
  {
    SC_METHOD(read_instruction);
    sensitive << address_in;
  }

  void read_instruction()
  {
    if (address_in.read() >= 0 && address_in.read() < INSTRUCTION_MEMORY_SIZE)
    {
      instruction_out.write(instruction_memory[address_in.read()]);
    }
    else
    {
      instruction_out.write(0);
      cout << "Invalid instruction address: " << address_in.read() << endl;
    }
  }
};