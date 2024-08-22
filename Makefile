password: password.c
	gcc -o output password.c -lsodium
install: all
	cp output spwdg
	sudo mv spwdg /usr/bin	
uninstall: 
	sudo rm /usr/bin/spwdg
