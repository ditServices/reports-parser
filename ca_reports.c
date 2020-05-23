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
#define TB_REEL 5
#define TB_SCENE 40
#define TB_SLATE 85
#define TB_TAKE 125
#define TB_LENS 165
#define TB_STOP 205
#define TB_FILTERS 245

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

/* Draw table header */
 int ca_draw_header(CA_REPORT *report) {
   HPDF_Page_BeginText(report->pages[0]);
   HPDF_Page_TextOut(report->pages[0], report->col1 + TB_REEL, report->height - TABLE_HEADER, "REEL");
   HPDF_Page_TextOut(report->pages[0], report->col1 + TB_SCENE, report->height - TABLE_HEADER, "SCENE");
   HPDF_Page_TextOut(report->pages[0], report->col1 + TB_SLATE, report->height - TABLE_HEADER, "SLATE");
   HPDF_Page_TextOut(report->pages[0], report->col1 + TB_TAKE, report->height - TABLE_HEADER, "TAKE");
   HPDF_Page_TextOut(report->pages[0], report->col1 + TB_LENS, report->height - TABLE_HEADER, "LENS");
   HPDF_Page_TextOut(report->pages[0], report->col1 + TB_STOP, report->height - TABLE_HEADER, "STOP");
   HPDF_Page_TextOut(report->pages[0], report->col1 + TB_FILTERS, report->height - TABLE_HEADER, "NOTES");

   HPDF_Page_EndText(report->pages[0]);
   return 0;
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
  report->newpage = 1;
  report->pages = malloc(sizeof(HPDF_Page) * report->newpage);
  report->pages[0] = HPDF_AddPage(report->pdf);

  HPDF_Page_SetSize(report->pages[0], HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
  report->font = HPDF_GetFont(report->pdf, "Helvetica", NULL);
  HPDF_Page_SetFontAndSize(report->pages[0], report->font, DEFAULT_TEXT_SIZE);

  report->width = HPDF_Page_GetWidth(report->pages[0]);
  report->height = HPDF_Page_GetHeight(report->pages[0]);
  report->col1 = report->width / 2;
  report->col1 = report->col1 - report->col1 + 50;
  report->col2 = report->width / 2;
  report->col2 + 100;
  report->table_row = report->height - TABLE_START;
  ca_draw_header(report);
  return report;
}

/* Add production title to report header */
int ca_add_pt(CA_REPORT *report, char *pt) {
  char *token = pt;
  HPDF_Page_SetFontAndSize(report->pages[0], report->font, HEADING_ONE);
  float tw = HPDF_Page_TextWidth(report->pages[0], token);

  HPDF_Page_BeginText(report->pages[0]);
  HPDF_Page_TextOut(report->pages[0], (report->width - tw) / 2, report->height - 40, token);
  HPDF_Page_EndText(report->pages[0]);

  /* Return page size to default */
  HPDF_Page_SetFontAndSize(report->pages[0], report->font, DEFAULT_TEXT_SIZE);
  return 0;
}

/* Add director to report */
int ca_add_dir(CA_REPORT *report, char *_dir) {
  char token[META_LEN] = "Director: ";
  strcat(token, _dir);
  HPDF_Page_SetFontAndSize(report->pages[0], report->font, DEFAULT_TEXT_SIZE);

  HPDF_Page_BeginText(report->pages[0]);
  HPDF_Page_TextOut(report->pages[0], report->col1, report->height - META_TOP, token);
  HPDF_Page_EndText(report->pages[0]);
  return 0;
}

/* Add DOP to report */
int ca_add_dop(CA_REPORT *report, char *dop) {
  char token[META_LEN] = "DOP: ";
  strcat(token, dop);

  HPDF_Page_SetFontAndSize(report->pages[0], report->font, DEFAULT_TEXT_SIZE);


  HPDF_Page_BeginText(report->pages[0]);
  HPDF_Page_TextOut(report->pages[0], report->col1, report->height - META_MIDDLE, token);
  HPDF_Page_EndText(report->pages[0]);
  return 0;
}

/* Add DIT to report */
int ca_add_dit(CA_REPORT *report, char *dit) {
  char token[META_LEN] = "DIT: ";
  strcat(token, dit);

  HPDF_Page_SetFontAndSize(report->pages[0], report->font, DEFAULT_TEXT_SIZE);

  HPDF_Page_BeginText(report->pages[0]);
  HPDF_Page_TextOut(report->pages[0], report->col1, report->height - META_BOTTOM, token);
  HPDF_Page_EndText(report->pages[0]);
  return 0;
}

/* Add camera to report */
int ca_add_cam(CA_REPORT *report, char *cam) {
  char token[META_LEN] = "Camera: ";
  strcat(token, cam);

  HPDF_Page_SetFontAndSize(report->pages[0], report->font, DEFAULT_TEXT_SIZE);

  HPDF_Page_BeginText(report->pages[0]);
  HPDF_Page_TextOut(report->pages[0], report->col2, report->height - META_TOP, token);
  HPDF_Page_EndText(report->pages[0]);
  return 0;
}

/* Add camera format to report */
int ca_add_frmt(CA_REPORT *report, char *frmt) {
  char token[META_LEN] = "Format: ";
  strcat(token, frmt);

  HPDF_Page_SetFontAndSize(report->pages[0], report->font, DEFAULT_TEXT_SIZE);

  HPDF_Page_BeginText(report->pages[0]);
  HPDF_Page_TextOut(report->pages[0], report->col2, report->height - META_MIDDLE, token);
  HPDF_Page_EndText(report->pages[0]);

  return 0;
}

/* Add codec to report */
int ca_add_codec(CA_REPORT *report, char *codec) {

  char token[META_LEN] = "Codec: ";
  strcat(token, codec);

  HPDF_Page_SetFontAndSize(report->pages[0], report->font, DEFAULT_TEXT_SIZE);

  HPDF_Page_BeginText(report->pages[0]);
  HPDF_Page_TextOut(report->pages[0], report->col2, report->height - META_BOTTOM, token);
  HPDF_Page_EndText(report->pages[0]);

  return 0;
}

/* Add date to report */
int ca_add_date(CA_REPORT *report, char *date) {
  HPDF_Page_SetFontAndSize(report->pages[0], report->font, HEADING_TWO);
  HPDF_Page_BeginText(report->pages[0]);
  HPDF_Page_TextOut(report->pages[0], report->col1, report->height - 40, date);
  HPDF_Page_EndText(report->pages[0]);
  HPDF_Page_SetFontAndSize(report->pages[0], report->font, DEFAULT_TEXT_SIZE);
  return 0;
}

/* Table row add function - Need to accomodate for spanning several pages */
int ca_add_tablerow(CA_REPORT *report, char *take,
                    char *lens, char *stop, char *filt ) {
  int page = report->newpage;
  page = page - 1;
  HPDF_Page_SetFontAndSize(report->pages[page], report->font, DEFAULT_TEXT_SIZE);

  HPDF_Page_BeginText(report->pages[page]);
  HPDF_Page_TextOut(report->pages[page], report->col1 + TB_TAKE, report->table_row, take);
  HPDF_Page_TextOut(report->pages[page], report->col1 + TB_LENS, report->table_row, lens);
  HPDF_Page_TextOut(report->pages[page], report->col1 + TB_STOP, report->table_row, stop);
  HPDF_Page_TextOut(report->pages[page], report->col1 + TB_FILTERS, report->table_row, filt);

  HPDF_Page_EndText(report->pages[page]);

  report->table_row = report->table_row - 20;
  return 0;
}

/* Add reel data to page
 * These functions need to check the page that they are writing to */
int ca_add_reel(CA_REPORT *report, char *reel) {
  HPDF_Page_SetFontAndSize(report->pages[0], report->font, DEFAULT_TEXT_SIZE);
  HPDF_Page_BeginText(report->pages[0]);

  HPDF_Page_TextOut(report->pages[0], report->col1 + TB_REEL, report->table_row, reel);

  HPDF_Page_EndText(report->pages[0]);
  return 0;
}

/* Add scene data to page */
int ca_add_scene(CA_REPORT *report, char *scene) {
  HPDF_Page_SetFontAndSize(report->pages[0], report->font, DEFAULT_TEXT_SIZE);
  HPDF_Page_BeginText(report->pages[0]);

  HPDF_Page_TextOut(report->pages[0], report->col1 + TB_SCENE, report->table_row, scene);

  HPDF_Page_EndText(report->pages[0]);
  return 0;
}


/* Add slate data to page */
int ca_add_slate(CA_REPORT *report, char *slate) {
  HPDF_Page_SetFontAndSize(report->pages[0], report->font, DEFAULT_TEXT_SIZE);
  HPDF_Page_BeginText(report->pages[0]);

  HPDF_Page_TextOut(report->pages[0], report->col1 + TB_SLATE, report->table_row, slate);

  HPDF_Page_EndText(report->pages[0]);
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
    free(report->pages[0]);
    free(report);
}
