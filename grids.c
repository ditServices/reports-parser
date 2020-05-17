#include "ca_reports.h"

/* Margins */
enum {
  GRID_LEFT_M = 5,
  GRID_RIGHT_M = 5
};

/* Draw layout grid that contains production title metadata */
int ca_draw_meta_grid(HPDF_Doc pdf, HPDF_Page page) {

  HPDF_REAL height = HPDF_Page_GetHeight(page);
  HPDF_REAL width = HPDF_Page_GetWidth(page);
  HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", NULL);
  HPDF_UINT x, y;

  HPDF_Page_SetFontAndSize(page, font, 5);
  HPDF_Page_SetGrayFill(page, 0.5);
  HPDF_Page_SetGrayStroke(page, 0.8);

  y = height - 10;
  HPDF_Page_SetLineWidth(page, 0.8);
  HPDF_Page_MoveTo(page, GRID_LEFT_M, y);
  HPDF_Page_LineTo(page, width - GRID_RIGHT_M, y);
  HPDF_Page_Stroke(page);

  HPDF_Page_SetGrayFill(page, 0);
  HPDF_Page_SetGrayStroke(page, 0);
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
