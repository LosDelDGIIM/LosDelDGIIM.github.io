.SUFFIXES:
.PHONY: x1, x2, x3, clean

comp:= mpicxx -std=c++11 -Wall

x1: holamundo_mpi_exe
	mpirun -oversubscribe -np 5    ./$<

x2: sendrecv1_mpi_exe
	mpirun -oversubscribe -np 2 ./$<

x3: sendrecv2_mpi_exe
	mpirun -oversubscribe -np 5 ./$<

x4: ejemplo_probe_mpi_exe
	mpirun -oversubscribe -np 10 ./$<

x4b: ejemplo_probe_v2_mpi_exe
	mpirun -oversubscribe -np 10 ./$<

x5: ejemplo_iprobe_mpi_exe
	mpirun -oversubscribe -np 10 ./$<

x6: intercambio_sincrono_mpi_exe
	mpirun -oversubscribe -np 8 ./$<

x7: intercambio_nobloq_mpi_exe
	mpirun -oversubscribe -np 8 ./$<

%_mpi_exe: %.cpp
	$(comp) $< -o $@

clean:
	rm -f *_exe
