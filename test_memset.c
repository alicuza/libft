#include <criterion/criterion.h>
#include <criterion/new/assert.h>  // New assertion API
#include <string.h>           // For memset
#include <stdlib.h>           // For malloc/free

Test(memset_suite, basic_zero_fill) {
	const size_t buffer_size = 10;
	unsigned char *buffer = malloc(buffer_size);
	cr_expect_not_null(buffer, "Failed to allocate buffer");

	// Initialize buffer with a known non-zero pattern (0xAA)
	for (size_t i = 0; i < buffer_size; ++i) {
		buffer[i] = 0xAA;
	}

	// Call memset to set first 5 bytes to 0x00
	memset(buffer, 0x00, 5);

	// Expected buffer: [0x00, 0x00, 0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA]
	unsigned char expected[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};

	struct cr_mem buffer_mem = { .data = buffer, .size = buffer_size };
	struct cr_mem expected_mem = { .data = expected, .size = buffer_size };

	// Assert buffers are equal using new API
	cr_expect(eq(mem, buffer_mem, expected_mem, buffer_size), "Expected buffer to match after memset");

	free(buffer);  // Clean up
}

