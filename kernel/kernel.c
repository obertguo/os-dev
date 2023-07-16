void main() {
	const char GREEN_ON_BLACK = 0xa0;
	const char RED_ON_WHITE = 0x4f;

	char *VIDEO_MEMORY = (char *) 0xb80f0;

	for (int i = 0; i < 26; ++i) {
		*VIDEO_MEMORY = 'a' + i;
		*(VIDEO_MEMORY + 1) = GREEN_ON_BLACK;

		VIDEO_MEMORY += 2;
	}

	for (int i = 0; i < 26; ++i) {
		*VIDEO_MEMORY = 'A' + i;
		*(VIDEO_MEMORY + 1) = RED_ON_WHITE;

		VIDEO_MEMORY += 2;
	}
}