ManateeCoin is a next-generation cryptocurrency backed by manatee supporters.


## Building ManateeCoin

### On *nix

Dependencies: GCC 4.7.3 or later, CMake 2.8.6 or later, and Boost 1.55 or later.

You may download them from:

* http://gcc.gnu.org/
* http://www.cmake.org/
* http://www.boost.org/
* Alternatively, it may be possible to install them using a package manager.

```
mkdir build
cd build
cmake ..
make
```

###On Ubuntru 16.04 LTS


1. Install dependencies
	``` 
	sudo apt-get install cmake build-essential libboost-dev libboost-chrono-dev libboost-thread-dev libboost-filesystem-dev libboost-regex-dev libboost-program-options-dev
	```

2. Clone source code
	```
	git clone http://git.mananet.net/manatails/manateecoin.git
	cd manateecoin
	```

3. Build
	```
	mkdir build
	cd build
	cmake ..
	make
	```

The resulting executables can be found in `build/release/src`.

