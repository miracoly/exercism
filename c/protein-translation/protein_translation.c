#include <string.h>
#include "protein_translation.h"

#define INVALID_PROTEIN (proteins_t) { \
    .valid = false,                    \
    .count = 0                         \
  }
#define EMPTY_PROTEIN (proteins_t) { \
    .valid = true,                   \
    .count = 0,                      \
    .proteins = {0}                  \
  }

typedef enum {
    VALID = 0,
    STOP,
    INVALID
} protein_status_bla;

typedef struct {
    protein_status_bla status;
    protein_t protein;
} protein_status;


static protein_status getProtein(const char codon[static 3]) {
    if (!strncmp(codon, "UAA", 3)
        || !strncmp(codon, "UAG", 3)
        || !strncmp(codon, "UGA", 3))
        return (protein_status) {
                .status = STOP
        };
    else if (!strncmp(codon, "AUG", 3))
        return (protein_status) {
                .status = VALID,
                .protein = Methionine
        };
    else if (!strncmp(codon, "UUC", 3) ||
             !strncmp(codon, "UUU", 3))
        return (protein_status) {
                .status = VALID,
                .protein = Phenylalanine
        };
    else if (!strncmp(codon, "UUA", 3) ||
             !strncmp(codon, "UUG", 3))
        return (protein_status) {
                .status = VALID,
                .protein = Leucine
        };
    else if (!strncmp(codon, "UCU", 3)
             || !strncmp(codon, "UCC", 3)
             || !strncmp(codon, "UCA", 3)
             || !strncmp(codon, "UCG", 3)) {
        return (protein_status) {
                .status = VALID,
                .protein = Serine
        };
    } else if (!strncmp(codon, "UAC", 3)
               || !strncmp(codon, "UAU", 3))
        return (protein_status) {
                .status = VALID,
                .protein = Tyrosine
        };
    else if (!strncmp(codon, "UGU", 3)
             || !strncmp(codon, "UGC", 3))
        return (protein_status) {
                .status = VALID,
                .protein = Cysteine
        };
    else if (!strncmp(codon, "UGG", 3))
        return (protein_status) {
                .status = VALID,
                .protein = Tryptophan
        };
    else
        return (protein_status) {
                .status = INVALID,
        };

}

static bool three_chars_left(const char *const rna) {
    return rna[0] != '\0' && rna[1] != '\0' && rna[2] != '\0';
}

proteins_t proteins(const char *const rna) {
    if (rna == NULL) return INVALID_PROTEIN;
    if (rna[0] == '\0') return EMPTY_PROTEIN;

    proteins_t res = {.valid = true};
    size_t i = 0;
    size_t k = 0;
    protein_status status = {0};

    while (three_chars_left(&rna[i]) && i < MAX_PROTEINS) {
        status = getProtein(&rna[i]);
        i += 3;

        if (status.status == INVALID) return INVALID_PROTEIN;
        else if (status.status == STOP) break;
        else {
            res.count++;
            res.proteins[k++] = status.protein;
        }
    }

    if (rna[i] != '\0' && status.status != STOP) return INVALID_PROTEIN;
    return res;
}
