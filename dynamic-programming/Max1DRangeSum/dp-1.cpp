/* As Manuel wants to get rich fast and without too much work, he decided to make a career in gambling.
Initially, he plans to study the gains and losses of players, so that, he can identify patterns of consecutive
wins and elaborate a win-win strategy. But Manuel, as smart as he thinks he is, does not know how to
program computers. So he hired you to write programs that will assist him in elaborating his strategy.
Your first task is to write a program that identifies the maximum possible gain out of a sequence of
bets. A bet is an amount of money and is either winning (and this is recorded as a positive value), or
losing (and this is recorded as a negative value).

Input
The input set consists of a positive number N ≤ 10000 , that gives the length of the sequence, followed
by N integers. Each bet is an integer greater than 0 and less than 1000.
The input is terminated with N = 0.
Output
For each given input set, the output will echo a line with the corresponding solution. If the sequence
shows no possibility to win money, then the output is the message ‘Losing streak.’

Sample Input
5
12 -4
-10 4
9
3
-2 -1 -2
0

Sample Output
The maximum winning streak is 13.
Losing streak. */

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;

    while (true) {
        cin >> N;

        if (N == 0) {
            break; // Terminate when N is 0
        }

        vector<int> bets(N);
        for (int i = 0; i < N; ++i) {
            cin >> bets[i];
        }

        int max_sum = bets[0];
        int current_sum = bets[0];

        for (int i = 1; i < N; ++i) {
            current_sum = max(bets[i], current_sum + bets[i]);
            max_sum = max(max_sum, current_sum);
        }

        if (max_sum > 0) {
            cout << "The maximum winning streak is " << max_sum << "." << endl;
        } else {
            cout << "Losing streak." << endl;
        }
    }

    return 0;
}
