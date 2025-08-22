install:
	@echo Installation in progress. Please wait
	@$(CC) fntbuilder.c -g0 -O0 -o /bin/fntbuilder
	@chmod ugo+rx /bin/fntbuilder
	@echo Installation was successfully completed
uninstall:
	@rm -f /bin/fntbuilder
	@echo Uninstallation was successfully completed