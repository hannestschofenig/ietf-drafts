all: txt

chbar:
	changebar draft-ietf-tls-rfc4347-bis.0 draft-ietf-tls-rfc4347-bis.1
	rm -f draft-ietf-tls-rfc4347-bis.chbar.txt
	groff -ms -Tascii draft-ietf-tls-rfc4347-bis.1.chbar | ./fix.pl > draft-ietf-tls-rfc4347-bis.chbar.txt

txt:	
	rm -f draft-ietf-tls-rfc4347-bis.txt
	groff -ms -Tascii draft-ietf-tls-rfc4347-bis.1 | ./fix.pl > draft-ietf-tls-rfc4347-bis.txt

contents: txt
	rm -f contents.txt
	perl ./mktoc.pl < draft-ietf-tls-rfc4347-bis.txt > contents.txt




