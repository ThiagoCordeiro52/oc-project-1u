#include <systemc.h>
#include "mux.cpp"

void testbench_process() {
    sc_signal<sc_uint<32>> operand1;
    sc_signal<sc_uint<32>> operand2;
    sc_signal<sc_uint<32>> operand3;
    sc_signal<sc_uint<32>> result;
    sc_signal<bool> zero;

    MUX mux("mux");
    mux.operand1(operand1);
    mux.operand2(operand2);
    mux.operand3(operand3);
    mux.result(result);
    mux.zero(zero);

    sc_trace_file *wf = sc_create_vcd_trace_file("mux_waveforms");
    sc_trace(wf, operand1, "operand1");
    sc_trace(wf, operand2, "operand2");
    sc_trace(wf, operand3, "operand3");
    sc_trace(wf, result, "result");
    sc_trace(wf, zero, "zero");

    const int num_tests = 5;
    sc_uint<32> test_operands[num_tests][3] = {
        {0, 0, 0},
        {1, 0, 0},
        {0, 0, 1},
        {0, 1, 1},
        {0, 1, 1}
    };
    sc_uint<2> test_controls[num_tests] = {0, 1, 2, 2, 3};
    for (int i = 0; i < num_tests; ++i) {
        operand1 = test_operands[i][0];
        operand2 = test_operands[i][1];
        operand3 = test_operands[i][2]; 
        sc_start(10, SC_NS);

        std::cout << "@" << sc_time_stamp() << " Starting MUX simulation for Test Case " << i+1 << "\n";
        std::cout << "A: " << operand1 << std::endl;
        std::cout << "B: " << operand2 << std::endl;
        std::cout << "S: " << operand3 << std::endl;

        sc_start(1, SC_NS);

        std::cout << "MUX Result: " << result << std::endl;
        std::cout << "Zero Flag: " << zero << std::endl;
    }

    sc_close_vcd_trace_file(wf);
}

int sc_main(int argc, char* argv[]) {
    testbench_process();

    return 0;
}
