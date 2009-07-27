install:
	$(MAKE) --directory=./src install

cleaninstall:
	$(MAKE) --directory=./src cleaninstall

clean:
	$(MAKE) --directory=./src clean

release:
	$(MAKE) --directory=./src release

cleansettings :
	rm -rf /boot/home/config/settings/Hare/$(NAME)
