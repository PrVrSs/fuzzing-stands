all: vulnserver

vulnserver:
	gcc -g -O0 -fno-stack-protector -fno-omit-frame-pointer -ftest-coverage -fprofile-arcs server.c -o vulnserver

clean:
	rm vulnserver
