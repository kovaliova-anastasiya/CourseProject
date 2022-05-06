#include "mpi.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <chrono>

const char* executable_name = R"(C:\Users\andre\PycharmProjects\term_paper\WindowsApp\Sorter\x64\Release\ProcessSorter.exe)";

// main.exe NUMBER_OF_PROCS NUMBER_OF_FILES MODE
int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Distributor::Wrong number of cmd arguments, expected 2" << std::endl;
        return -2;
    }
    const int kProcCount = atoi(argv[1]),
              kFilesCount = atoi(argv[2]);

    std::vector<HANDLE> proc_info(kProcCount);
    const auto t1 = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < kProcCount; ++i) {
        PROCESS_INFORMATION ProcessInfo;

        STARTUPINFO StartupInfo;
        ZeroMemory(&StartupInfo, sizeof(StartupInfo));
        StartupInfo.cb = sizeof StartupInfo;

        if (CreateProcess(executable_name, const_cast<char*>(
                (" " + std::to_string(i) + " " + std::to_string(kFilesCount) + " " + std::to_string(kProcCount) + " " +  std::string(argv[3])).c_str()
            ),
            NULL, NULL, FALSE, 0, NULL,
            NULL, &StartupInfo, &ProcessInfo)) {
            proc_info[i] = ProcessInfo.hProcess;
            //SetPriorityClass(proc_info[i], BELOW_NORMAL_PRIORITY_CLASS);
        } else {
            std::cout << "Distributor::The process could not be started..." << std::endl;
            std::cout << "Distributor::Error " << GetLastError() << std::endl;
        }
    }

    std::cout << "Distributor:: All processes started normally." << std::endl;
    WaitForMultipleObjects(kProcCount, &proc_info[0], TRUE, INFINITE);
    for (int i = 0; i < kProcCount; ++i) {
        CloseHandle(proc_info[i]);
    }
    const auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Distributor:: Total time spent: " <<
                 std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() <<
                 " ms" << std::endl;
}