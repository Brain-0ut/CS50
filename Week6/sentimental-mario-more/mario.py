def main():

    while True:
        try:
            height = int(input("Height: "))
            if 0 < height < 9:
                break
            else:
                print("Please put a number between 0 and 8.")  # if height less than 1 or height more than 8
        except ValueError:
            print("That's not an integer! Please put a number between 0 and 8.")  # if input not number

    for i, j in zip(range(height), reversed(range(height))):
        print(" "*j + "#"*(i+1) + "  " + "#"*(i+1))


if __name__ == "__main__":
    main()