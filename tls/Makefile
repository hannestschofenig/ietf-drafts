all: txt

chbar:
	changebar tls.0 tls.1
	rm -f tls.chbar.txt
	groff -ms -Tascii tls.1.chbar | ./fix.pl > tls.chbar.txt

txt:	
	rm -f tls.txt
	groff -ms -Tascii tls.1 | ./fix.pl > tls.txt

contents: txt
	rm -f contents.txt
	perl ./mktoc.pl < tls.txt > contents.txt




