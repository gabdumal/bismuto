# Bismuto Optimizer

## Environment

### Developing

This project is configured with **CMake**, and uses **Clang** as the compiler.

Be sure to have installed these tools in your system:

- `gcc`
- `clang`
- `clang-tools-extra`
- `cmake`
- `ninja`
- `gdb` (optional)
- `lldb` (optional)

#### Windows

You can follow this [guide](https://github.com/gabdumal/msys2) to install the MSYS2 environment.
It is recommended way to install the necessary tools in Windows.

The guide recommends using the `CLANG64` environment.
Therefore, you can install the needed tools using the following commands:
  
```bash
pacman -S mingw-w64-clang-x86_64-clang
pacman -S mingw-w64-clang-x86_64-clang-tools-extra
pacman -S mingw-w64-clang-x86_64-ninja
pacman -S mingw-w64-clang-x86_64-cmake
pacman -S mingw-w64-clang-x86_64-gdb
```

#### Fedora

You can install the necessary tools using the following command:

```bash
sudo dnf install cmake clang clang-tools-extra ninja-build lldb

# Maybe you need to install the following packages
sudo dnf groupinstall "Development Tools"
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
# Windows with MSYS2 CLANG64 and Ninja
 cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=/c/msys64/clang64/bin/clang.exe -DCMAKE_CXX_COMPILER:FILEPATH=/c/msys64/clang64/bin/clang++.exe -S . -B build -G Ninja
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

#### LibreOffice

This project uses LibreOffice Calc to generate the input files for the optimization problem.

##### Windows

You can install LibreOffice through the official [website](https://www.libreoffice.org/download/download/).

Then , you need to add the LibreOffice path to the system environment variables.

```bash
setx PATH "%PATH%;C:\Program Files\LibreOffice\program"
```

##### Fedora

You can install LibreOffice using the following command:

```bash
sudo dnf install libreoffice
```

#### GLPK

This project uses the **GLPK** library, which is a open-source linear programming library.

##### Windows

Using the MSYS2 `CLANG64` environment, you can install the library using the following command:

```bash
pacman -S mingw-w64-clang-x86_64-glpk
```

You can run the command-line interface `glpsol` to test if the library was installed correctly.

```bash
glpsol --version
```

The **documentation** must be downloaded from the official [website](<https://ftp.gnu.org/gnu/glpk/>).

Select the most recent version tarball.
At the time of writing, the most recent version is [`glpk-5.0.tar.gz`](<https://ftp.gnu.org/gnu/glpk/glpk-5.0.tar.gz>).
Extraia o arquivo compactado.

A documentação pode ser encontrada na pasta `/doc`.

##### Fedora

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
