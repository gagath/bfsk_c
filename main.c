#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define SAMPLING 8000

#define FREQ_TRUE 4000
#define FREQ_FALSE (FREQ_TRUE / 2)

void sine(FILE *f, float freq, float sampling)
{
	int i;
	int samples;
	int8_t val;
	float theta;

	samples = sampling / freq;

	for (i = 0; i < samples; i++) {
		theta = ((float) i / samples) * 2 * M_PI;
		val = sin(theta) * 127;
		fwrite(&val, 1, sizeof(int8_t), f);
	}
}

void write_byte(FILE *f, uint8_t byte)
{
	int i;
	int val;

	for (i = 0; i < 8; i++) {
		val = byte & (1 << i);

		if (val) {
			sine(f, FREQ_TRUE, SAMPLING);
			sine(f, FREQ_TRUE, SAMPLING);
		} else {
			sine(f, FREQ_FALSE, SAMPLING);
		}
	}
}

int main(void)
{
	int c;
	int i;

	fprintf(stderr, "Data speed : %d bauds\n", FREQ_FALSE);

	/* Header */
	for (i = 0; i < 100; i++) {
		write_byte(stdout, 1);
	}

	/* Body */
	while ((c = fgetc(stdin)) != EOF) {
		write_byte(stdout, c);
	}

	/* End of transmission */
	for (i = 0; i < 10; i++) {
		write_byte(stdout, 1);
	}

	return 0;
}

