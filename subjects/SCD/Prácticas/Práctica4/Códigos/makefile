.SUFFIXES:
.PHONY:    pc,pc2,pcm,fp,f,fi,fc,clean

compilador := g++ -std=c++11
flagsc     := -Wall

r: relojes_exe
	./$<

t: tiempos_exe
	./$<

e1: ejecutivo1_exe
	./$<

e1c: ejecutivo1-compr_exe
	./$<

e2: ejecutivo2_exe
	./$<

%_exe: %.cpp
	$(compilador) $(flagsc) -o $@ $<

clean:
	rm -rf *_exe *.dSYM
