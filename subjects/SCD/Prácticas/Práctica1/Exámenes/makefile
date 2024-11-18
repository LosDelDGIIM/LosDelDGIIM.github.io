.SUFFIXES:
.PHONY: x, pc1, clean

compilador:=g++
opcionesc:= -std=c++11 -pthread -Wfatal-errors
scd_path:=../../Práctica1/Código

x: monitor_em_exe
	./$<

pc1: prodcons1_su_exe
	./$<

%_exe: %.cpp $(scd_path)/scd.cpp $(scd_path)/scd.h
	$(compilador) $(opcionesc) -o $@ $< $(scd_path)/scd.cpp


clean:
	rm -f *_exe
