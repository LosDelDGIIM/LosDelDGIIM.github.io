.SUFFIXES:
.PHONY: x, pc1, clean

compilador:=g++
opcionesc:= -std=c++11 -pthread -Wfatal-errors

x: monitor_em_exe
	./$<

pc1: prodcons1_su_exe
	./$<

pc1b: prodcons1_su_fifo_exe
	./$<

%_exe: %.cpp scd.cpp scd.h
	$(compilador) $(opcionesc)  -o $@ $< scd.cpp

clean:
	rm -f *_exe
