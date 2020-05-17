#ifndef CAMERA_REPORTS_H
#define CAMERA_REPORTS_H

#include "hpdf.h"

typedef struct CA_REPORT {
  int newpage;
  HPDF_Doc pdf;
  HPDF_Font font;
  HPDF_Page page_1;
} CA_REPORT;

CA_REPORT* new_report();

/* Add metadata to report header */
int ca_add_pt(CA_REPORT *report, char *pt);
int ca_add_dir(char *_dir);
int ca_add_dop(char *dop);
int ca_add_dit(char *dit);
int ca_add_frmt(char *frmt);
int ca_add_cam(char *cam);
int ca_add_codec(char *codec);
int ca_add_data(char *date);

/* add table data */
int ca_add_tablerow(char *reel, char *scene, char *slate, char *take,
                    char *lens, char *stop, char *filt );

/* grid drawing methods for metadata table
 * and additional pages */
int ca_draw_meta_grid();
int ca_draw_table_grid();
int ca_draw_con_grit();

/* save report */
int ca_save_report(CA_REPORT *report);
void ca_free(CA_REPORT *report);

#endif
