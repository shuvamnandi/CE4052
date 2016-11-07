all: main.c
	gcc -Wall -o main main.c led.c buzzer.c timeout.c -lwiringPi -lpthread
	sudo ./main 

clean: main.c
	rm -rf main
