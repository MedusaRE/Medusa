include res/make/vars/tools.mk

.PHONY: all
all:
	$(MAKE) -C medusa_software/paris
	$(MAKE) -C medusa_software/libmedusa
	$(MAKE) -C medusa_software/warsaw
	$(MAKE) -C medusa_software/libxparse
	$(MAKE) -C medusa_software/barcelona
	$(MAKE) -C medusa_software/barcelona
	$(MAKE) -C medusa_software/berlin
	$(MAKE) -C medusa_software/frontend
	$(MAKE) -C medusa_software/london
	$(MAKE) -C medusa_software/rome
	$(MAKE) -C medusa_software/work/libmedusa_testing
	$(MAKE) -C medusa_software/work/text_editing
	$(MAKE) -C medusa_software/work/unicorn_states
	$(MAKE) -C docs
	$(MAKE) -C www

.PHONY: clean
clean:
	$(MAKE) -C medusa_software/paris clean
	$(MAKE) -C medusa_software/libxparse clean
	$(MAKE) -C medusa_software/libmedusa clean
	$(MAKE) -C medusa_software/barcelona clean
	$(MAKE) -C medusa_software/barcelona clean
	$(MAKE) -C medusa_software/berlin clean
	$(MAKE) -C medusa_software/frontend clean
	$(MAKE) -C medusa_software/london clean
	$(MAKE) -C medusa_software/rome clean
	$(MAKE) -C medusa_software/warsaw clean
	$(MAKE) -C medusa_software/work/libmedusa_testing clean
	$(MAKE) -C medusa_software/work/text_editing clean
	$(MAKE) -C medusa_software/work/unicorn_states clean
	$(MAKE) -C docs clean
	$(MAKE) -C www clean

.PHONY: install
install:
	$(MAKE) -C medusa_software/libmedusa install
	$(MAKE) -C www install
	$(MAKE) -C medusa_software/frontend install

.PHONY: gitlab-runner_build
gitlab-runner_build:
	gitlab-runner exec shell build