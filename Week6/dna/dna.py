import csv
import sys


def main():

    #  Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")
    if not (".csv" in sys.argv[1]):
        sys.exit("Second parameter must be a .csv file with DB of people")
    if not (".txt" in sys.argv[2]):
        sys.exit("Third parameter must be a .txt file with Sequence of DNA")

    #  Read database file into a variable
    db = []
    with open(sys.argv[1], 'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            db.append(row)
    all_str = [x for x in db[0].keys() if not (x == 'name')]

    #  Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as file:
        sequence = file.read().rstrip()

    #  Find longest match of each STR in DNA sequence
    str_counts = {one_str: 0 for one_str in all_str}
    for one_str in all_str:
        str_counts[one_str] = str(longest_match(sequence, one_str))

    #  Check database for matching profiles
    for people in db:
        name = people.pop('name')
        if people == str_counts:
            print(name)
            exit()
    print('No match')
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in sequence, return longest run found
    return longest_run


main()
