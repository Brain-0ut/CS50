from sys import argv


def main():

    if len(argv) != 2:
        exit("Usage: python bleep.py dictionary")
    with open(argv[1], 'r') as file:
        ban = file.read().split()
    text = input("What message would you like to censor? ")
    censor_txt = ' '.join([word if word.lower() not in ban else "*" * len(word) for word in text.split()])
    print(censor_txt)


if __name__ == "__main__":
    main()
