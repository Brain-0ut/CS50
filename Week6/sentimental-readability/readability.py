def main():
    text = input("Text: ")  # Input text
    text = text.split()  # split to words
    sentences_count = 0  # count for sentences
    words_count = len(text)  # count for words
    char_count = 0  # counted each char for all words
    for word in text:
        if '.' in word or '!' in word or '?' in word:
            sentences_count += 1
        if word.isalpha():
            char_count += len(word)
        else:
            char_count += len(word) - 1
    print(char_count, words_count, sentences_count)
    l = char_count / words_count * 100
    s = sentences_count / words_count * 100
    grade = l * 0.0588 - s * 0.296 - 15.8
    if grade < 1.0:
        print("Before Grade 1")
    elif grade >= 16.0:
        print("Grade 16+")
    else:
        print(f"Grade {round(grade)}")

    return True


if __name__ == "__main__":
    main()
