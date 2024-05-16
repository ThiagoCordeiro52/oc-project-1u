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

int readInstruction(const std::string& instruction) {
    int decodedInstruction = 0;

    if (instruction == "add") {
        decodedInstruction = 0x20;
    } else if (instruction == "sub") {
        decodedInstruction = 0x22;
    }

    return decodedInstruction;
}

void executeMIPSInstruction(const std::string& instruction, RegisterDatabase& regDB, InstructionMemory& imem, MUX& mux, ALU& alu, sc_signal<sc_dt::sc_uint<32>>& pc) {
    std::istringstream iss(instruction);
    std::string opcode, rd, rs, rt;
    int immediate;

    iss >> opcode;

    if (opcode == "addi") {
        iss >> rt >> rs >> immediate;
        sc_uint<32> rs_value = regDB.registers[std::stoi(rs.substr(1))];
        sc_uint<32> result = rs_value + immediate;
        regDB.registers[std::stoi(rt.substr(1))] = result;
    }

    pc.write(pc.read() + 4); 
}

int sc_main(int argc, char* argv[]) {

    RegisterDatabase regDB("RegDB");
    InstructionMemory imem("IMem");
    MUX mux("MUX");
    ALU alu("ALU");
    sc_signal<sc_dt::sc_uint<32>> pc("PC");  

    Memory mem("Mem");

    imem.address_in(pc);
    mux.operand2(mem.data);
    mux.operand3(pc);

    alu.operand1(mux.result);
    alu.operand2(mem.data);

    std::ifstream file_input("examples/raiz_quadrada.asm");
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
        int instruction_int = readInstruction(instruction);
        imem.instruction_memory[i] = instruction_int;
    }

    sc_clock clock("clock", 10, SC_NS);

    for (int i = 0; i < instructions.size(); ++i) {
        std::string instruction = instructions[i];
        executeMIPSInstruction(instruction, regDB, imem, mux, alu, pc);
        sc_start(10, SC_NS);  
    }

    std::cout << "Final Register File State:" << std::endl;
    for (int i = 0; i < 32; ++i) {
        std::cout << "$" << i << ": " << regDB.registers[i] << std::endl;
    }

    return 0;
}
