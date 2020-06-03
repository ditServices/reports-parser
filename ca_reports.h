#ifndef CAMERA_REPORTS_H
#define CAMERA_REPORTS_H

#include "hpdf.h"

typedef struct CA_REPORT {
  /*page count*/
  int newpage;
  int total_reels;
  /* Save data we need for other pages */
  char *report_date;
  char *camera_index;
  char *camera_assist;
  /* report creation objects */
  HPDF_Doc pdf;
  HPDF_Font font;
  HPDF_Page *pages;
  HPDF_REAL width;
  HPDF_REAL height;
  HPDF_UINT col1, col2;
  HPDF_UINT table_row;
} CA_REPORT;

CA_REPORT* new_report();

/* Add metadata to report header */
int ca_add_pt(CA_REPORT *report, char *pt);
int ca_add_dir(CA_REPORT *report, char *_dir);
int ca_add_dop(CA_REPORT *report, char *dop);
int ca_add_dit(CA_REPORT *report, char *dit);
int ca_add_frmt(CA_REPORT *report, char *frmt);
int ca_add_cam(CA_REPORT *report, char *cam);
int ca_add_codec(CA_REPORT *report, char *codec);
int ca_add_date(CA_REPORT *report, char *date);
int ca_add_assistant(CA_REPORT *report, char *cam_assistant);
int ca_add_cindex(CA_REPORT *report, char *index);
int ca_add_loc(CA_REPORT *report, char *loc);
int ca_add_pcomp(CA_REPORT *report, char *pcomp);
int ca_add_cspace(CA_REPORT *report, char *cspace);
int ca_add_fps(CA_REPORT *report, char *fps);

/* Implementation Needed */
int ca_add_sangle(CA_REPORT *report, char *sangle);
int ca_add_flines(CA_REPORT *report, char *flines);

int ca_add_reel(CA_REPORT *report, char *reel);
int ca_add_scene(CA_REPORT *report, char *scene);
int ca_add_slate(CA_REPORT *report, char *slate);

/* add table data */
int ca_add_tablerow(CA_REPORT *report, char *take,
                    char *lens, char *stop, char *filt);
int ca_total_reels(CA_REPORT *report);
int ca_add_assistant(CA_REPORT *report, char *data);

/* grid drawing methods for metadata table
 * and additional pages */
int ca_draw_meta_grid(HPDF_Doc pdf, HPDF_Page page);
int ca_draw_table_grid();
int ca_draw_con_grid();

/* save report */
int ca_save_report(CA_REPORT *report);
void ca_free(CA_REPORT *report);

#endif
