#include "ca_reports.h"

#include <stdlib.h>
#include <stdio.h>

CA_REPORT* new_report() {
  CA_REPORT *report = malloc(sizeof(CA_REPORT));
  report->newpage = 1;

  return report;
}

void ca_free(CA_REPORT *report) {
    printf("freeing mem\n");
    free(report);
}
