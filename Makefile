STD = -std=c99

OPTIONS = -Wall -Wpedantic -Wno-unused-result -O0 -g

LIBRARIES = -lm conectorC/lib/libmysql.lib

main : main.c
	gcc $(STD) $(OPTIONS) main.c -o main $(LIBRARIES)