def main():

    while True:
        try:
            change = float(input("Change owed: "))
            if change >= 0:
                break
            else:
                print("Please put a change owed in format '0.00'")  # if change owed less than 0
        except ValueError:
            # if input not a float number
            print("That's not a float! Please put a change owed in format '0.00' without any symbols like $")
    change = int(change * 100)
    coins = [25, 10, 5, 1]
    count = 0  # count of coins
    for coin in coins:
        count += change // coin
        change -= coin * (change // coin)
    print(count)


if __name__ == "__main__":
    main()
