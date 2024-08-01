# PascalCompiler
A Compiler for (a slightly simpler version of) Pascal. Written in C, Bison, and Flex

## Dependencies
- Flex
- Bison
- xmllint (from libxml2)

If using Ubuntu, run the following commands to install all dependencies:
- `sudo apt-get install flex`
- `sudo apt-get install bison`
- `sudo snap install libxml2`

## Running
- Compile the Makefile with the `make` command
- Run the `pascal` file (`./pascal`)
  - This will take Pascal language code into stdin. The best way to use this is to pipe input from `.pas` files. See tests in the `tests/` directory for examples
