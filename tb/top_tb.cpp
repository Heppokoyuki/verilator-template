#include <iostream>
#include <verilated.h>
#include <verilated_fst_c.h>
#include "Vtop.h"

int time_counter = 0;

int
main(int argc, char **argv)
{
    Verilated::commandArgs(argc, argv);
    Vtop *dut = new Vtop();

    Verilated::traceEverOn(true);
    VerilatedFstC* tfp = new VerilatedFstC;

    dut->trace(tfp, 100);
    tfp->open("wave.fst");
    
    //Initialize
    dut->reset_n = 0;
    dut->clk = 0;
    dut->en = 0;

    while (time_counter < 100) {
        dut->eval();
        tfp->dump(time_counter);
        time_counter++;
    }
    dut->reset_n = 1;
    
    int cycle = 0;
    while (time_counter < 500) {
        if((time_counter % 5) == 0) {
            dut->clk = !dut->clk;
        }
        if((time_counter % 10) == 0) {
            cycle++;
        }

        if(cycle % 5 == 0) {
            dut->en = 1;
        }
        else {
            dut->en = 0;
        }

        dut->eval();
        tfp->dump(time_counter);
        time_counter++;
    }

    dut->final();
    tfp->close();
}
