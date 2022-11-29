NFLAGS = -fopenmp -O3 -fstdlib -faligned -fno-math-errno -fno-signed-zeros -ffinite-math-only -fno-rounding-math -fprefetch -floop-apb-conditional-loads -fstrict-aliasing -faligned -ffast-math -mcpu=elbrus-v5

all:
	l++ $(NFLAGS) Elbrus.o ElbrusFunc.o Func.o -o a.out

Elbrus.o: Elbrus.cpp
	l++ $(NFLAGS) -c Elbrus.cpp

Func.o: Func.cpp
	l++ $(NFLAGS) -c Func.cpp

ElbrusFunc.o:
	l++ $(NFLAGS) -c ElbrusFunc.cpp

clean:
	rm -rf *.o a.out

asm:
	l++ -ffast -ffast-math -faligned -O3 -mcpu=elbrus-v5 -S El_Func.cpp
