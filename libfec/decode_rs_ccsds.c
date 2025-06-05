/*
 * Copyright 2002, Phil Karn, KA9Q
 * Copyright 2025, Tomoya Hagen (tomoya.hagen@spaceteam.at)
 * May be used under the terms of the GNU Lesser General Public License (LGPL)
 */

/* This function wraps around the fixed 8-bit decoder, performing the
 * basis transformations necessary to meet the CCSDS standard
 *
 * Copyright 2002, Phil Karn, KA9Q
 * May be used under the terms of the GNU Lesser General Public License (LGPL)
 */
#include "fec.h"
#include "fixed.h"
#include "tables.h"

int decode_rs_ccsds(data_t *data)
{
  int i, r;
  data_t cdata[NN];

  /* Convert data from dual basis to conventional */
  for (i = 0; i < NN; i++)
    cdata[i] = Tal1tab[data[i]];

  r = decode_rs_8(cdata, (void *)0, 0, 0);

  if (r > 0)
  {
    /* Convert from conventional to dual basis */
    for (i = 0; i < NN; i++)
      data[i] = Taltab[cdata[i]];
  }
  return r;
}
