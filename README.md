### Camera Reports Parser

__Donate to this project to keep it alive.__

<noscript><a href="https://liberapay.com/hdcdigi/donate"><img alt="Donate using Liberapay" src="https://liberapay.com/assets/widgets/donate.svg"></a></noscript>

__Public Roadmap__
https://trello.com/b/DEhIf5Hp/careports-roadmap

This project defines a simple markup language for camera assistants that can be parsed into a PDF report. This application defines the grammar and includes the code to generate the PDF report.

Currently in active development, not all features are active.

![](https://i.imgur.com/d6TANDK.png)

# Build instructions

Ensure that you have Haru PDF (https://github.com/libharu/libharu) installed to `/usr/local/lib/`

You will also need Flex and Bison 3.6. 

If building on MacOS you will need to install Bison via homebrew. Once this is installed you will need to modify the Makefile with the path of your installation. This is because MacOS ships with a outdated version of Bison nativley. 

For example:
```
ca_mu.tab.c: ca_mu.y
	bison -d ca_mu.y
```

Will become: 
```
ca_mu.tab.c: ca_mu.y
	/path/to/bison -d ca_mu.y
```

Then run:

```
make
```
