install:
	@echo Compiling the program source code. Please wait
	@gcc fntbuilder.c -g0 -O0 -o fntbuilder
	@echo Compilation successfuly complete
	@chmod ugo+rx fntbuilder
	@echo Enter you user password for do last installation step
	@sudo cp -f -p fntbuilder /bin/
	@echo Installation complete
uninstall:
	@echo Enter you user password for uninstall this software
	@sudo rm -f /bin/fntbuilder
	@echo Uninstallation complete