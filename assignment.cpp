#include <bits/stdc++.h>
using namespace std;

bool findCanAbhimanyuWin(int currentEnemy, int currentPower, int noOfTimesCanRecharge, bool isBoonAvailable, bool isThirdEnemySkipped, bool isSeventhEnemySkipped, int numberOfEnemies, int initialPower, vector<int> &enemyPowers, vector<vector<vector<vector<vector<vector<int>>>>>> &cachedPossibilityOfAbhimanyuVictory)
{
    // abhimanyu has passed all enemy circles successfully, so he has won
    if (currentEnemy > numberOfEnemies)
    {
        return true;
    }

    // Checking if the winning possibility has already been processed with the given values of currentEnemy, currentPower, noOfTimesCanRecharge, isBoonAvailable, isThirdEnemySkipped, isSeventhEnemySkipped.
    // This helps reduce the overhead of further duplicate recurrence trees.
    if (cachedPossibilityOfAbhimanyuVictory[currentEnemy][currentPower][noOfTimesCanRecharge][isBoonAvailable][isThirdEnemySkipped][isSeventhEnemySkipped] != -1)
    {
        return cachedPossibilityOfAbhimanyuVictory[currentEnemy][currentPower][noOfTimesCanRecharge][isBoonAvailable][isThirdEnemySkipped][isSeventhEnemySkipped];
    }

    bool canAbhimanyuWin = false;

    // If the current enemy's power is greater than his maximum power, he must apply the boon to skip the battle; otherwise, he will be defeated.
    if (enemyPowers[currentEnemy] > initialPower)
    {
        if (isBoonAvailable)
            canAbhimanyuWin |= findCanAbhimanyuWin(currentEnemy + 1, currentPower, noOfTimesCanRecharge, false, currentEnemy == 3, currentEnemy == 7, numberOfEnemies, initialPower, enemyPowers, cachedPossibilityOfAbhimanyuVictory);
        return cachedPossibilityOfAbhimanyuVictory[currentEnemy][currentPower][noOfTimesCanRecharge][isBoonAvailable][isThirdEnemySkipped][isSeventhEnemySkipped] = canAbhimanyuWin;
    }

    // According to rule no. 5, if the 3rd and 7th enemies are defeated, they can regenerate their power to half of their initial power (using floor division) and attack from behind.
    // Therefore, the power of the 4th and 8th enemies is increased by half of the power of the 3rd and 7th, respectively.
    // *Assumed that if they are skipped, they will no longer attack from behind.

    if (currentEnemy == 4 && !isThirdEnemySkipped)
        enemyPowers[currentEnemy] += (enemyPowers[currentEnemy - 1] / 2);

    if (currentEnemy == 8 && !isSeventhEnemySkipped)
        enemyPowers[currentEnemy] += (enemyPowers[currentEnemy - 1] / 2);

    // If, with the current power, he can defeat the current enemy, there is a choice to defeat the enemy and proceed further.
    // His current power will be decreased by the current enemy's power (as per rule no. 3).
    if (enemyPowers[currentEnemy] <= currentPower)
    {
        canAbhimanyuWin |= findCanAbhimanyuWin(currentEnemy + 1, currentPower - enemyPowers[currentEnemy], noOfTimesCanRecharge, isBoonAvailable, isThirdEnemySkipped, isSeventhEnemySkipped, numberOfEnemies, initialPower, enemyPowers, cachedPossibilityOfAbhimanyuVictory);
    }

    // If the current enemy's power is less than his maximum power but greater than his current power, then there is a choice: he can either apply the boon or recharge his power to his initial maximum power.
    if (noOfTimesCanRecharge && initialPower >= enemyPowers[currentEnemy])
    {
        canAbhimanyuWin |= findCanAbhimanyuWin(currentEnemy + 1, initialPower - enemyPowers[currentEnemy], noOfTimesCanRecharge - 1, isBoonAvailable, isThirdEnemySkipped, isSeventhEnemySkipped, numberOfEnemies, initialPower, enemyPowers, cachedPossibilityOfAbhimanyuVictory);
    }

    if (isBoonAvailable)
    {
        canAbhimanyuWin |= findCanAbhimanyuWin(currentEnemy + 1, currentPower, noOfTimesCanRecharge, false, currentEnemy == 3, currentEnemy == 7, numberOfEnemies, initialPower, enemyPowers, cachedPossibilityOfAbhimanyuVictory);
    }

    // Revert the changes applied to the 4th and 8th enemies after processing with the current enemy is complete.
    if (currentEnemy == 4 && !isThirdEnemySkipped)
        enemyPowers[currentEnemy] -= (enemyPowers[currentEnemy - 1] / 2);

    if (currentEnemy == 8 && !isSeventhEnemySkipped)
        enemyPowers[currentEnemy] -= (enemyPowers[currentEnemy - 1] / 2);

    return cachedPossibilityOfAbhimanyuVictory[currentEnemy][currentPower][noOfTimesCanRecharge][isBoonAvailable][isThirdEnemySkipped][isSeventhEnemySkipped] = canAbhimanyuWin;
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

    // A 6-dimensional cache array to store the possibility of Abhimanyu's victory, which reduces the duplicated recurrence tree.
    vector<vector<vector<vector<vector<vector<int>>>>>> cachedPossibilityOfAbhimanyuVictory(
        n + 2, vector<vector<vector<vector<vector<int>>>>>(
                   initialPower + 2, vector<vector<vector<vector<int>>>>(
                                         noOfTimesCanRecharge + 2, vector<vector<vector<int>>>(
                                                                       2, vector<vector<int>>(
                                                                              2, vector<int>(2, -1))))));

    return findCanAbhimanyuWin(1, initialPower, noOfTimesCanRecharge, true, false, false, n, initialPower, enemyPowers, cachedPossibilityOfAbhimanyuVictory);
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
