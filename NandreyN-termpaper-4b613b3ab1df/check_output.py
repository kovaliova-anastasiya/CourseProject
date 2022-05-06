#!usr/bin/env python3

import argparse

def check_file(file_name):
    with open(file_name, 'r') as file:
        lines = list(file.readlines())
        return all([
            lines[i] <= lines[i + 1] for i, _ in enumerate(lines[:-1])
        ])


if __name__ == '__main__':
    arguments_parser = argparse.ArgumentParser()
    arguments_parser.add_argument('file')
    arguments = arguments_parser.parse_args()
    print(check_file(arguments.file))
