import sys

def main():

    if len(sys.argv) != 2 or not sys.argv[1].isdigit() or int(sys.argv[1]) < 0:
        sys.exit("Usage: python caesar.py k")

    k = int(sys.argv[1]) % 26
    cipher = ""
    text = input("plaintext: ")
    for ch in text:
        if ch.isalpha():
            if ch.isupper():
                cipher += chr((ord(ch)-ord("A")+k)%26+ord("A"))
            else:
                cipher += chr((ord(ch)-ord("a")+k)%26+ord("a"))
        else:
            cipher += ch
    print("ciphertext: " + cipher)


main()
