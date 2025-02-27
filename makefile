install:
	@echo Installation in progress. Please wait
	@$(CC) fntbuilder.c -g0 -O0 -o /bin/fntbuilder
	@chmod ugo+rx /bin/fntbuilder
	@echo Installation successfully complete
uninstall:
	@rm -f /bin/fntbuilder
	@echo Uninstallation successfully complete