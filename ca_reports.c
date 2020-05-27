#include "ca_reports.h"

#include <stdlib.h>
#include <setjmp.h>
#include <stdio.h>
#include <string.h>

#define META_LEN 250
#define META_TOP 90
#define META_MIDDLE 120
#define META_BOTTOM 150

#define INDEX_YPOS 40
#define INDEX_XPOS 200

#define INDEX_SIZE  40
#define HEADING_ONE 20
#define HEADING_TWO 13
#define DEFAULT_TEXT_SIZE 10

#define TABLE_HEADER 200
#define CTABLE_HEADER 70
#define TABLE_START 230
#define TB_REEL 5
#define TB_SCENE 40
#define TB_SLATE 85
#define TB_TAKE 125
#define TB_LENS 165
#define TB_STOP 205
#define TB_FILTERS 245

#define P_NUM_YPOS 800

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
 int ca_draw_header(CA_REPORT *report, int YPOS) {
   int page = report->newpage;
   page = page - 1;
   HPDF_Page_BeginText(report->pages[page]);
   HPDF_Page_TextOut(report->pages[page], report->col1 + TB_REEL, report->height - YPOS, "REEL");
   HPDF_Page_TextOut(report->pages[page], report->col1 + TB_SCENE, report->height - YPOS, "SCENE");
   HPDF_Page_TextOut(report->pages[page], report->col1 + TB_SLATE, report->height - YPOS, "SLATE");
   HPDF_Page_TextOut(report->pages[page], report->col1 + TB_TAKE, report->height - YPOS, "TAKE");
   HPDF_Page_TextOut(report->pages[page], report->col1 + TB_LENS, report->height - YPOS, "LENS");
   HPDF_Page_TextOut(report->pages[page], report->col1 + TB_STOP, report->height - YPOS, "STOP");
   HPDF_Page_TextOut(report->pages[page], report->col1 + TB_FILTERS, report->height - YPOS, "NOTES");

   HPDF_Page_EndText(report->pages[page]);
   return 0;
 }

int ca_add_cindex(CA_REPORT *report, char* cam_index) {
  int page = report->newpage - 1;
  HPDF_Page_SetFontAndSize(report->pages[page], report->font, INDEX_SIZE);
  HPDF_Page_BeginText(report->pages[page]);
  HPDF_Page_TextOut(report->pages[page], report->col2 + INDEX_XPOS, report->height - INDEX_YPOS, cam_index);
  HPDF_Page_EndText(report->pages[page]);
  HPDF_Page_SetFontAndSize(report->pages[page], report->font, DEFAULT_TEXT_SIZE);
  return 0;
}

int ca_add_pnum(CA_REPORT *report) {
  int page = report->newpage - 1;
  char page_num[3];
  sprintf(page_num, "%d", report->newpage);
  HPDF_Page_SetFontAndSize(report->pages[page], report->font, DEFAULT_TEXT_SIZE);
  HPDF_Page_BeginText(report->pages[page]);
  HPDF_Page_TextOut(report->pages[page], report->col1, report->height - P_NUM_YPOS, page_num);
  HPDF_Page_EndText(report->pages[page]);
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
  report->pages = malloc(sizeof(HPDF_Page*) * report->newpage);
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
  ca_draw_header(report, TABLE_HEADER);
  ca_add_pnum(report);
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
  int page = report->newpage - 1;
  HPDF_Page_SetFontAndSize(report->pages[page], report->font, HEADING_TWO);
  HPDF_Page_BeginText(report->pages[page]);
  HPDF_Page_TextOut(report->pages[page], report->col1, report->height - 40, date);
  HPDF_Page_EndText(report->pages[page]);
  HPDF_Page_SetFontAndSize(report->pages[page], report->font, DEFAULT_TEXT_SIZE);
  return 0;
}

int ca_add_page(CA_REPORT *report) {
  report->newpage++;
  report->pages = realloc(report->pages, sizeof(HPDF_Page*) * report->newpage);
  if(report->pages) {
    report->pages[report->newpage-1] = malloc(sizeof(HPDF_Page));
    report->pages[report->newpage-1] = HPDF_AddPage(report->pdf);
    HPDF_Page_SetSize(report->pages[report->newpage-1], HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
    HPDF_Page_SetFontAndSize(report->pages[report->newpage-1], report->font, DEFAULT_TEXT_SIZE);
    ca_draw_header(report, CTABLE_HEADER);
    ca_add_date(report, report->report_date);
    ca_add_cindex(report, report->camera_index);
    ca_add_pnum(report);
  }
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

    if(report->table_row < 150) {
      ca_add_page(report);
      report->table_row = report->height - 100;
    }


  return 0;
}

/* Add reel data to page
 * These functions need to check the page that they are writing to */
int ca_add_reel(CA_REPORT *report, char *reel) {
  int page = report->newpage;
  page = page - 1;
  HPDF_Page_SetFontAndSize(report->pages[page], report->font, DEFAULT_TEXT_SIZE);
  HPDF_Page_BeginText(report->pages[page]);

  HPDF_Page_TextOut(report->pages[page], report->col1 + TB_REEL, report->table_row, reel);

  HPDF_Page_EndText(report->pages[page]);
  return 0;
}

/* Add scene data to page */
int ca_add_scene(CA_REPORT *report, char *scene) {
  int page = report->newpage;
  page = page - 1;
  HPDF_Page_SetFontAndSize(report->pages[page], report->font, DEFAULT_TEXT_SIZE);
  HPDF_Page_BeginText(report->pages[page]);

  HPDF_Page_TextOut(report->pages[page], report->col1 + TB_SCENE, report->table_row, scene);

  HPDF_Page_EndText(report->pages[page]);
  return 0;
}


/* Add slate data to page */
int ca_add_slate(CA_REPORT *report, char *slate) {
  int page = report->newpage;
  page = page - 1;
  HPDF_Page_SetFontAndSize(report->pages[page], report->font, DEFAULT_TEXT_SIZE);
  HPDF_Page_BeginText(report->pages[page]);

  HPDF_Page_TextOut(report->pages[page], report->col1 + TB_SLATE, report->table_row, slate);

  HPDF_Page_EndText(report->pages[page]);
  return 0;
}

/* Write report out to file */
int ca_save_report(CA_REPORT *report) {
  printf("Saving report\n");
  HPDF_SaveToFile(report->pdf, "report.pdf");
  HPDF_Free(report->pdf);
  return 0;
}

/* Ensure that memory is freed needs to iterate over each dynamically allocated page */
void ca_free(CA_REPORT *report) {
    printf("Freeing memory\n");

    for(int i=0; i < report->newpage; i++) {
        free(report->pages[i]);
    }

    free(report->pages);

    if(report->report_date && report->camera_index) {
      free(report->report_date);
      free(report->camera_index);
    }

    free(report);
}
