
SRC  := $(wildcard *.xml)

HTML := $(patsubst %.xml,%.html,$(SRC))
TXT  := $(patsubst %.xml,%.txt,$(SRC))
DIF  := $(patsubst %.xml,%.diff.html,$(SRC))

all: $(HTML) $(TXT) $(DIF)

#please, instead of chsning S2B here, amke S2B be on your path
S2B=s2x.pl -n
#S2B=/home/ekr/doc/ietf-drafts/ekr/s2b/s2x.pl
#S2B = cp

#%.html: %.xml
#	../xml2rfc.tcl $^ $@

draft-jennings-p2psip-new.ixml: draft-jennings-p2psip-new.xml
	$(S2B) $< $@

draft-jennings-p2psip-new.txt: draft-jennings-p2psip-new.ixml
	xml2rfc $^ $@

draft-jennings-p2psip-new.html: draft-jennings-p2psip-new.ixml
	xml2rfc $^ $@


%.html: %.xml
	xsltproc -o $@ ../rfc2629.xslt $^

%.txt: %.xml
	xml2rfc $^ $@

%.diff.html: %.txt
	htmlwdiff  $^.old $^ >  $@
