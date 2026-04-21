# OS Jackfruit – Mini Container Runtime

## 📌 Overview
This project implements a lightweight container runtime in C using Linux namespaces.

It demonstrates how containers achieve isolation without using Docker.

---

## 🧠 Architecture

Flow of execution:

clone() → sethostname() → chroot() → mount /proc → execvp()

### Components:
- **my_engine.c** → main container runtime
- **rootfs-alpha** → isolated filesystem
- **Linux kernel** → provides namespaces

---

## ⚙️ Features

- PID Isolation using `CLONE_NEWPID`
- Hostname Isolation using `CLONE_NEWUTS`
- Mount Isolation using `CLONE_NEWNS`
- Filesystem Isolation using `chroot()`
- Command execution inside container

---

## 🔬 System Calls Used

| System Call | Purpose |
|------------|--------|
| clone() | Create isolated process |
| chroot() | Change root filesystem |
| sethostname() | Change container hostname |
| execvp() | Execute command |
| waitpid() | Wait for container exit |

---

## ▶️ How to Run

```bash
cd boilerplate
gcc my_engine.c -o my_engine
sudo ./my_engine run c1 rootfs-alpha /bin/bash
