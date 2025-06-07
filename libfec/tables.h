/*
 * Copyright 2025, Tomoya Hagen (tomoya.hagen@spaceteam.at)
 * May be used under the terms of the GNU Lesser General Public License (LGPL)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "fixed.h"

extern unsigned char Taltab[NN + 1];
extern unsigned char Tal1tab[NN + 1];
extern unsigned char CCSDS_alpha_to[NN + 1];
extern unsigned char CCSDS_index_of[NN + 1];
extern unsigned char CCSDS_poly[NROOTS + 1];

#define ALPHA_TO CCSDS_alpha_to
#define INDEX_OF CCSDS_index_of
#define GENPOLY CCSDS_poly

#ifdef __cplusplus
}
#endif
