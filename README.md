# **HTTP Server**

![Project Status](https://img.shields.io/badge/Status-In%20Progress-yellow)  
![Languages](https://img.shields.io/badge/C%2B%2B-100%25-blue)  
![License](https://img.shields.io/badge/License-MIT-green)

A simple yet efficient HTTP server written in C++, capable of serving static HTML pages and handling multiple client connections using multithreading (in progress). This project demonstrates the fundamentals of socket programming, HTTP protocol handling, and concurrent programming.

---

## **Features**

- 🌐 **Serve Static Webpages**  
  Capable of serving basic HTML files over HTTP. 

- ⚙️ **Multithreading (In Progress)**  
  Adding support for handling multiple client connections concurrently.  

- 🔒 **Customizable**  
  Easily extendable to include additional HTTP methods or features like HTTPS.  

---

## **Installation**

1. **Clone the Repository**  
   ```bash
   git clone https://github.com/bignya23/http-server.git
   cd http-server
   ```

2. **Build the Project**  
   Ensure you have a C++ compiler and CMake installed. Then, run:
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```

3. **Run the Server**  
   ```bash
   ./HttpServer.exe
   ```

---

## **Current Progress**

### Completed:
- Basic HTTP request parsing.
- Serving static HTML files.  

### In Progress:
- Multithreading to handle multiple clients concurrently.
- Graceful error handling and logging.

---

## **Planned Features**

- 🔗 **Support for Additional HTTP Methods**  
  Extend to include POST, PUT, etc.  

- 🔒 **HTTPS Support**  
  Secure communication using SSL/TLS.  

- 📊 **Dynamic Content Serving**  
  Serve dynamic pages with CGI or custom backend integration.  

---


## **How It Works**

1. **Socket Programming**  
   The server uses sockets to listen for incoming connections and communicate with clients.

2. **HTTP Request Handling**  
   Parses HTTP GET requests to serve the requested files.

3. **Multithreading (WIP)**  
   Plans to use a thread pool to handle multiple client requests simultaneously.

---
## **Contributing**

Contributions are welcome! Feel free to submit issues or pull requests to enhance the functionality or fix bugs.

---

## **License**

This project is licensed under the MIT License. See `LICENSE` for details.

---

## **Contact**

📧 **Your Name**  
GitHub: [YourUsername](https://github.com/yourusername)  
Email: your.email@example.com  

---

This template ensures that your README remains concise but informative as you work on new features. Update the "Current Progress" and "Planned Features" sections as you develop your project.
