import sys


def main():
    if len(sys.argv) != 2 or not sys.argv[1].isalpha():
        sys.exit("Usage: python caesar.py k")

    k = [k - ord('a') for k in map(ord, sys.argv[1].lower())]
    cipher = ""
    text = input("plaintext: ")
    i = 0
    for ch in text:
        if ch.isalpha():
            if ch.isupper():
                cipher += chr((ord(ch) - ord("A") + k[i % 3]) % 26 + ord("A"))
            else:
                cipher += chr((ord(ch) - ord("a") + k[i % 3]) % 26 + ord("a"))
            i += 1
        else:
            cipher += ch
    print("ciphertext: " + cipher)


main()
