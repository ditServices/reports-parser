/*
 * This file is part of the Reports Parser Project (https://github.com/ditServices/reports-parser).
 * Copyright (c) 2020 Howard Colin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#include "ca_reports.h"

/* Margins */
enum {
  GRID_LEFT_M = 5,
  GRID_RIGHT_M = 5,
  GRID_TOP_M = 5,
  GRID_BTM_M = 5,
  MG_TITLE_TOP = 15,
  MG_TITLE_BOTTOM = 50
};

/* Draw layout grid that contains production title metadata */
int ca_draw_meta_grid(HPDF_Doc pdf, HPDF_Page page) {

  HPDF_REAL height = HPDF_Page_GetHeight(page);
  HPDF_REAL width = HPDF_Page_GetWidth(page);
  HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", NULL);
  HPDF_UINT x, y;

  HPDF_Page_SetFontAndSize(page, font, 5);
  HPDF_Page_SetLineWidth(page, 0.8);

  /* Title box */
  y = height - MG_TITLE_TOP;
  for(int x_lines = 0; x_lines < 2; x_lines++) {
    HPDF_Page_MoveTo(page, GRID_LEFT_M, y);
    HPDF_Page_LineTo(page, width - GRID_RIGHT_M, y);
    HPDF_Page_Stroke(page);
    y = height - MG_TITLE_BOTTOM;
  }

  x = width - GRID_LEFT_M;

  HPDF_Page_MoveTo(page, x, height - MG_TITLE_TOP);
  HPDF_Page_LineTo(page, x, height - MG_TITLE_BOTTOM);
  HPDF_Page_Stroke(page);

  return 0;
}

/* Draw table grid for shot data */
int ca_draw_table_grid() {
  return 0;
}

/* Grid to be added to new pages */
int ca_draw_con_grid() {
  return 0;
}
