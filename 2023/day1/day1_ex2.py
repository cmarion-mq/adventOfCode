def main():
    try:
        f = open('day1_input.txt')
        sum = 0
        ldigits = {'one': 1, 'two': 2, 'three': 3, 'four': 4, 
        'five': 5, 'six': 6, 'seven': 7, 'eight': 8, 'nine': 9}
        lines = f.readlines()
        for line in lines:
            num = []
            for i in range(0,len(line)):
                if line[i].isdigit():
                    num.append(int(line[i]))
                else:
                    for key, value in ldigits.items():
                        if  line[i:].find(key) == 0:
                            num.append(value)
                            i += len(key) - 2 #limite le passage dans le for, les chiffres n'ont pas plus d'une lettre commune entre début et fin
                            break
            if len(num) == 1:
                sum += num[0] * 10 + num[0]
            else:
                sum += num[0] * 10 + num[len(num) - 1]
        print(sum)
        f.close()
    except AssertionError as e:
        print(AssertionError.__name__, e, sep=": ")

if __name__ == "__main__":
    main()