#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_N 10000
#define MAX_M 1000000
#define MAX_OUTPUT_SIZE (8 * MAX_M) // 8 MB

uint8_t code_len[MAX_N];      // Length of the code for each symbol
uint64_t code_bits[MAX_N];    // Bits of the code for each symbol

uint16_t text[MAX_M];         // The text symbols
unsigned char output_buffer[MAX_OUTPUT_SIZE / 8]; // Output bit array

// Function to read a 4-byte little-endian unsigned integer
uint32_t read_uint32_le(FILE *f) {
    unsigned char buffer[4];
    fread(buffer, 1, 4, f);
    uint32_t value = ((uint32_t)buffer[0]) |
                     ((uint32_t)buffer[1] << 8) |
                     ((uint32_t)buffer[2] << 16) |
                     ((uint32_t)buffer[3] << 24);
    return value;
}

// Function to read a 2-byte little-endian unsigned integer
uint16_t read_uint16_le(FILE *f) {
    unsigned char buffer[2];
    fread(buffer, 1, 2, f);
    uint16_t value = ((uint16_t)buffer[0]) |
                     ((uint16_t)buffer[1] << 8);
    return value;
}

int main() {
    FILE *fin = fopen("input.txt", "rb");
    FILE *fout = fopen("output.txt", "wb");
    // Read N
    uint32_t N = read_uint32_le(fin);
    // Read codes for each symbol
    for (uint32_t i = 0; i < N; i++) {
        uint32_t L = read_uint32_le(fin);
        code_len[i] = (uint8_t)L;
        code_bits[i] = 0;

        for (uint32_t j = 0; j < L; j++) {
            unsigned char b;
            fread(&b, 1, 1, fin);
            code_bits[i] |= ((uint64_t)b) << j;
        }
    }

    // Read M
    uint32_t M = read_uint32_le(fin);

    // Read M symbols
    for (uint32_t i = 0; i < M; i++) {
        uint16_t s = read_uint16_le(fin);
        text[i] = s;
    }

    fclose(fin); // We have read all the input

    // Prepare the output buffer
    uint64_t output_bit_pos = 0;
    for (uint32_t i = 0; i < M; i++) {
        uint8_t code_length = code_len[text[i]];
        uint64_t code = code_bits[text[i]];
        uint8_t bits_written = 0;

        while (bits_written < code_length) {
            uint64_t byte_pos = output_bit_pos / 8;
            uint8_t bit_offset = output_bit_pos % 8;
            uint8_t bits_in_current_byte = (uint8_t)(8 - bit_offset);
            if (bits_in_current_byte > (code_length - bits_written)) {
                bits_in_current_byte = code_length - bits_written;
            }

            uint8_t bits_to_write = (uint8_t)((code >> bits_written) & ((1ULL << bits_in_current_byte) - 1));
            bits_to_write <<= bit_offset;
            output_buffer[byte_pos] |= bits_to_write;

            bits_written += bits_in_current_byte;
            output_bit_pos += bits_in_current_byte;
        }
    }

    // Pad with zeros to make total bits a multiple of 8
    uint64_t total_bits = output_bit_pos;
    uint64_t total_bytes = (total_bits + 7) / 8;

    // Write the output buffer to output.txt
    fwrite(output_buffer, 1, total_bytes, fout);

    fclose(fout);

    return 0;
}
