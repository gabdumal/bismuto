# DCC163 Operational Research

## Environment

This project is configured with **CMake**, and uses **Clang** as the compiler.

Be sure to have installed these tools in your system:

- `gcc`
- `clang`
- `clang-tools-extra`
- `cmake`

### Windows

You can download **MinGW-w64** installer, which includes the necessary tools, in this [repository](https://github.com/niXman/mingw-builds-binaries?tab=readme-ov-file#mingw-w64-binaries).

Install also **Clang** compiler, which can be downloaded from the official [website](https://releases.llvm.org/download.html).
Remember to install the **LLVM** toolchain, which includes the **Clang** compiler, and the **Clang Tools Extra**, which includes the **clang-tidy** tool.

Then install **CMake** from the official [website](https://cmake.org/download/).

### Fedora

You can install the necessary tools using the following command:

```bash
sudo dnf install cmake clang clang-tools-extra
```

## Extensions

The project is set to be developed in Visual Studio Code, with the following extensions:

- CMake Tools
- CMake
- C/C++
- clangd

## Compiling and Running

In order to compile and run the project, follow the instructions below.

Create a folder named `/build` in the root of the repository.

```bash
mkdir build
```

### Command Line

Run the following command to **configure** CMake:

```bash
# UNIX systems
cmake -S . -B build

# Windows with MinGW
cmake -S . -B build -G "MinGW Makefiles"
```

In order to **compile** the project, run:

```bash
cmake --build build
```

Then you can execute the compiled program, by **running** the executable file generated in the `/build` folder.

In **UNIX** systems, you can run the following command:

```bash
# UNIX systems
./build/src/optimization_model

# Windows with MinGW
.\build\src\optimization_model.exe
```

If there are any errors, try deleting the `/build` folder and running the commands again.

### VsCode

In order to compile and run the project in Visual Studio Code, you can use the **CMake Tools** extension.

Open the command palette with `Ctrl+Shift+P`, and select the option `CMake: Configure`.

Then, select the option `CMake: Build`.

After that, you can run the program by selecting the option `CMake: Run`.
