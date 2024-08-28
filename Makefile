main: main.c
	gcc -o spwdg main.c -lsodium
install:
	sudo mv spwdg /usr/bin	
uninstall: 
	sudo rm /usr/bin/spwdg
