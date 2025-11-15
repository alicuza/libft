# FLOW

- f get-next-line:
	returns the next line of the given fd or NULL if it fails or reached the end of file.
	it has to remember where in the file it is to print the next line.
	it uses a fixed buffer size, meaning, there are 2 cases to consider:
		a) the buffer contains a new line char
		b) the buffer doesn't contain a new line char
	1. we get the buffer: f get-buffer-fd and check for failure
	2. we get the next line: f get-next
	3. return next-line

- f get-buffer-fd:
	searches the buffer list pointed to by the given head for the buffer
	corresponding to the given fd. if no buffer corresponds, it creates
	a new buffer and links it to the list.
	returns the pointer to the buffer or NULL when it fails to create
	the new buffer.
	1. check whether we trigger the function for the first time.
		(whether head points to NULL, because of static initialisations)
		a. if so, we create a node and assign it to the head.
			we check for failure and return.
		b. otherwise we continue
	2. while the buffer exists, we check whether it is the correct buffer
		- it is the correct buffer by default, if it is the first time we call the function.
		- we iterate over the buffer list and check whether the given fd matches
		  the one stored in the buffer.
		a. if it matches, we return the found buffer
		b. otherwise we iterate to the end of the loop and continue
	3. creates a node and links it to the buffer list.

- f get-next:
	searches for the next new line in the document and copies everything
	up to that point to the next line that will be returned.
	1. while there is no newline char in the buffer:
		- check the length of the buffer to see if it is empty:
			a. if the buffer is empty, read a new chunk into it and check for failure.
				- check length of buffer again:
					a. if it is -1, the read failed: we free and return NULL
					b. if it is 0, the read reached the EOF:
						we free the current buffer and return the next_line_buffer
			b. otherwise we continue
		- add it to the next line buffer. using a modified strjoin that joins 2 strings,
			while the first has to be a traditional null terminated string, the second
			can be a new line terminated string of chars: f strjoin-mod
	2. if there is a newline char, use strjoin-mod to copy it over, check for failure.
