PICS=
OS=$(shell uname -s)
#RCMD=./weaver.sh
RCMD=R CMD Sweave
BIBS = *.bib

ifeq ($(OS),Darwin)
	OPEN=open
else
	OPEN=xpdf
endif

PICSPDF := $(PICS:.eps=.pdf)

$(FILENAME).dvi: $(FILENAME).tex $(PICS)
	latex $(FILENAME).tex	

all: 

.PRECIOUS: %.tex

%.tex : %.Snw
	$(RCMD) $< 

%.eps : %.pic
	groff -ms -mpic -p pic_macros $< > tmp.ps
	ps2epsi tmp.ps $@
	ps2pdf $@


%.eps : %.gpic
	groff -ms -mpic -p pic-macros $< > tmp.ps
	ps2epsi tmp.ps $@
	ps2pdf $@

%.pdf : %.eps
	epstopdf $<

#$(FILENAME).pdf: $(FILENAME).tex $(PICSPDF)
#	pdflatex $(FILENAME).tex

%.pdf: %.tex $(PICS)
	pdflatex $<

%.display: %.pdf
	$(OPEN) $<


bbl: $(MAIN).bbl

$(MAIN).bbl: $(BIBS) $(MAIN).dvi
	- latex $(MAIN)
	- latex $(MAIN)
	- bibtex $(MAIN)
	- bibtex $(MAIN)
	- ed - $(MAIN).bbl <fixbbl
	- latex $(MAIN)
	- latex $(MAIN)
	latex $(MAIN)

display: $(MAIN).ps
	gv $(MAIN).ps

clean:
	rm -f $(MAIN).ps $(MAIN).pdf $(MAIN).log $(MAIN).dvi $(MAIN).aux $(MAIN).bbl $(MAIN).blg $(ART)
	- ed - $(MAIN).bbl <fixbbl

