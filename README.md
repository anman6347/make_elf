<a name="readme-top"></a>

<!-- PROJECT LOGO -->
<br />
<div align="center">
    <a href="https://www.designevo.com/jp/">
        <img src="logo/logo.png" alt="Logo" width="80" height="80">
    </a>
    <h3 align="center">ELF Maker</h3>
    <p align="center">ELF Maker doesn't use any third-party libraries</p>
</div>

<!-- TABLE OF CONTENTS -->
<details align="center">
    <summary>Table of Contents</summary>
    <div class="ulc">
        <ol type="i" style="inside">
        <li><a href="#about-the-project">About The Project</a></li>
        <li><a href="#getting-started">Getting Started</a></li>
        <li><a href="#usage">Usage</a></li>
        <li><a href="#roadmap">Roadmap</a></li>
        <li><a href="#license">License</a></li>
        </ol>
    </div>
</details>
<style>
.ulc {
    display: flex;
    align-items: center;
    flex-direction: column;
}
</style>

<!-- ABOUT THE PROJECT -->
## About The Project
ELF maker outputs ELF files desired by you.\
This project is being developed by an individual and has just begun, so development of most features has not yet been carried out.\
ELF Maker doesn't use any third-party libraries :)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Built With
🚧 WIP 🚧

<img src="https://upload.wikimedia.org/wikipedia/commons/1/18/C_Programming_Language.svg" width=6%>
<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

### Installation
1. Clone the repo
    ```sh
    git clone git@github.com:your_username_/make_elf.git
    ```
2. Compile main.c
    ```sh
    gcc main.c -o ELFMaker
    ```
<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage
ELF Maker can currently only generate simple object files.
1. Make object file
    ```sh
    ./ELFMaker > hello.o
    ```
2. Make executable file
    ```sh
    ld hello.o -o hello 
    ```
3. Test your executable file
    ```sh
    ./hello
    ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ROADMAP -->
## Roadmap
See the [open issues](https://github.com/anman6347/make_elf/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>
