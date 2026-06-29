all:
	gcc SIM.c -o SIM.exe -I./SRC/include -L./SRC/lib -lmingw32 -lSDL2 -mconsole