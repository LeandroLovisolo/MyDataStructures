MyDataStructures
================

MyDataStructures is a collection of basic data structures written in the C++ programming language, and a web interface that allows you to visualize them and interact with them.

The C++ data structures are compiled into JavaScript using [Emscripten](http://kripken.github.io/emscripten-site/) and executed in the browser.

The web interface is built using [Ember](http://emberjs.com) and [Bootstrap](http://getbootstrap.com).

Requirements
------------

In order to build the Unix binaries GNU Make and Clang are required. (Alternatively you can build the binaries using GCC, but you need to set the `CXX` variable to `g++` in `common/Makefile`.)

To build the website you need the Emscripten SDK, Node.js and NPM installed and in your path.

Building the Unix binaries
--------------------------

Run `make clean all` from the root directory.

Building the static website
---------------------------

Install the Broccoli compilation library's command line interface.

```
cd website
npm install -g broccoli-cli
```

Then run `make website` from the project's root directory. This both compiles the data structures into JavaScript and builds the website.

You can then run the website either by opening the `website/dist/index.html` file in a web browser or by running `make serve` from the project's root directory and visiting `http://localhost:4200`.

License
-------

MIT licensed.
