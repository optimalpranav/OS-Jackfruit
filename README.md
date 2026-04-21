# OS Jackfruit – Mini Container Runtime

## 1. Team Information

| Name       | SRN        |
|Rahul Bellary | PES1UG24CS357 |
| Pranav S S | PES1UG24CS336 |

---

## 2. Build and Run Instructions

### Prerequisites

```bash
sudo apt update
sudo apt install build-essential
```

---

### Compile

```bash
cd boilerplate
gcc my_engine.c -o my_engine
```

---

### Run Container

```bash
sudo ./my_engine run c1 rootfs-alpha /bin/bash
```

---

### Inside Container

```bash
ps
hostname
ls /
```

---

### Run Command

```bash
sudo ./my_engine run c2 rootfs-alpha /bin/ls
```

---

## 3. Demo Screenshots

### Process Isolation

![PS](screenshots/ps.png)

### Hostname Isolation

![Hostname](screenshots/hostname.png)

### Filesystem Isolation

![LS](screenshots/ls.png)

### Full Execution

![Full Run](screenshots/full_run.png)

---

## 4. Engineering Analysis

### 4.1 Isolation Mechanisms

The container runtime uses Linux namespaces for isolation:

* **CLONE_NEWPID** → Provides process isolation (container sees its own processes)
* **CLONE_NEWUTS** → Allows setting a separate hostname for container
* **CLONE_NEWNS** → Provides mount namespace isolation

Additionally, `chroot()` is used to restrict the filesystem view of the container.

---

### 4.2 Execution Flow

clone() → sethostname() → chroot() → mount /proc → execvp()

---

### 4.3 Observations

* Only container processes are visible using `ps`
* Hostname changes to `container`
* Filesystem is isolated from host
* Commands run independently inside container

---

## 5. Design Decisions

* Used `chroot()` instead of `pivot_root` for simplicity
* Focused on namespace-based isolation
* Implemented minimal container runtime instead of full Docker-like system

---

## 6. Limitations

* No cgroups (no CPU/memory limits)
* No networking namespace
* Limited to basic container functionality

---

## 7. Conclusion

Successfully implemented a lightweight container runtime using Linux namespaces, demonstrating core concepts behind containerization.
