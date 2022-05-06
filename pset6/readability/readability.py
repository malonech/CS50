from cs50 import get_string

print("Text: ")
text = get_string("")

letters = 0
words = 0
sentences = 0

for i in range(len(text)):
    if (text[i] >= 'a' and text[i] <= 'z') or (text[i] >= 'A' and text[i] <= 'Z'):
        letters += 1
    if  text[i] == ' ':
        words += 1
    if (text[i] == '.' or text[i] == '!' or text[i] == '?'):
        sentences += 1

words += 1

L = (letters / words) * 100
S = (sentences / words) * 100

grade = round(0.0588 * L - 0.296 * S - 15.8)

if grade > 16:
    print("Grade 16+")
elif grade < 1:
    print("Before Grade 1")
else:    
    print(f"Grade {grade}")
