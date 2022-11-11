.PHONY: all
all: medusa-re.org

.PHONY: medusa-re.org
medusa-re.org: medusa-re.org/book.pdf

medusa-re.org/book.pdf: ../docs/book.pdf
	cp $< $@

clean:
	rm -f medusa-re.org/book.pdf