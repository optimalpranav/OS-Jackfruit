# OS Jackfruit – Mini Container Runtime

## 📌 Description
This project implements a lightweight container runtime using Linux namespaces in C.

It demonstrates how containers work internally without using Docker.

---

## 🚀 Features
- PID Isolation (CLONE_NEWPID)
- Hostname Isolation (CLONE_NEWUTS)
- Filesystem Isolation using chroot()
- Mount Isolation (CLONE_NEWNS)
- Command execution inside container

---

## ⚙️ Technologies Used
- C Programming
- Ubuntu 22.04
- Linux System Calls:
  - clone()
  - chroot()
  - execvp()
  - sethostname()

---

## 🧩 How It Works

Flow:
clone() → sethostname() → chroot() → mount /proc → execvp()

---

## ▶️ How to Run

```bash
cd boilerplate
gcc my_engine.c -o my_engine
sudo ./my_engine run c1 rootfs-alpha /bin/bash
