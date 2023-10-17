CC = clang

CFLAGS = -Wall -Werror -O1 -pthread

build: fault server

fault: pg_fault.c
	$(CC) pg_fault.c -o fault $(CFLAGS)

server: pg_server.c
	$(CC) pg_server.c -o pg_server $(CFLAGS)

# need to run as sudo for it to work correctly
run : SHELL:=/bin/bash
run:
	@if ! [ "$(shell id -u)" = 0 ]; then \
		echo "You must be in root"; \
	else \
		./pg_server & ./fault; \
	fi 

# Useful for when the server is in the background
teardown : SHELL:=/bin/bash
teardown:
	@ if ! [ "$(shell id -u)" = 0 ]; then \
		 echo "You must be in root"; \
	 elif pgrep pg_server; then \
		 pkill pg_server; \
	 fi 

clean:
	@ if [ "$(shell id -u)" = 0 ]; then \
		$(MAKE) teardown; \
		 fi
	rm -f fault pg_server

