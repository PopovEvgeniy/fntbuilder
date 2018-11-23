install:
	@echo Installation in progress. Please wait
	@gcc fntbuilder.c -g0 -O0 -o fntbuilder
	@chmod ugo+rx fntbuilder
	@cp -f -p fntbuilder /bin/
	@echo Installation was successfuly complete
uninstall:
	@rm -f /bin/fntbuilder
	@echo Uninstallation was successfuly complete