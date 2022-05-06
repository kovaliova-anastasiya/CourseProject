#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>

// mian numer_of_proc number_of_files
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Not enough arguments, pass number of proc and files" << std::endl;
        return -1;
    }

    const int PROC_COUNT = atoi(argv[1]);
    const int FILES_COUNT = atoi(argv[2]);

    std::cout << "Distributor:: Starting tasks\n";
    auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<pid_t> pids(PROC_COUNT);

    for (int i = 0; i < PROC_COUNT; ++i) {
        pid_t current_pid = fork();
        if (current_pid > 0) {
            pids.push_back(current_pid);
        } else if (current_pid == 0) {
            int ret_code = execl("sorter","sorter", 
                    std::to_string(i).c_str(), std::to_string(FILES_COUNT).c_str(), std::to_string(PROC_COUNT).c_str()
                , (char*)0);
            if (ret_code == -1) {
                std::cout << "Distributor:: Process launch failed\n";
                return -1;
            }
            return 0;
        } else {
            std::cout << "Distributor::Cannot create process with number " << i << "\n";
            return -1;
        }
    }
    std::cout << "Distributor:: All tasks started normally\n";
    for (int i = 0; i < PROC_COUNT; ++i) {
        int status;
        while (-1 == waitpid(pids[i], &status, 0));
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            std::cout << "Process " << i << " (pid " << pids[i] << ") failed\n";
            exit(1);
        }
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    printf(
        "Distributor:: Total time spent: %ld ms \n",
        std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
    );
}