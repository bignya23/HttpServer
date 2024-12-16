# Multithreaded HTTP/1.1 Server

A lightweight, multithreaded HTTP/1.1 server designed to host static webpages. Built with modern C++ using **sockets**, **multithreading**, and **CMake**.

## Features

- **HTTP/1.1 Support**: Handles basic HTTP requests (GET and HEAD).
- **Static File Hosting**: Serves static HTML, CSS, JavaScript, images, and more.
- **Multithreaded Architecture**: Efficiently handles multiple client connections concurrently using a thread pool.
- **Platform**: Compatible with Windows. Made using <winsock.h>.

## Getting Started

### Prerequisites

- **C++ Compiler**: Ensure you have a compiler that supports C++11 or higher.
- **CMake**: Version 3.10 or later.

### Building the Project

1. Clone the repository:

   ```bash
   git clone https://github.com/bignya23/http-server.git
   cd http-server
   ```

2. Create a build directory and configure the project:

   ```bash
   mkdir build
   cd build
   cmake ..
   ```

3. Build the project:

   ```bash
   cmake --build .
   ```

4. Run the server:

   ```bash
   ./http-server.exe
   ```

### Configuration

You can configure the server by editing the following settings in the source code:

- **Port**: Default is `8080`.
- **Document Root**: Set to the directory containing your static files (e.g., `./www`).

## Usage

1. Place your static files (e.g., `index.html`, `style.css`, etc.) in the `www/` directory (or the configured document root).
2. Start the server:
   ```bash
   ./http-server
   ```
3. Open a browser and navigate to:
   ```
   http://<server-ip>:8080
   ```
   Replace `<server-ip>` with your server's IP address.


## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

## Acknowledgments

- Built using C++ and Socket Programming.
- Inspired by the need for lightweight and educational HTTP server implementations.

---

Feel free to use, modify, and contribute to this project!

