/*
 * Copyright 2002, Phil Karn, KA9Q
 * Copyright 2025, Tomoya Hagen (tomoya.hagen@spaceteam.at)
 * May be used under the terms of the GNU Lesser General Public License (LGPL)
 */

/* Reed-Solomon encoder
 * Copyright 2004, Phil Karn, KA9Q
 * May be used under the terms of the GNU Lesser General Public License (LGPL)
 */
#include <string.h>
#include "fixed.h"
#include "tables.h"

#undef A0
#define A0 (NN)

void encode_rs_8(data_t *data, data_t *parity);

/* Portable C version */
void encode_rs_8(data_t *data, data_t *parity)
{
  int i, j;
  data_t feedback;

  memset(parity, 0, NROOTS * sizeof(data_t));

  for (i = 0; i < NN - NROOTS; i++)
  {
    feedback = INDEX_OF[data[i] ^ parity[0]];
    if (feedback != A0)
    { /* feedback term is non-zero */
      for (j = 1; j < NROOTS; j++)
      {
        parity[j] ^= ALPHA_TO[MODNN(feedback + GENPOLY[NROOTS - j])];
      }
    }
    /* Shift */
    memmove(&parity[0], &parity[1], sizeof(data_t) * (NROOTS - 1));
    if (feedback != A0)
      parity[NROOTS - 1] = ALPHA_TO[MODNN(feedback + GENPOLY[0])];
    else
      parity[NROOTS - 1] = 0;
  }
}
