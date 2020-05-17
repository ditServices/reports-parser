#include "ca_reports.h"

#include <stdlib.h>
#include <setjmp.h>
#include <stdio.h>
#include <string.h>

#define HEADING_ONE 18
#define DEFAULT_TEXT_SIZE 12

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
  ca_draw_meta_grid(report->pdf ,report->page_1);
  report->font = HPDF_GetFont(report->pdf, "Helvetica", NULL);
  HPDF_Page_SetFontAndSize(report->page_1, report->font, DEFAULT_TEXT_SIZE);
  return report;
}


/* Add production title to report header */
int ca_add_pt(CA_REPORT *report, char *pt) {
  char *token = pt;
  HPDF_Page_SetFontAndSize(report->page_1, report->font, HEADING_ONE);
  float tw = HPDF_Page_TextWidth(report->page_1, token);

  HPDF_Page_BeginText(report->page_1);
  HPDF_Page_TextOut(report->page_1, (HPDF_Page_GetWidth(report->page_1) - tw) / 2, HPDF_Page_GetHeight(report->page_1) - 40, token);
  HPDF_Page_EndText(report->page_1);

  /* Return page size to default */
  HPDF_Page_SetFontAndSize(report->page_1, report->font, DEFAULT_TEXT_SIZE);
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
