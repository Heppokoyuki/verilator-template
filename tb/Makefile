TOP = top
PACKAGES = 
INTERFACE = 
VFLAGS = -Wall --cc --trace-fst --trace-params --trace-structs --trace-underscore
CFLAGS= '-std=c++17 -W -Wall'
VC = verilator
CC = g++
OBJDIR=objdir
EXECUTABLE=V$(TOP)

.PHONY: all $(OBJDIR)/$(EXECUTABLE) view clean
.SILENT: all $(OBJDIR)/$(EXECUTABLE) $(OBJDIR)/V$(TOP).mk

all: $(OBJDIR)/$(EXECUTABLE)
	echo "Hi! Let's get simulation!" ; \
	cd $(OBJDIR) ; \
	./$(EXECUTABLE)

$(OBJDIR)/$(EXECUTABLE): $(OBJDIR)/V$(TOP).mk
	cd $(OBJDIR) ; \
	echo "compiling" ; \
	make -j -f V$(TOP).mk $(EXECUTABLE)

$(OBJDIR)/V$(TOP).mk:
	echo "verilating" ; \
	verilator $(VFLAGS) --Mdir $(OBJDIR) --cc $(PACKAGES) $(INTERFACE) --top-module $(TOP) $(TOP).sv --exe top_tb.cpp -I../src -CFLAGS $(CFLAGS)

view:
	cd $(OBJDIR) ; gtkwave wave.fst &

clean:
	rm -r $(OBJDIR)
