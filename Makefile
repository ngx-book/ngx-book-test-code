all:
	gcc -Wall -g -o request_timeout request_timeout.c

clean:
	rm -f request_timeout
