#!usr/bin/env python3


import argparse
import random
import string
import os


STRING_LENGTH = 30


def write_file(number, number_of_strings,directory_path):

    with open(os.path.join(directory_path, 'input{}.txt'.format(number)), 'w') as file:
        for __ in range(number_of_strings):
            file.write(''.join(
                random.choice(string.ascii_uppercase + string.digits) for _ in range(STRING_LENGTH)
            ))
            file.write('\n')


if __name__ == '__main__':
    arguments_parser = argparse.ArgumentParser()
    arguments_parser.add_argument('--count', required=True)
    arguments_parser.add_argument('--length', required=True)
    arguments_parser.add_argument('ex_directory', nargs='*')

    arguments = arguments_parser.parse_args()
    file_count, number_of_strings = arguments.count, arguments.length
    out_dir = arguments.ex_directory[0] if arguments.ex_directory else '.'

    for i in range(int(file_count)):
        write_file(int(i), int(number_of_strings), out_dir)
        print("File 'input{}.txt' generated ".format(i))
