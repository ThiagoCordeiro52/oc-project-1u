#include <systemc.h>
#include "common/pc/pc.h"
#include "common/ula/ula.h"
#include "common/registers/registers.h"
#include "common/instruction-memory/instruction-memory.h"
#include "common/data-memory/data-memory.h"
#include "common/mux/mux.h"
#include "pipelines/1-fetch.h"
#include "pipelines/2-decode.h"
#include "pipelines/3-execute.h"
#include "pipelines/4-access.h"

SC_MODULE(Testbench) {

    ProgramCounter pc;
    ALU alu;
    Register reg1, reg2;
    RegisterDatabase regDB;
    InstructionMemory imem;
    Memory mem;
    MUX mux;
    Fetch fetch;
    Decode decode;
    Execute execute;
    Access access;

    // Signals
    sc_clock clock;
    sc_signal<bool> reset, enable, jump;
    sc_signal<sc_uint<32>> jumpAddress, pc_address;
    sc_signal<sc_uint<32>> operand1, operand2, alu_control, alu_result;
    sc_signal<bool> alu_zero;
    sc_signal<sc_logic> a, b, cin;
    sc_signal<sc_logic> sum, cout;
    sc_signal<sc_uint<32>> reg1_data_in, reg1_data_out;
    sc_signal<sc_uint<32>> regDB_reg_id, regDB_data_in, regDB_data_out;
    sc_signal<sc_uint<32>> imem_address_in, imem_instruction_out;
    sc_signal<bool> mem_clock, mem_write_enable, mem_read_enable;
    sc_signal<sc_uint<32>> mem_address, mem_data;
    sc_signal<sc_uint<32>> mux_operand1, mux_operand2, mux_operand3, mux_result;
    sc_signal<bool> mux_zero;

}