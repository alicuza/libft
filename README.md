I am not sure what the functional difference between clean and fclean is. I thought that, since clean keeps the target, it make doesnt need to rebuild. Here is how to achieve this behaviour:

.SECONDARY can be used to avoid redundant rebuilds in some unusual situations. For example:

hello.bin: hello.o bye.o
		$(CC) -o $@ $^

%.o: %.c
		$(CC) -c -o $@ $<

.SECONDARY: hello.o bye.o

See: [https://www.gnu.org/software/make/manual/html_node/Special-Targets.html]()
