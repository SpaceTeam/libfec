#include "fixed.h"

extern unsigned char Taltab[NN + 1];
extern unsigned char Tal1tab[NN + 1];
extern unsigned char CCSDS_alpha_to[NN + 1];
extern unsigned char CCSDS_index_of[NN + 1];
extern unsigned char CCSDS_poly[NROOTS + 1];

#define ALPHA_TO CCSDS_alpha_to
#define INDEX_OF CCSDS_index_of
#define GENPOLY CCSDS_poly