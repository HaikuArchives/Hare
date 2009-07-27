army:
	$(MAKE) --directory=./String/ install
	$(MAKE) --directory=./Matcher/ install
	$(MAKE) --directory=./Santa/ install

install:
	$(MAKE) --directory=./String/ install
	$(MAKE) --directory=./Matcher/ install
	$(MAKE) --directory=./AudioInfo/ install
	$(MAKE) --directory=./Santa/ install
	$(MAKE) --directory=./FlipSideAE/ install
	$(MAKE) --directory=./AudioInfo/ --makefile=MakefileTTE release

clean:
	$(MAKE) --directory=./String/ clean
	$(MAKE) --directory=./Matcher/ clean
	$(MAKE) --directory=./AudioInfo/ clean
	$(MAKE) --directory=./Santa/ clean
	$(MAKE) --directory=./FlipSideAE/ clean
	$(MAKE) --directory=./AudioInfo/ --makefile=MakefileTTE clean

release:
	$(MAKE) --directory=./String/ release
	$(MAKE) --directory=./Matcher/ release
	$(MAKE) --directory=./AudioInfo/ release
	$(MAKE) --directory=./Santa/ release
	$(MAKE) --directory=./FlipSideAE/ release
	$(MAKE) --directory=./AudioInfo/ --makefile=MakefileTTE release

cleaninstall:
	$(MAKE) --directory=./String/ cleaninstall
	$(MAKE) --directory=./Matcher/ cleaninstall
	$(MAKE) --directory=./AudioInfo/ cleaninstall
	$(MAKE) --directory=./Santa/ cleaninstall
	$(MAKE) --directory=./FlipSideAE/ cleaninstall
	$(MAKE) --directory=./AudioInfo/ --makefile=MakefileTTE cleaninstall