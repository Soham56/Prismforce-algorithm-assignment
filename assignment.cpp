#include <bits/stdc++.h>
using namespace std;

bool findCanAbhimanyuWin(int currentEnemy, int numberOfEnemies, vector<int> &enemyPowers, int initialPower, int currentPower, int noOfTimesCanRecharge, int isBoonAvailable, vector<vector<vector<vector<int>>>> &cachedPossibilityOfAbhimanyuVictory)
{
    // abhimanyu has passed all enemy circles successfully, so he has won
    if (currentEnemy > numberOfEnemies)
    {
        return true;
    }

    // checking is that wining possibility already processed before, with given values of currentEnemy, currentPower, noOfTimesCanRecharge, isBoonAvailable
    // in this way reducing the overhead of further duplicate recurrence tree
    if (cachedPossibilityOfAbhimanyuVictory[currentEnemy][currentPower][noOfTimesCanRecharge][isBoonAvailable] != -1)
    {
        return cachedPossibilityOfAbhimanyuVictory[currentEnemy][currentPower][noOfTimesCanRecharge][isBoonAvailable];
    }

    // if the current enemy power is more that his maximum power , then he must apply the boon to skip the battle otherwise he will be defeated
    if (enemyPowers[currentEnemy] > initialPower)
    {
        if (isBoonAvailable)
            return cachedPossibilityOfAbhimanyuVictory[currentEnemy][currentPower][noOfTimesCanRecharge][isBoonAvailable] = findCanAbhimanyuWin(currentEnemy + 1, numberOfEnemies, enemyPowers, initialPower, currentPower, noOfTimesCanRecharge, false, cachedPossibilityOfAbhimanyuVictory);
        return cachedPossibilityOfAbhimanyuVictory[currentEnemy][currentPower][noOfTimesCanRecharge][isBoonAvailable] = false;
    }

    bool canAbhimanyuWin = false;

    // if with the current power he can defeat the current enemy then there is a choice to defeat the enemy and process further and his current power will be decreased by the current enemy power ( refered 3rd rule )
    if (enemyPowers[currentEnemy] <= currentPower)
    {
        canAbhimanyuWin |= cachedPossibilityOfAbhimanyuVictory[currentEnemy][currentPower][noOfTimesCanRecharge][isBoonAvailable] = findCanAbhimanyuWin(currentEnemy + 1, numberOfEnemies, enemyPowers, initialPower, currentPower - enemyPowers[currentEnemy], noOfTimesCanRecharge, isBoonAvailable, cachedPossibilityOfAbhimanyuVictory);
    }

    // if the current enemy power is less than his maxmimum power but more than his current power , then there is a choice of either he can apply the boon or he can recharge his power with his initial maximum power
    if (noOfTimesCanRecharge)
        canAbhimanyuWin |= cachedPossibilityOfAbhimanyuVictory[currentEnemy][currentPower][noOfTimesCanRecharge][isBoonAvailable] = findCanAbhimanyuWin(currentEnemy + 1, numberOfEnemies, enemyPowers, initialPower, initialPower - enemyPowers[currentEnemy], noOfTimesCanRecharge - 1, isBoonAvailable, cachedPossibilityOfAbhimanyuVictory);

    if (isBoonAvailable)
        canAbhimanyuWin |= cachedPossibilityOfAbhimanyuVictory[currentEnemy][currentPower][noOfTimesCanRecharge][isBoonAvailable] = findCanAbhimanyuWin(currentEnemy + 1, numberOfEnemies, enemyPowers, initialPower, currentPower, noOfTimesCanRecharge, false, cachedPossibilityOfAbhimanyuVictory);

    return cachedPossibilityOfAbhimanyuVictory[currentEnemy][currentPower][noOfTimesCanRecharge][isBoonAvailable] = canAbhimanyuWin;
}

bool canAbhimanyuAbleToGetBackToPandavas()
{
    int n = 11, initialPower, noOfTimesCanRecharge;
    cin >> initialPower >> noOfTimesCanRecharge;
    vector<int> enemyPowers(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> enemyPowers[i];
    }

    /**
     * for enemy circle 3 and 7 , after killed they can regenerate again and attack with half power ( assumed floor division ), and attach from behind while combatting with enemy circle 4 and 8 respectively,
     * so abhimanyu has to fight total of enemyPower[4] + (enemyPower[3]/2) at circle 4
     * and enemyPower[8] + (enemyPower[7]/2) at circle 8

     * - refered 5th rule
     */
    enemyPowers[4] += (enemyPowers[3] / 2);

    enemyPowers[8] += (enemyPowers[7] / 2);

    // a 4-dimentional cache array, to store if the possibility of abhimanyu's victory , which reduce the duplicated recurrence tree
    vector<vector<vector<vector<int>>>> cachedPossibilityOfAbhimanyuVictoryOfAbhimanyuVictory(n + 2, vector<vector<vector<int>>>(initialPower + 2, vector<vector<int>>(noOfTimesCanRecharge + 2, vector<int>(2, -1))));

    return findCanAbhimanyuWin(1, n, enemyPowers, initialPower, initialPower, noOfTimesCanRecharge, true, cachedPossibilityOfAbhimanyuVictoryOfAbhimanyuVictory);
}

/************** Test-case Region **************/

int main()
{

    int test_case = 2;
    test_case++;

    while (test_case > 1)
    {

        test_case--;
        if (canAbhimanyuAbleToGetBackToPandavas())
        {
            cout << "Yes, Abhimanyu will be able to get back to Pandavas !\n";
        }
        else
        {
            cout << "No, Abhimanyu will not be able to get back to Pandavas !\n";
        }
    }

    return 0;
}
