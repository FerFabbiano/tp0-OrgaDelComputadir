#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main () {
	
	const char base64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	char string[3] = "Man";
	uint32_t car0 = string[0];
	uint32_t car1 = string[1];
	uint32_t car2 = string[2];
	uint32_t bits = (car0 << 0x10) + (car1 << 0x08) + car2;
	uint32_t result = (bits >> 18) & 63;
	uint32_t result2 = (bits >> 12) & 63;
	uint32_t result3 = (bits >> 6) & 63;
	uint32_t result4 = (bits) & 63;

	char base64[5];
	base64[0] = base64chars[result];
	base64[1] = base64chars[result2];
	base64[2] = base64chars[result3];
	base64[3] = base64chars[result4];

	printf("%s\n", base64);
	
}