#include <systemc.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "common/pc/pc.hpp"
#include "common/ula/ula.hpp"
#include "common/registers/registers.hpp"
#include "common/instruction-memory/instruction-memory.hpp"
#include "common/data-memory/data-memory.hpp"
#include "common/mux/mux.hpp"

void executeMIPSInstruction(const std::string& instruction,
                            RegisterDatabase& regDB,
                            InstructionMemory& imem,
                            MUX& mux,
                            ALU& alu,
                            ProgramCounter& pc)
{
    std::istringstream iss(instruction);
    std::string opcode, rd, rs, rt;
    int immediate;

    iss >> opcode;

    if (opcode == "add") {
        iss >> rd >> rs >> rt;
        int rs_index = std::stoi(rs.substr(1));
        int rt_index = std::stoi(rt.substr(1));

        // Read register values from RegisterDatabase
        sc_uint<32> rs_value = regDB.registers[rs_index];
        sc_uint<32> rt_value = regDB.registers[rt_index];

        // Set operand inputs for MUX
        mux.operand1.write(rs_value);
        mux.operand2.write(rt_value);
        mux.operand3.write(0); // select operand1 for output

        // Trigger MUX and ALU operations
        mux.compute();
        alu.operand1.write(mux.result.read());
        alu.operand2.write(rt_value);
        alu.alu_control.write(0); // ALU addition operation

        // Perform ALU operation and store result in RegisterDatabase
        alu.compute();
        sc_uint<32> result = alu.result.read();
        regDB.registers[std::stoi(rd.substr(1))] = result;
    }
    // Increment Program Counter
    pc.enable(true);
}

int sc_main(int argc, char* argv[]) {

    RegisterDatabase regDB("RegDB");
    InstructionMemory imem("IMem");
    MUX mux("MUX");
    ALU alu("ALU");
    ProgramCounter pc("PC");
    Memory mem("Mem");

    imem.clock(pc.clock);
    imem.address_in(pc.address);
    imem.instruction_out(mux.operand3);
    mux.operand2(mem.data);
    mux.result(alu.operand1);
    alu.operand2(mem.data);

    std::ifstream file_input("input.asm");
    if (!file_input.is_open()) {
        std::cerr << "Error: Unable to open input file" << std::endl;
        return 1;
    }

    std::vector<std::string> instructions;
    std::string line;
    while (std::getline(file_input, line)) {
        instructions.push_back(line);
    }
    file_input.close();

    for (int i = 0; i < instructions.size(); ++i) {
        std::string instruction = instructions[i];
        executeMIPSInstruction(instruction, regDB, imem, mux, alu, pc);
        std::cout << "Executing instruction: " << instruction << std::endl;
    }

    std::cout << "Final Register File State:" << std::endl;
    for (int i = 0; i < 32; ++i) {
        std::cout << "$" << i << ": " << regDB.registers[i] << std::endl;
    }

    return 0;
}
