/*
 * Copyright 2002, Phil Karn, KA9Q
 * Copyright 2025, Tomoya Hagen (tomoya.hagen@spaceteam.at)
 * May be used under the terms of the GNU Lesser General Public License (LGPL)
 */

/* This function wraps around the fixed 8-bit encoder, performing the
 * basis transformations necessary to meet the CCSDS standard
 *
 * Copyright 2002, Phil Karn, KA9Q
 * May be used under the terms of the GNU Lesser General Public License (LGPL)
 */
#include "fec.h"
#include "fixed.h"
#include "tables.h"

void encode_rs_ccsds(data_t *data, data_t *parity)
{
  int i;
  data_t cdata[NN - NROOTS];

  /* Convert data from dual basis to conventional */
  for (i = 0; i < NN - NROOTS; i++)
    cdata[i] = Tal1tab[data[i]];

  encode_rs_8(cdata, parity);

  /* Convert parity from conventional to dual basis */
  for (i = 0; i < NN; i++) {
    if (i < NN - NROOTS) {
      data[i] = Taltab[cdata[i]];
    } else {
      parity[i - NN + NROOTS] = Taltab[parity[i - NN + NROOTS]];
    }
  }
}
