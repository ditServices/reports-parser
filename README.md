### Camera Reports Parser

This project defines a simple markup language for camera assistants that can be parsed into a PDF report. This application defines the grammar and includes the code to generate the PDF report.

Currently in active development, not all fetures are active.

### Deps and build

In order to build this project you will need to link against HaruPDF lib, libm and libz.

`make` will also run `flex` and `bison` against the correct files as long as you have those softwares installed.
