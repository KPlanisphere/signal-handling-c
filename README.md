# Signal Handling in C

## Description
This project contains a series of C programs that demonstrate various aspects of signal handling in Unix-like operating systems. These programs illustrate how to handle signals using signal handlers, how to send signals between processes, and how to use alarms and the `setjmp`/`longjmp` functions for non-local jumps. Each file showcases different aspects of signal handling, providing a comprehensive overview of how to implement these mechanisms in C.

### Key Features
- **Signal Handlers**: Examples of setting up signal handlers using the `signal` function.
- **Inter-Process Signals**: Demonstrations of sending signals between processes using the `kill` function.
- **Alarms**: Usage of the `alarm` function to send `SIGALRM` signals after a specified amount of time.
- **Non-Local Jumps**: Examples of using `setjmp` and `longjmp` for non-local jumps in response to signals.

### Files
1. **A1P8.c**
    - Demonstrates setting up signal handlers for all signals and handling them.
    - **Key Code Snippet**:
        ```c
        #include <signal.h>
        #include <unistd.h>
        #include <stdio.h>

        void atrapa(int);

        int main() {
            int i;
            for(i = 1; i <= 64; i++)
                signal(i, atrapa);
            printf("Identificativo de proceso: %d\n", getpid());
            pause();
            printf("Continuando...\n");
        }

        void atrapa(int sig) {
            signal(sig, atrapa);
            printf("Recibida la señal: %d\n", sig);
        }
        ```
        This code sets up a signal handler for all signals and pauses the process until a signal is received.

2. **A2P8.c**
    - Illustrates the use of the `alarm` function to send `SIGALRM` signals at specified intervals.
    - **Key Code Snippet**:
        ```c
        #include <signal.h>
        #include <unistd.h>
        #include <stdio.h>

        void atrapa(int);

        int main() {
            int i;
            signal(SIGALRM, atrapa);
            printf("Identificativo de proceso: %d\n", getpid());
            alarm(5);
            pause();
            alarm(3);
            pause();
            for(i = 1; i < 10; i++) {
                alarm(1);
                pause();
            }
            return 0;
        }

        void atrapa(int sig) {
            signal(sig, atrapa);
            printf("RIIIIIIING!\n");
        }
        ```
        This code sets up a signal handler for `SIGALRM` and uses `alarm` to send `SIGALRM` signals at intervals.

3. **A3P8.c**
    - Demonstrates sending `SIGUSR1` and `SIGKILL` signals from a child process to a parent process.
    - **Key Code Snippet**:
        ```c
        #include <sys/types.h>
        #include <stdio.h>
        #include <unistd.h>
        #include <signal.h>
        #include <stdlib.h>

        void atrapa(int sig) {
            signal(sig, atrapa);
            printf("SIGUSR1, magnicidio\n");
        }

        int main() {
            pid_t padre, hijo;
            padre = getpid();
            signal(SIGUSR1, atrapa);
            if((hijo = fork()) == 0) {
                sleep(1);
                kill(padre, SIGUSR1);
                sleep(1);
                kill(padre, SIGUSR1);
                sleep(1);
                kill(padre, SIGUSR1);
                sleep(1);
                kill(padre, SIGKILL);
                exit(0);
            } else { /* padre */
                for (;;);
            }
        }
        ```
        This code sets up a signal handler for `SIGUSR1` and sends `SIGUSR1` and `SIGKILL` signals from the child process to the parent process.

4. **A4P8.c**
    - Illustrates sending a termination signal (`SIGTERM`) from a parent process to a child process.
    - **Key Code Snippet**:
        ```c
        #include <stdio.h>
        #include <signal.h>
        #include <stdlib.h>

        int main() {
            int pid, i = 10;
            if((pid = fork()) == 0) {
                while(i != 0) {
                    printf("HIJO, PID = %d\n", getpid());
                    i--;
                    sleep(1);
                }
            } else {
                sleep(10);
                printf("PADRE. Terminacion del proceso %d\n", getpid());
                kill(pid, SIGTERM);
            }
            exit(0);
        }
        ```
        This code creates a child process that prints its PID every second for 10 seconds, after which the parent process sends a termination signal (`SIGTERM`) to the child process.

5. **A5P8.c**
    - Demonstrates the use of `setjmp` and `longjmp` for non-local jumps in response to a signal.
    - **Key Code Snippet**:
        ```c
        #include <signal.h>
        #include <stdio.h>
        #include <stdlib.h>
        #include <setjmp.h>

        jmp_buf entorno;
        void atrapa(int);

        int main() {
            int valor;
            printf("longjmp y setjmp son una forma de simular el 'goto'\n\n");
            signal(SIGUSR1, atrapa);
            valor = setjmp(entorno);
            if(valor == 0) {
                printf("Inicia el punto de interrupcion del proceso.\n");
                sleep(1);
            }
            printf("Regreso al punto de interrupcion del proceso.\n");
        }

        void atrapa(int sig) {
            signal(SIGUSR1, atrapa);
            longjmp(entorno, sig);
        }
        ```
        This code sets up a signal handler for `SIGUSR1` and uses `setjmp` and `longjmp` to perform a non-local jump when the signal is received.

## How to Use
1. **Compilation**: Each C file can be compiled using a C compiler such as `gcc`.
    ```bash
    gcc A1P8.c -o A1P8
    gcc A2P8.c -o A2P8
    gcc A3P8.c -o A3P8
    gcc A4P8.c -o A4P8
    gcc A5P8.c -o A5P8
    ```

2. **Execution**: Run the compiled programs to see the output of signal handling operations.
    ```bash
    ./A1P8
    ./A2P8
    ./A3P8
    ./A4P8
    ./A5P8
    ```