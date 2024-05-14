#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rna_transcription.h"

static char to_single_rna(char dna) {
    switch (dna) {
        case 'C':
            return 'G';
        case 'G':
            return 'C';
        case 'T':
            return 'A';
        case 'A':
            return 'U';
        default:
            return '\0';
    }
}

char* to_rna(const char* dna) {
    if (!dna) return NULL;
    const size_t len = strlen(dna);
    char* rna = calloc(len + 1, sizeof(char));

    for (size_t i = 0; i < len; ++i) {
        rna[i] = to_single_rna(dna[i]);
    }

    rna[len] = '\0';

    return rna;
}
