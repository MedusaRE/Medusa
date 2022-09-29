all:
	cd medusa_software/barcelona/; make
	cd medusa_software/berlin/; make
	cd medusa_software/frontend/; make
	cd medusa_software/libmedusa/; make
	cd medusa_software/libxparse/; make
	cd medusa_software/london/; make
#	cd medusa_software/work/lief_testing/; make
	cd medusa_software/paris/; make
	cd medusa_software/rome/; make
	cd medusa_software/work/java/; make
	cd medusa_software/work/libmedusa_testing/; make
	cd medusa_software/work/text_editing/; make
	cd medusa_software/work/unicorn_states/; make
	cd docs; pdflatex book.tex
	sh tools/badges/badges.sh
	@ echo "Done, enjoy!"

clean:
	cd medusa_software/frontend/; make clean
	cd medusa_software/libmedusa/; make clean
	cd medusa_software/libxparse/; make clean
#	cd medusa_software/work/lief_testing/; make clean
	cd medusa_software/work/text_editing/; make clean
	cd medusa_software/work/unicorn_states/; make clean

install:
	cd medusa_software/libmedusa; make install