#include <systemc.h>
#include <iostream>
#include "ula.cpp" 

void testbench_process() {
    sc_signal<sc_uint<32>> operand1;
    sc_signal<sc_uint<32>> operand2;
    sc_signal<sc_uint<3>> alu_control;
    sc_signal<sc_uint<32>> result;
    sc_signal<bool> zero;

    ALU alu("alu");
    alu.operand1(operand1);
    alu.operand2(operand2);
    alu.alu_control(alu_control);
    alu.result(result);
    alu.zero(zero);

    sc_trace_file *wf = sc_create_vcd_trace_file("alu_waveforms");
    sc_trace(wf, operand1, "operand1");
    sc_trace(wf, operand2, "operand2");
    sc_trace(wf, alu_control, "alu_control");
    sc_trace(wf, result, "result");
    sc_trace(wf, zero, "zero");

    // Test cases for SUM, SUB, AND, and OR
    const int num_tests = 5;
    sc_uint<32> test_operands[num_tests][2] = {
        {15, 10},
        {15, 10},
        {1, 0},
        {0, 1},
        {0, 1}
    };
    sc_uint<3> test_controls[num_tests] = {0, 1, 2, 2, 3};
    for (int i = 0; i < num_tests; ++i) {
        operand1 = test_operands[i][0];
        operand2 = test_operands[i][1];
        alu_control = test_controls[i];
      	sc_start(10, SC_NS);

        std::cout << "@" << sc_time_stamp() << " Starting ALU simulation for Test Case " << i+1 << "\n";
        std::cout << "Operand1: " << operand1 << std::endl;
        std::cout << "Operand2: " << operand2 << std::endl;
        std::cout << "ALU Control: " << alu_control << std::endl;

        sc_start(1, SC_NS);

        std::cout << "ALU Result: " << result << std::endl;
        std::cout << "Zero Flag: " << zero << std::endl;
    }

    // Close VCD trace file
    sc_close_vcd_trace_file(wf);
}

int sc_main(int argc, char* argv[]) {

  testbench_process();

    return 0;
}
