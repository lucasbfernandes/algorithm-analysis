import numpy
import sys

sys.setrecursionlimit(40000)
DP_MEMO = numpy.full((205, 3101, 3101), -1, dtype=numpy.int8)


def get_random_input():
    input_integers = numpy.random.random_integers(1, 15, 201)
    numpy.random.shuffle(input_integers)
    return input_integers


def get_text_input():
    input_integers = []
    for line in sys.stdin:
        line_split = str.split(line)
        input_integers += map(int, line_split)
    return numpy.array(input_integers)


def get_answer_string(is_solvable):
    if is_solvable == 1:
        return "Yes"
    elif is_solvable == 0:
        return "No"
    else:
        return "Error"


def get_initial_answer():
    return [numpy.array([], dtype=numpy.int8), numpy.array([], dtype=numpy.int8), numpy.array([], dtype=numpy.int8)]


def find_answer(i, bucket1_sum, bucket2_sum, p_sum, in_array, answer):
    if i == in_array.size:
        return answer

    elif bucket1_sum + in_array[i] <= p_sum and DP_MEMO.item((i + 1, bucket1_sum + in_array[i], bucket2_sum)) == 1:
        answer[0] = numpy.insert(answer[0], 0, in_array[i], axis=0)
        return find_answer(i + 1, bucket1_sum + in_array[i], bucket2_sum, p_sum, in_array, answer)

    elif bucket2_sum + in_array[i] <= p_sum and DP_MEMO.item((i + 1, bucket1_sum, bucket2_sum + in_array[i])) == 1:
        answer[1] = numpy.insert(answer[1], 0, in_array[i], axis=0)
        return find_answer(i + 1, bucket1_sum, bucket2_sum + in_array[i], p_sum, in_array, answer)

    else:
        answer[2] = numpy.insert(answer[2], 0, in_array[i], axis=0)
        return find_answer(i + 1, bucket1_sum, bucket2_sum, p_sum, in_array, answer)


def solve_it(p_sum, in_array):
    DP_MEMO.itemset((in_array.size, p_sum, p_sum), 1)
    for i in range(in_array.size - 1, -1, -1):
        for j in range(p_sum, -1, -1):
            for k in range(p_sum, -1, -1):
                if j + in_array[i] <= p_sum:
                    if k + in_array[i] <= p_sum:
                        is_solvable = (
                            DP_MEMO.item((i + 1, j + in_array[i], k)) or
                            DP_MEMO.item((i + 1, j, k + in_array[i])) or
                            DP_MEMO.item((i + 1, j, k))
                        )
                        DP_MEMO.itemset((i, j, k), is_solvable)
                    else:
                        is_solvable = (
                            DP_MEMO.item((i + 1, j + in_array[i], k)) or
                            DP_MEMO.item((i + 1, j, k))
                        )
                        DP_MEMO.itemset((i, j, k), is_solvable)
                else:
                    if k + in_array[i] <= p_sum:
                        is_solvable = (
                            DP_MEMO.item((i + 1, j, k + in_array[i])) or
                            DP_MEMO.item((i + 1, j, k))
                        )
                        DP_MEMO.itemset((i, j, k), is_solvable)
                    else:
                        is_solvable = (
                            DP_MEMO.item((i + 1, j, k))
                        )
                        DP_MEMO.itemset((i, j, k), is_solvable)
    return DP_MEMO.item((0, 0, 0))


def main():
    # input_integers = get_text_input()
    input_integers = get_random_input()

    total_sum = numpy.sum(input_integers)
    p_sum = total_sum / 3

    if total_sum % 3 != 0:
        print("Total sum is not divisible by 3")
    else:
        print("Total sum: {sum}\n".format(sum=total_sum))
        print("3-partition sum: {sum}\n".format(sum=p_sum))
        print("Input array: {array}\n".format(array=input_integers))

        is_solvable = solve_it(p_sum, input_integers)
        answer = find_answer(0, 0, 0, p_sum, input_integers, get_initial_answer())

        print("Solvable: {answer}\n".format(answer=get_answer_string(is_solvable)))
        print("Bucket #1: {bucket}\n".format(bucket=answer[0]))
        print("Bucket #2: {bucket}\n".format(bucket=answer[1]))
        print("Bucket #3: {bucket}\n".format(bucket=answer[2]))


main()
