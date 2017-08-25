def convert_name(string):
    j = 0
    words = []
    for i, c in enumerate(string):
        if i != 0 and c.isupper():
            words.append(string[j:i])
            j = i
    words.append(string[j:])
    return '_'.join([s.lower() for s in words])

if __name__ == '__main__':
    print(convert_name(input()))
