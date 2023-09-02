# OS-Archive
The repository contains the codes and related files of two final projects for my undergrad operating system course.
## Project 1

I studied and analyzed the implementation of system calls in the xv6 operating system code. I added a new pssyscall() system call to xv6 to allow retrieving process information. I also modified the ps command in xv6 to use the new pssyscall() to display process status information. To test my new system call and command, I utilized the xv6 environment with QEMU virtualization. My test results demonstrated that pssyscall() successfully returned process data to the ps command for display.

## Project 2

I developed a loadable kernel module (LKM) in C that implements a banking application. The LKM allows opening customer accounts, checking balances, transferring funds between accounts, and closing accounts. To enable these financial transactions, the LKM implements core file operations like open, read, write, and close. I created device nodes using mknod to associate the LKM with account file descriptors. I wrote test applications in C and Python that perform banking tasks by exercising the LKM API. By loading and unloading the module, I verified that my banking LKM integrated correctly with the Linux kernel.
<p align="center">
  <img src="https://github.com/MelvinMo/OS-Archive/blob/main/Project%202/project2.jpg" alt="IMG" />
</p>
