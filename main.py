import random
import os
import sys


def generate_data(input_fn: str):
    with open(input_fn, 'w') as f:
        for i in range(60000):
            float_ = random.random()
            int_ = random.randrange(100, 998)
            sign_ = random.choice([-1, 1])
            res = sign_ * (int_ + float_)
            if i % 3 == 0:
                res = format(res, '.8E')

            f.write(str(res) + "\n")


def experiment():
    EPSILON = 1e-16
    NUM_METHODS = 12
    PROGAM_NAME = "dtos_time" + (".exe" if os.name == 'nt' else "")
    if not os.path.exists(f"./build/{PROGAM_NAME}"):
        raise ValueError(
            "C++ executable is not found in current directory. You must run this python script from the directory with C++ executable")
    TIME_RES_FN = ".temp"   # Should be the same as TIME_RES_FN in C++ program

    # Verify that file for time results exists, so that C++ program can write into it
    fp = open(TIME_RES_FN, 'w')
    fp.close()

    cycles = int(sys.argv[1])
    input_fn = sys.argv[2]
    output_fn = sys.argv[3]

    generate_data(input_fn)

    tot_cnt = []
    average = []
    isCorrect = True
    for i in range(1, NUM_METHODS+1):
        min_time = float('inf')
        method_tot_cnt = [0 for _ in range(cycles)]
        method_average = [0 for _ in range(cycles)]
        for j in range(cycles):
            os.system(
                f"./build/{PROGAM_NAME} {str(i)} {input_fn} {output_fn} {TIME_RES_FN}")
            try:
                with open(TIME_RES_FN, 'r') as f:
                    min_time = min(min_time, float(f.readline()))
            except ValueError as err:
                raise ValueError(
                    f"{err}\nC++ program haven't generated text file with results as expected. Was it even executed?")

            with open(output_fn, 'r') as f:
                method_tot_cnt.append(int(f.readline()))
                method_average.append(float(f.readline()))

        if (min(method_average) == max(method_average)) or \
           (min(method_tot_cnt) - max(method_tot_cnt) <= EPSILON):
            result_exl = f"The results of this method are always the same with eps = {EPSILON}"
        else:
            result_exl = f"The results of this method are NOT the same!!"

        with open(output_fn, 'r') as f:
            tot_cnt.append(int(f.readline()))
            average.append(float(f.readline()))
        print(f'Method: {i}, min time: {min_time}. {result_exl}\n')

    pivot_tot_res = tot_cnt[0]
    pivot_avr_res = average[0]
    for i in range(1, len(tot_cnt)):
        if abs(pivot_tot_res - tot_cnt[i]) > EPSILON or pivot_avr_res != average[i]:
            isCorrect = False

    # if isCorrect:
        # print(f"All results are the same with epsilon {EPSILON}")
    # else:
        # print(f"Results do NOT coincide!!!")

    os.remove(TIME_RES_FN)


if __name__ == "__main__":
    cmd = f"cmake -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Release -H./ -B./build -G \"{'Visual Studio 15 2017' if os.name == 'nt' else 'Unix Makefiles'}\" && cmake --build ./build --config Release --target all"
    os.system(cmd)
    if len(sys.argv) != 4:
        print("Wrong number of arguments")
    else:
        experiment()
