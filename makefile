install:
	@echo Installation in progress. Please wait
	@gcc fntbuilder.c -g0 -O0 -o /bin/fntbuilder
	@chmod ugo+rx /bin/fntbuilder
	@echo Installation was successfuly complete
uninstall:
	@rm -f /bin/fntbuilder
	@echo Uninstallation was successfuly complete