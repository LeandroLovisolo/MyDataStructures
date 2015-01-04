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

Adding a new data structure
---------------------------

Follow the steps below.

1. Create a new directory on the project's root, for example `foo`.
2. Add the directory you just created to the `DIRS` variable in the `Makefile`, for example `DIRS = avl heap skiplist foo`.
3. Create an empty `Makefile` inside the newly created directory, define a `BIN` variable with the desired target binary name, then include `common/Makefile`. Check out the `Makefile` in the directory of any data structure for an example.
4. Add your source code to the new directory.
5. Define the data structure's JavaScript interface inside a `#ifdef EMSCRIPTEN` conditional block, as explained shortly below.
6. Define your Unix binary's `main` function in an `#else` block following the previous `#ifdef` to make sure it's not included in the JavaScript build.
7. Add a new entry for your data structure in `website/js/config.js` as explained below.

### Defining the data structure's JavaScript interface ###

- Your data structure's JavaScript interface is defined as a collection of functions that take zero or one integer parameter and return void.
- The function names need to start with a common prefix, for example `foo_`.
- Additionally, you need to provide a print function that takes zero parameters and returns a string of type `const char *` containing an ASCII representation of your data structure. This is what the user will see in the output panel. If your prefix is `foo_`, then the function's name needs to be `foo_print`. This function will be called by the web interface every time the user performs an operation on your data structure.
- Your functions must be wrapped inside an `extern "C" { ... }` block, and you need to write the `EMSCRIPTEN_KEEPALIVE` macro in your function declarations between the return type and the function name. For example:
```
extern "C" {
  void EMSCRIPTEN_KEEPALIVE foo_insert(int x) {
    ...
  }

  void EMSCRIPTEN_KEEPALIVE foo_clear() {
    ...
  }

  const char * EMSCRIPTEN_KEEPALIVE foo_print() {
    ...
  }
}

```

### Adding the data structure to `website/js/config.js` ###

Pending.

License
-------

MIT licensed.
