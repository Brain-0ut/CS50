def main():
    while True:
        card = input("Number: ")
        if card.isdigit():
            break
        else:
            print("Please put a card number (only digits)")  # if card contain not only digits
    if 13 < len(card) < 16 or len(card) != 14:
        if is_visa(card):
            print("VISA")
            exit()
        elif is_master(card):
            print("MASTERCARD")
            exit()
        elif is_amex(card):
            print("AMEX")
            exit()
    print("INVALID")


def is_visa(card):  # Check if is VISA card
    return check(card) if int(card[:1]) == 4 else False


def is_master(card):  # Check if is MASTERCARD card
    return check(card) if 50 < int(card[:2]) < 56 else False


def is_amex(card):  # Check if is AMEX card
    return check(card) if int(card[:2]) == 34 or int(card[:2]) == 37 else False


def check(card):  # Check if the checksum of card is right
    check_sum = sum(int(item) for item in card[::-2])
    for i in card[-2::-2]:
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
