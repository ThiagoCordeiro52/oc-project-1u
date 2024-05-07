#include <systemc.h>
#include <iostream>
#include "adder.cpp"

void testbench_process() {
    // Signals
    sc_signal<sc_logic> a, b, cin, sum, cout;

    BIT_ADDER my_adder("my_adder");
    my_adder.a(a);
    my_adder.b(b);
    my_adder.cin(cin);
    my_adder.sum(sum);
    my_adder.cout(cout);

    // Create a VCD trace file
    // Isso daqui está relacionado aos testes, ainda não sei bem como funciona
    sc_trace_file *wf = sc_create_vcd_trace_file("adder_waveforms");
    sc_trace(wf, a, "a");
    sc_trace(wf, b, "b");
    sc_trace(wf, cin, "cin");
    sc_trace(wf, sum, "sum");
    sc_trace(wf, cout, "cout");

    const int num_tests = 4;
    sc_logic test_a[num_tests] = {SC_LOGIC_0, SC_LOGIC_1, SC_LOGIC_0, SC_LOGIC_1};
    sc_logic test_b[num_tests] = {SC_LOGIC_0, SC_LOGIC_0, SC_LOGIC_1, SC_LOGIC_1};
    sc_logic test_cin[num_tests] = {SC_LOGIC_0, SC_LOGIC_1, SC_LOGIC_1, SC_LOGIC_0};

    for (int i = 0; i < num_tests; ++i) {
        a = test_a[i];
        b = test_b[i];
        cin = test_cin[i];

        sc_start(1, SC_NS);

        std::cout << "Test case: " << i+1 << " --> " << sc_time_stamp() << "\n";
        std::cout << "a: " << a << ", b: " << b << ", cin: " << cin << std::endl;

        // No EDA é possível ativar a opção EPWave
        sc_start(10, SC_NS);

        // O resultado está em binário
        std::cout << "sum: " << sum << ", cout: " << cout << std::endl;
    }

    sc_close_vcd_trace_file(wf);
}

int sc_main(int argc, char* argv[]) {
    testbench_process();

    return 0;
}
