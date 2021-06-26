# Anti Malware Stresser

#### Nicolas SERVOT

The goal of this software is to perform malicious activity like anti-debuggin or anti reverse-engineering tricks while checkin if we're still under the radar or not. 
At the moment, 3 features are implemented : anti-debugging, anti-analysis and anti VM. All 3 of these tests are called in the main function sequentially. If a countermeasure is detected, the test return FAIL, otherwise it returns PASS.
One more feature are to come : the anti-disassembler. 

## How to run

To create the *main* executable, run the makefile with  ``` make```.
To clean, use the phony function ``` make clean ```.

## Anti-debugging

The goal of this test is to detect processes corresponding to reverse engineering tools such as ghidra, PETools, wireshark, radare etc... To do so, the list of the name of all running processes ```ps -eo comm ``` is compared to a list of known process name corresponding to such tools. If there is at least one of such a process running, the test fails, otherwise it passes.

### Ptrace

The premis of this technique is that ptrace can only be called once on a process. If it return -1, then the process is already traced. gdb is an example of a debugger tracing the process. For instance, if gdb is called on *main*, this test is supposed to fail.

### Breakpoint detecter

The goal of this test if to check wether or not a breakpoint has been set. When using gdb, setting  breakpoints is done by replacing the byte at a given address with an int 3 Opcode, which is 0xcc. Therefore, the test scan the address space for 0xcc. This feature is still not working as it yields a segfault when called.

## Anti-Analysis

## Anti VM

Forensics is usually performed with some sort of sandboxing, as the malware needs to be isolated from the host machine to perform dynamic analysis. 3 subroutines are implemented to check for VM signs for redundance purpose. Root privilege is not assumed in order to make this test as general as possible. 

### Kernel modules

Running the ``` /sbin/lsmod``` command returns the list of currently loaded modules. Some modules are trademarks of a certain VM. The test is implemented for both VMware and VirtualBox, therefore ```grep "vmw \| vboxguest"``` is performed on the output of lsmod and stored in a file. If the file is empty, the test passes, otherwise it fails.

### PCI buses

The utility *lspci* displays information about PCI buses in the system and devices connected to them. Some controller are labelled with the name of the VM. The command ```lspci | grep "VMware \| VirtualBox" > file.txt``` selects the feature of interest if they exist. If the file is empty, the test succeeds, otherwise it fails.

### SCSI devices

Running ```/proc/scsi/scsi``` on a linux machine returns the list of devices connected to the small computer system interface subsystem. Then, we can identify the machine type with the model name. The trick is the same as the las 2 subroutines.