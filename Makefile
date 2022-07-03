all:
	cd medusa_software/frontend/; make
	cd medusa_software/libmedusa/; make
	cd medusa_software/libxparse/; make
	cd medusa_software/work/lief_testing/; make
	cd medusa_software/work/text_editing/; make
	cd medusa_software/work/unicorn_states/; make
	@ echo "Done, enjoy!"

clean:
	cd medusa_software/frontend/; make clean
	cd medusa_software/libmedusa/; make clean
	cd medusa_software/libxparse/; make clean
	cd medusa_software/work/lief_testing/; make clean
	cd medusa_software/work/text_editing/; make clean
	cd medusa_software/work/unicorn_states/; make clean