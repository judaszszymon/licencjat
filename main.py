import random
import os.path
INT_MAX = 2147483647


def generate_yes_instance(tab_size, subset_size):
    tab = []
    max_size = 10000
    for i in range(tab_size):
        new_element = random.randrange(subset_size + 1, max_size, subset_size + 1)
        tab.append(new_element)

    indexes = random.sample(range(len(tab)), subset_size)
    s = 0
    for i in indexes:
        tab[i] += 1
        s += tab[i]
    return tab, s


def generate_no_instance(tab_size, near_subset_sum):
    tab = []
    max_size = 10000
    for i in range(tab_size):
        new_element = random.randrange(2, max_size, 2)
        tab.append(new_element)

    s = 0
    indexes = random.sample(range(len(tab)), near_subset_sum)
    for i in indexes:
        s += tab[i]
    return tab, s+1


def write_test_to_file(tab, s, filename):
    if os.path.exists(filename):
        os.remove(filename)

    with open(filename, 'w') as f:
        f.write(str(len(tab)) + ' ' + str(s) + '\n')
        for number in tab:
            f.write(str(number) + ' ')


def generate_tests(start_tab_size, end_tab_size, amount_of_same_type_test, directory):
    if not os.path.exists(directory):
        os.makedirs(directory)

    for tab_size in range(start_tab_size, end_tab_size):
        for i in range(amount_of_same_type_test):
            subset_size = tab_size * (i + 1) / (amount_of_same_type_test + 1)
            tab, s = generate_no_instance(tab_size, subset_size)
            write_test_to_file(tab, s, os.path.join(directory, 'no_{}_{}.txt'.format(tab_size, subset_size)))
            tab, s = generate_yes_instance(tab_size, subset_size)
            write_test_to_file(tab, s, os.path.join(directory, 'yes_{}_{}.txt'.format(tab_size, subset_size)))


def main():
    generate_tests(6, 48, 4, 'tests')

if __name__ == '__main__':
    main()

