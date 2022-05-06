import argparse
import subprocess
import sys
import os
import shutil


tests_folder = "Tests"
sizes = [2, 4, 6, 8, 10]


def check_datasets_generated(max_count_needed):
    fldr_path = os.path.join(os.path.curdir, tests_folder)
    if not os.path.exists(fldr_path) or not os.path.isdir(fldr_path):
        return False
    for i in range(max_count_needed):
        file_path = os.path.join(fldr_path, "input{}.txt".format(i))
        if not os.path.exists(file_path) or not os.path.isfile(file_path):
            return False
    return True


def test_win(exec_path):
    for s in sizes:
        print(get_output(exec_path + " 4 {} 0".format(s), ""))


def test_linux(exec_path):
    raise NotImplementedError


def test_unix(exec_path):
    raise NotImplementedError 


test_packages = {
    "windows": test_win,
    "linux": test_linux,
    "unix": test_unix
}


def get_output(script, input_text):
    return subprocess.check_output(
        script,
        input=input_text,
        encoding='utf-8'
    )


if __name__ == '__main__':
    argument_parser = argparse.ArgumentParser()
    argument_parser.add_argument('--platform', required=True)
    argument_parser.add_argument('--executable', required=True)
    arguments = argument_parser.parse_args()
    target_platform = arguments.platform
    if target_platform.lower() not in test_packages:
        raise ValueError('platform')

    check_datasets_generated(max(sizes))
    test_packages[target_platform](arguments.executable)
