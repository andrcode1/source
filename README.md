# Standard Calculator

This is a simple standard calculator application built using C++ and wxWidgets.

## Prerequisites

Before you can run the calculator, ensure you have the following installed:

- [wxWidgets](https://www.wxwidgets.org/downloads/) (version 3.2.6 or later)
- A C++ compiler (e.g., GCC, Clang, or MSVC)

## Building and Running the Project

1. **Clone the Repository**:

git clone https://github.com/andrcode1/source.git
cd StandardCalculator

2. **Compile the Project**:

    `g++ -o StandardCalculator App.cpp MainFrame.cpp StandardCalculator.cpp -I<path_to_wxWidgets_include> -L<path_to_wxWidgets_lib> -lwx_baseu-3.2 -lwx_gtk3u_core-3.2`

    Replace `<path_to_wxWidgets_include>` and `<path_to_wxWidgets_lib>` with the actual paths to your wxWidgets include and library directories.

3. **Run the Application**:

    ` ./StandardCalculator `
