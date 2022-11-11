PDFLATEX=pdflatex

all: book.pdf

clean:
	rm -f book.pdf
	rm -f book*.svg
	rm -f book*.html
	rm -f book*.xref

book.pdf: book.tex
	$(PDFLATEX) $^