def main():
    try:
        f = open('day1_input.txt')
        sum = 0
        lines = f.readlines()
        for line in lines:
            num = [int(x) for x in [*line] if x.isdigit()]
            # num = []
            # for x in [*line]:
            #     if x.isdigit():
            #         num.append(int(x))
            # print(num)
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