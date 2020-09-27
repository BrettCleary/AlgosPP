# AlgosPP
 C++ Algorithms Library

<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->

<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
  * [Built With](#built-with)
* [Installation](#installation)
* [Usage](#usage)
* [Contributing](#contributing)
* [License](#license)
* [Contact](#contact)
* [Sorting Performance](#sorting-performance)

<!-- ABOUT THE PROJECT -->
## About The Project
AlgosPP is a static library for sorting algorithms, advanced data structures, and graph algorithms.

### Features
* AlgosPPSorting
  * basic sorting algorithms
  * [introsort algorithm that matches std::sort performance](#sorting-performance)
* AlgosPPDataStructures.lib
  * Van Emde Boas Tree
    * generic
    * outperforms balanced BST std::set (log(n) time complexity) on large number of elements with log(log(n)) time complexity
  * Fibonacci Heap
* AlgosPPGraphBasic.lib
  * Graph Class
  * BFS
  * DFS
  * Topological Sort
  * Strongly Connected Components
  * Bellman Ford Single Source Shortest Paths
* AlgosPPGraphAdv.lib
  * Prims Minimum Spanning Tree
  * Dijkstras Single Source Shortest Paths
  * Floyd Warshall All Pairs Shortest Paths
  * Johnson All Pairs Shortest Paths

### Built With
* [Google Test](https://github.com/google/googletest)
* [Cmake](https://cmake.org/)

### Installation

1. Clone the repo
```sh
git clone https://github.com/BrettCleary/DigitCNN
```
OR

2. Include *.lib

<!-- USAGE EXAMPLES -->
## Usage

See unit tests for usage examples.

<!-- CONTRIBUTING -->
## Contributing

Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.

<!-- CONTACT -->
## Contact

Project Link: [https://github.com/BrettCleary/SeqNN](https://github.com/BrettCleary/AlgosPP)

## Sorting Performance

Profiling for each sorting algorithm implemented compared to std::sort:

![Imgur image](https://imgur.com/uSwUmP8.jpg)
