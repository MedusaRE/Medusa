all:
	$(MAKE) -C medusa_software/barcelona
	$(MAKE) -C medusa_software/barcelona
	$(MAKE) -C medusa_software/berlin
	$(MAKE) -C medusa_software/frontend
	$(MAKE) -C medusa_software/libmedusa
	$(MAKE) -C medusa_software/libxparse
	$(MAKE) -C medusa_software/london
	$(MAKE) -C medusa_software/paris
	$(MAKE) -C medusa_software/rome
	$(MAKE) -C medusa_software/work/libmedusa_testing
	$(MAKE) -C medusa_software/work/text_editing
	$(MAKE) -C medusa_software/work/unicorn_states
	$(MAKE) -C docs
	@ echo "Done, enjoy!"

clean:
	$(MAKE) -C medusa_software/frontend
	$(MAKE) -C medusa_software/libmedusa
	$(MAKE) -C medusa_software/libxparse
	$(MAKE) -C medusa_software/work/text_editing
	$(MAKE) -C medusa_software/work/unicorn_states
	$(MAKE) -C docs clean

install:
	$(MAKE) -C medusa_software/libmedusa install