import glob
import re
import subprocess


def main():
    inputs = glob.glob('inputs/in_*.txt')
    for input in inputs:
        suffix = re.findall(r'in_(.*\.txt)', input)[0]
        exp = f'expectations/exp_{suffix}'
        output = f'outputs/out_{suffix}'
        subprocess.run(['cmake-build-debug/shell.exe', input, output])
        if (open(exp).read() != open(output).read()):
            print(f'Diff in {suffix}')


if __name__ == '__main__':
    main()