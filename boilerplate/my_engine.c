#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>
#include <string.h>

#define STACK_SIZE (1024 * 1024)
char stack[STACK_SIZE];

// Function executed inside container
int container_main(void *arg) {
    char **args = (char **)arg;

    char *rootfs = args[0];
    char **cmd = &args[1];

    printf("[+] Inside container!\n");

    // Set hostname
    sethostname("container", 10);

    // Fix hostname resolution
    system("echo '127.0.0.1 container' >> /etc/hosts");

    // Change root filesystem
    if (chroot(rootfs) != 0) {
        perror("chroot failed");
        return 1;
    }

    chdir("/");

    // Mount proc filesystem
    system("mount -t proc proc /proc");

    // Execute command
    execvp(cmd[0], cmd);
    perror("exec failed");

    return 1;
}

int main(int argc, char *argv[]) {

    if (argc < 5) {
        fprintf(stderr, "Usage: %s run <id> <rootfs> <command>\n", argv[0]);
        return 1;
    }

    char *rootfs = argv[3];
    char **cmd = &argv[4];

    // Prepare arguments for clone
    char *args[100];
    args[0] = rootfs;

    int i;
    for (i = 0; i < argc - 4; i++) {
        args[i + 1] = cmd[i];
    }
    args[i + 1] = NULL;   // 🔥 IMPORTANT FIX

    // Create container using namespaces
    pid_t pid = clone(container_main, stack + STACK_SIZE,
                      CLONE_NEWPID | CLONE_NEWUTS | CLONE_NEWNS | SIGCHLD,
                      args);

    if (pid < 0) {
        perror("clone failed");
        exit(1);
    }

    printf("[+] Container started with PID %d\n", pid);

    waitpid(pid, NULL, 0);

    printf("[+] Container exited\n");

    return 0;
}
