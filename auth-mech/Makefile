auth-mech.txt: auth-mech.1
	rm -f ..txt ..toc auth-mech.txt ; cat paper-prologue auth-mech.1 | nroff -p -mpic -ms > ..txt 2> ..toc ; ./toc.pl < ..toc > toc.txt ; ./xref.pl < ..toc > xref.txt
	rm -f ..txt ..toc auth-mech.txt ; cat paper-prologue auth-mech.1 | nroff -p -mpic -ms > ..txt 2> ..toc ; ./toc.pl < ..toc > toc.txt ; ./xref.pl < ..toc > xref.txt
	rm -f ..txt ..toc auth-mech.txt ; cat paper-prologue auth-mech.1 | nroff -p -mpic -ms > ..txt 2> ..toc ; ./toc.pl < ..toc > toc.txt ; ./xref.pl < ..toc > xref.txt
	./fix.pl < ..txt > auth-mech.txt

xref:	
	rm -f xrefs.out
	groff -ms -R -p -e -Tascii paper-prologue auth-mech.1 > auth-mech.txt  > xrefs.out 2>&1
	./xref.pl < xrefs.out >! xrefs

