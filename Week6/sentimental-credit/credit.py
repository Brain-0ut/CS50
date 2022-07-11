def main():
    while True:
        card = input("Number: ")
        if card.isdigit():
            break
        else:
            print("Please put a card number (only digits)")  # if card contain not only digits
    if 13 < len(card) < 16 or len(card) != 14:
        if is_visa(card):  # Check if is VISA card
            print("VISA")
            exit()
        elif is_master(card):  # Check if is MASTERCARD card
            print("MASTERCARD")
            exit()
        elif is_amex(card):  # Check if is AMEX card
            print("AMEX")
            exit()
    print("INVALID")


def is_visa(card):  # Check if is VISA card
    if int(card[:1]) == 4:
        return check(card)
    return False


def is_master(card):  # Check if is MASTERCARD card
    if 50 < int(card[:2]) < 56:
        return check(card)
    return False


def is_amex(card):  # Check if is AMEX card
    if int(card[:2]) == 34 or int(card[:2]) == 37:
        return check(card)
    return False


def check(card):  # Check if the checksum of card is right
    check_sum = sum(int(item) for item in list(card[::-2]))
    for i in list(card[-2::-2]):
        i = int(i)
        if i * 2 >= 10:
            check_sum += (i * 2 // 10) + (i * 2 % 10)
        else:
            check_sum += i * 2
    if not check_sum % 10:
        return True
    return False


if __name__ == "__main__":
    main()
