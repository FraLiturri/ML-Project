import sys
import python.info as info


def main():

    if len(sys.argv) == 1:  # No parameter passed;
        for q in info.questions:
            q = (
                "\n " + f"{info.questions.index(q)+1}. " + q
            )  # formatting strings in a certain way;
            questions_list += q
        print(
            f"\nHi welcome! I'll be your guide during this journey; try asking these questions: {questions_list}\n"
        )
        print(
            f"Note: ask question typing its number after\033[94m python info.py \033[0min the terminal. If you want to get general info type {info.StringPainter('blue', '0')}. \n"
        )

    else:  # Passed parameter;
        parametro = int(sys.argv[1])
        if parametro == 0:
            print(f"\n{info.guide}\n")
        elif parametro <= len(info.questions):
            print("\n" + info.answers[parametro - 1] + "\n")
        else:
            print(f"\nNumber {parametro} does not correspond to any question.\n")


if __name__ == "__main__":
    main()
