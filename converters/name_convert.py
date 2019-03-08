import re

def convert_name(string):
    return re.sub(r'([a-z])([A-Z])', r'\1_\2', string).lower()

if __name__ == '__main__':
    print(convert_name(input()))
