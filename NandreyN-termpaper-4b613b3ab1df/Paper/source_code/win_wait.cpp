WaitForMultipleObjects(PROC_COUNT, &proc_info[0],
					   TRUE, INFINITE);
for (auto i = 0; i < PROC_COUNT; ++i) {
        CloseHandle(proc_info[i]);
}