from cs50 import get_int
import sys

print("Number: ", end="")   
num = get_int("")
str_num = str(num)

length = len(str_num)


evensum = 0
oddsum = 0

if (length % 2 == 0):
    for i in range(length):
        if (i % 2 == 0):
            double = 2 * int(str_num[i])
            if double > 9:
                strdouble = str(double)
                double = int(strdouble[0]) + int(strdouble[1])
            oddsum = oddsum + double
        else:
            evensum = evensum + int(str_num[i])
else:
    for i in range(length):
        if (i % 2 == 0):
            evensum = evensum + int(str_num[i])
        else:
            double = 2 * int(str_num[i])
            if double > 9:
                strdouble = str(double)
                double = int(strdouble[0]) + int(strdouble[1])
            oddsum = oddsum + double

sum = evensum + oddsum

if sum % 10 != 0:
    print("INVALID")
    sys.exit(1)

if length == 15 and str_num[0] == '3':
    if str_num[1] == '4' or str_num[1] == '7':
        print("AMEX")
    else:
        print("INVALID")
elif length == 16 and str_num[0] == '5' and (str_num[1] == '1' or str_num[1] == '2' or str_num[1] == '3' or str_num[1] == '4' or str_num[1] == '5'):
    print("MASTERCARD")
elif (length == 13 or length == 16) and str_num[0] == '4':
    print("VISA")
else:
    print("INVALID!")