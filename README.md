# Bismuto Optimizer

## Environment

### Developing

This project is configured with **CMake**, and uses **Clang** as the compiler.

Be sure to have installed these tools in your system:

- `gcc`
- `clang`
- `clang-tools-extra`
- `cmake`
- `ninja` (optional)

#### Windows

You can download **MinGW-w64** installer, which includes the necessary tools, in this [repository](https://github.com/niXman/mingw-builds-binaries?tab=readme-ov-file#mingw-w64-binaries).

Install also **Clang** compiler, which can be downloaded from the official [website](https://releases.llvm.org/download.html).
Remember to install the **LLVM** toolchain, which includes the **Clang** compiler, and the **Clang Tools Extra**, which includes the **clang-tidy** tool.

Then install **CMake** from the official [website](https://cmake.org/download/).

#### Fedora

You can install the necessary tools using the following command:

```bash
sudo dnf install cmake clang clang-tools-extra ninja-build

# Maybe you need to install the following packages
sudo dnf groupinstall "Development Tools"
```

For cross-compiling to Windows, you can install the **MinGW** tools.

```bash
sudo dnf install mingw32-gcc mingw32-crt mingw64-gcc mingw64-gcc-c++ mingw64-crt mingw32-winpthreads mingw64-winpthreads
```

### Extensions

The project is set to be developed in Visual Studio Code, with the following extensions:

- CMake Tools
- CMake
- C/C++
- clangd

### Compiling and Running

In order to compile and run the project, follow the instructions below.

Create a folder named `/build` in the root of the repository.

```bash
mkdir build
```

#### Command Line

Run the following command to **configure** CMake:

```bash
# UNIX systems
cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=/usr/lib64/ccache/clang -DCMAKE_CXX_COMPILER:FILEPATH=/usr/lib64/ccache/clang++ -S . -B build -G Ninja

# Windows with MinGW
cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=/usr/lib64/ccache/clang -DCMAKE_CXX_COMPILER:FILEPATH=/usr/lib64/ccache/clang++ -S . -B build -G "MinGW Makefiles"
```

In order to **compile** the project, run:

```bash
cmake --build build
```

Then you can execute the compiled program, by **running** the executable file generated in the `/build` folder.

In **UNIX** systems, you can run the following command:

```bash
# UNIX systems
./build/src/bismuto

# Windows with MinGW
.\build\src\bismuto.exe
```

If there are any errors, try deleting the `/build` folder and running the commands again.

#### VsCode

In order to compile and run the project in Visual Studio Code, you can use the **CMake Tools** extension.

Open the command palette with `Ctrl+Shift+P`, and select the option `CMake: Configure`.

Then, select the option `CMake: Build`.

After that, you can run the program by selecting the option `CMake: Run`.

### Dependencies

This project uses the **GLPK** library, which is a open-source linear programming library.

#### Fedora

You can install the library using the following commands:

```bash
sudo dnf install glpk-utils
sudo dnf install glpk-doc
sudo dnf install glpk-devel
```

You can run the command-line interface `glpsol` to test if the library was installed correctly.

```bash
glpsol --version
```

The **documentation** can be found in the `/usr/share/doc/glpk-doc` folder.

To cross-compile to Windows, you have to install the **MinGW** version of the library.
It can be found in the official [website](https://sourceforge.net/projects/winglpk/).
