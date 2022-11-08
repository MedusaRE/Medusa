all:
	$(MAKE) -j`nproc` -C medusa_software/paris
	$(MAKE) -j`nproc` -C medusa_software/libxparse
	$(MAKE) -j`nproc` -C medusa_software/libmedusa
	$(MAKE) -j`nproc` -C medusa_software/barcelona
	$(MAKE) -j`nproc` -C medusa_software/barcelona
	$(MAKE) -j`nproc` -C medusa_software/berlin
	$(MAKE) -j`nproc` -C medusa_software/frontend
	$(MAKE) -j`nproc` -C medusa_software/london
	$(MAKE) -j`nproc` -C medusa_software/rome
	$(MAKE) -j`nproc` -C medusa_software/work/libmedusa_testing
	$(MAKE) -j`nproc` -C medusa_software/work/text_editing
	$(MAKE) -j`nproc` -C medusa_software/work/unicorn_states
	$(MAKE) -j`nproc` -C docs

clean:
	$(MAKE) -j`nproc` -C medusa_software/paris clean
	$(MAKE) -j`nproc` -C medusa_software/libxparse clean
	$(MAKE) -j`nproc` -C medusa_software/libmedusa clean
	$(MAKE) -j`nproc` -C medusa_software/barcelona clean
	$(MAKE) -j`nproc` -C medusa_software/barcelona clean
	$(MAKE) -j`nproc` -C medusa_software/berlin clean
	$(MAKE) -j`nproc` -C medusa_software/frontend clean
	$(MAKE) -j`nproc` -C medusa_software/london clean
	$(MAKE) -j`nproc` -C medusa_software/rome clean
	$(MAKE) -j`nproc` -C medusa_software/work/libmedusa_testing clean
	$(MAKE) -j`nproc` -C medusa_software/work/text_editing clean
	$(MAKE) -j`nproc` -C medusa_software/work/unicorn_states clean
	$(MAKE) -j`nproc` -C docs

install:
	$(MAKE) -j`nproc` -C medusa_software/libmedusa install