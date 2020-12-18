
<br />
<p align="center">

  <h3 align="center">Assignment: Real Estate Agency (Multithreads in C)</h3>

  <p align="center">
    This in an assignment for the Operating Systems course at Federal University of Santa Catarina to show how multithreaded processes in an operating system work.
  </p>
</p>



<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary><h2 style="display: inline-block">Table of Contents</h2></summary>
  <ol>
    <li>
      <a href="#motivation">Motivation</a>
      <a href="#description">Description</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
        </li>
    <li>
      <a href="#getting-started">Acknowledgements</a>
    </li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## Motivation
Exercise the use of concurrent programming, programming with shared memory and synchronization between threads
* Implementation of a toy application using C
* Use of POSIX threads and synchronization

## Description
Develop an application for registering and “real estate” management. The system will consist of:
* I tenant threads;
* C threads real estate brokers;
* D list of available properties;
* E list of properties delivered;

Tenant threads:
* Search for available properties in the list of available properties and, randomly choose a property to rent (remove from the queue the chosen property)
* After a random time (modeled with the sleep() command), the tenant delivers the property to the estate agent (adds the property in the list of properties delivered)
Real estate broker threads:
From time to time (waits based on sleep() commands), a broker performs one of the following actions:
* Moves delivered properties to the available properties list
* Adds a new property to the list of available properties
* Removes a property from the list of available properties

### Built With

* [C](https://www.cprogramming.com/)
* [Visual Studio](https://visualstudio.microsoft.com/pt-br/)



<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple steps.

### Prerequisites

You'll need to be on a working Linux operating system or have the pthreads C class properly installed on Windows ( I suggest using [POSIX Threads for Win32](https://sourceware.org/pthreads-win32/)). 

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/brunomanarin/pthreads.git
   ```
2. Move into the downloaded folder

   ```sh
    cd pthreads
   ```

3. Compile the code

   ```sh
    gcc main.c -o realEstate -lpthread 
   ```
4. Run the code

   ```sh
    ./realEstate
   ```

## Acknowledgements

Thanks to:
Professor Odorico Machado Mendizabal that lead the course.
Ps.:
The motivation and description parts of the Readme are from the instructions he gave us to make the assignment, just translated from Portuguese to English.
