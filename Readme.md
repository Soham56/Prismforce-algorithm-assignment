# Prismforce Algorithm Assignment

## Solution Approach

-   For a detailed explanation of the solution approach and its time complexity, please refer to the [reference link](https://github.com/Soham56/Prismforce-algorithm-assignment/blob/main/Solution%20Approach.pdf).

## Input Parameters

-   **initialPower**: The initial power of Abhimanyu.
-   **number of times can recharge**: The number of times Abhimanyu can recharge his power.
-   **array of enemy powers**: An array representing the power of each enemy.

## Test Case

### Input

```plaintext
initial power (p) = 10
number of times can recharge (b) = 1
array of enemy powers (k) = [3, 1, 9, 2, 1, 1, 1, 1, 2, 1, 1]
```

### Output

```plaintext
Yes, Abhimanyu will be able to get back to Pandavas!
```

## Explanation

In this test case, Abhimanyu starts with an initial power of 10. At the 3rd enemy, Abhimanyu's power will drop to 6, giving him a choice to either skip the battle using the boon or recharge his power back to 10.

-   **Choosing to Recharge:**

    1. Abhimanyu recharges his power to 10, defeats the 3rd enemy, and proceeds to the 4th enemy with his power reduced to 1.
    2. Since he defeated the 3rd enemy, it regenerates to half of its power and attacks from behind, while the 4th enemy attacks from the front. The combined power of the 4th enemy and half of the 3rd enemy’s power would engage Abhimanyu. However, as the boon is still available, he uses it to skip the 4th enemy and proceeds to the 5th.
    3. At the 5th enemy, with his power being 1 (equal to the enemy’s power), he defeats it and moves forward with a power level of 0.
    4. Finally, at the 6th enemy, without any remaining boon or recharge options, Abhimanyu is defeated.

-   **Choosing to Use the Boon:**
    1. Abhimanyu skips the 3rd enemy and confronts the 4th enemy with his power still at 6.
    2. Since he skipped the 3rd enemy, it does not regenerate and attack from behind. Abhimanyu defeats the 4th enemy and proceeds further with his power reduced to 5.
    3. This approach continues similarly through the 9th enemy, and by the time he reaches the 10th enemy, his power is reduced to 0.
    4. At the 10th enemy, since he still has the option to recharge, Abhimanyu replenishes his power to 10 and defeats the remaining enemies, ensuring his victory.
