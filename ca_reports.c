#include "ca_reports.h"

#include <stdlib.h>
#include <setjmp.h>
#include <stdio.h>
#include <string.h>

#define META_LEN 250
#define META_TOP 90
#define META_MIDDLE 120
#define META_BOTTOM 150

#define HEADING_ONE 20
#define HEADING_TWO 13
#define DEFAULT_TEXT_SIZE 10

#define TABLE_HEADER 200
#define TABLE_START 230
#define TB_TAKE 120
#define TB_LENS 160
#define TB_STOP 200
#define TB_FILTERS 240

/* HPDF Error methods */
jmp_buf env;

#ifdef HPDF_DLL
void  __stdcall
#else
void
#endif

error_handler (HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data)
{
    printf ("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
            (HPDF_UINT)detail_no);
    longjmp(env, 1);
}

/* init report with defualt values and grid.
 *  TODO: grid_methods */
CA_REPORT* new_report() {
  CA_REPORT *report = malloc(sizeof(CA_REPORT));
  report->pdf = HPDF_New(error_handler, NULL);

  if(setjmp(env)) {
    HPDF_Free(report->pdf);
    return NULL;
  }

  report->page_1 = HPDF_AddPage(report->pdf);
  report->newpage = 1;

  HPDF_Page_SetSize(report->page_1, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

  //ca_draw_meta_grid(report->pdf ,report->page_1);
  report->font = HPDF_GetFont(report->pdf, "Helvetica", NULL);
  HPDF_Page_SetFontAndSize(report->page_1, report->font, DEFAULT_TEXT_SIZE);

  report->width = HPDF_Page_GetWidth(report->page_1);
  report->height = HPDF_Page_GetHeight(report->page_1);
  report->col1 = report->width / 2;
  report->col1 = report->col1 - report->col1 + 50;
  report->col2 = report->width / 2;
  report->col2 + 100;
  report->table_row = report->height - TABLE_START;
  return report;
}


/* Add production title to report header */
int ca_add_pt(CA_REPORT *report, char *pt) {
  char *token = pt;
  HPDF_Page_SetFontAndSize(report->page_1, report->font, HEADING_ONE);
  float tw = HPDF_Page_TextWidth(report->page_1, token);

  HPDF_Page_BeginText(report->page_1);
  HPDF_Page_TextOut(report->page_1, (report->width - tw) / 2, report->height - 40, token);
  HPDF_Page_EndText(report->page_1);

  /* Return page size to default */
  HPDF_Page_SetFontAndSize(report->page_1, report->font, DEFAULT_TEXT_SIZE);
  return 0;
}

/* Add director to report */
int ca_add_dir(CA_REPORT *report, char *_dir) {
  char token[META_LEN] = "Director: ";
  strcat(token, _dir);
  HPDF_Page_SetFontAndSize(report->page_1, report->font, DEFAULT_TEXT_SIZE);

  HPDF_Page_BeginText(report->page_1);
  HPDF_Page_TextOut(report->page_1, report->col1, report->height - META_TOP, token);
  HPDF_Page_EndText(report->page_1);
  return 0;
}

/* Add DOP to report */
int ca_add_dop(CA_REPORT *report, char *dop) {
  char token[META_LEN] = "DOP: ";
  strcat(token, dop);

  HPDF_Page_SetFontAndSize(report->page_1, report->font, DEFAULT_TEXT_SIZE);


  HPDF_Page_BeginText(report->page_1);
  HPDF_Page_TextOut(report->page_1, report->col1, report->height - META_MIDDLE, token);
  HPDF_Page_EndText(report->page_1);
  return 0;
}

/* Add DIT to report */
int ca_add_dit(CA_REPORT *report, char *dit) {
  char token[META_LEN] = "DIT: ";
  strcat(token, dit);

  HPDF_Page_SetFontAndSize(report->page_1, report->font, DEFAULT_TEXT_SIZE);

  HPDF_Page_BeginText(report->page_1);
  HPDF_Page_TextOut(report->page_1, report->col1, report->height - META_BOTTOM, token);
  HPDF_Page_EndText(report->page_1);
  return 0;
}

/* Add camera to report */
int ca_add_cam(CA_REPORT *report, char *cam) {
  char token[META_LEN] = "Camera: ";
  strcat(token, cam);

  HPDF_Page_SetFontAndSize(report->page_1, report->font, DEFAULT_TEXT_SIZE);

  HPDF_Page_BeginText(report->page_1);
  HPDF_Page_TextOut(report->page_1, report->col2, report->height - META_TOP, token);
  HPDF_Page_EndText(report->page_1);
  return 0;
}

/* Add camera format to report */
int ca_add_frmt(CA_REPORT *report, char *frmt) {
  char token[META_LEN] = "Format: ";
  strcat(token, frmt);

  HPDF_Page_SetFontAndSize(report->page_1, report->font, DEFAULT_TEXT_SIZE);

  HPDF_Page_BeginText(report->page_1);
  HPDF_Page_TextOut(report->page_1, report->col2, report->height - META_MIDDLE, token);
  HPDF_Page_EndText(report->page_1);

  return 0;
}

/* Add codec to report */
int ca_add_codec(CA_REPORT *report, char *codec) {

  char token[META_LEN] = "Codec: ";
  strcat(token, codec);

  HPDF_Page_SetFontAndSize(report->page_1, report->font, DEFAULT_TEXT_SIZE);

  HPDF_Page_BeginText(report->page_1);
  HPDF_Page_TextOut(report->page_1, report->col2, report->height - META_BOTTOM, token);
  HPDF_Page_EndText(report->page_1);

  return 0;
}

/* Add date to report */
int ca_add_date(CA_REPORT *report, char *date) {
  HPDF_Page_SetFontAndSize(report->page_1, report->font, HEADING_TWO);
  HPDF_Page_BeginText(report->page_1);
  HPDF_Page_TextOut(report->page_1, report->col1, report->height - 40, date);
  HPDF_Page_EndText(report->page_1);
  HPDF_Page_SetFontAndSize(report->page_1, report->font, DEFAULT_TEXT_SIZE);
  return 0;
}

/* table row add func, not sure if this is correct as need to fig out a way
 * to add reel and scene info too, also need to acoomodate for spanning multi pages */

int ca_add_tablerow(CA_REPORT *report, char *take,
                    char *lens, char *stop, char *filt ) {
  HPDF_Page_SetFontAndSize(report->page_1, report->font, DEFAULT_TEXT_SIZE);

  HPDF_Page_BeginText(report->page_1);
  HPDF_Page_TextOut(report->page_1, report->col1 + TB_TAKE, report->table_row, take);
  HPDF_Page_TextOut(report->page_1, report->col1 + TB_LENS, report->table_row, lens);
  HPDF_Page_TextOut(report->page_1, report->col1 + TB_STOP, report->table_row, stop);
  HPDF_Page_TextOut(report->page_1, report->col1 + TB_FILTERS, report->table_row, filt);

  HPDF_Page_EndText(report->page_1);

  report->table_row = report->table_row - 20;
  return 0;
}



/* Write report out to file */
int ca_save_report(CA_REPORT *report) {
  printf("Saving report\n");
  HPDF_SaveToFile(report->pdf, "report.pdf");
  HPDF_Free(report->pdf);
  return 0;
}

/* Ensure that memory is freed */
void ca_free(CA_REPORT *report) {
    printf("Freeing memory\n");
    free(report);
}
