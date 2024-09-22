#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
    for ( int i =0 ; i < numsSize-1 ; i ++ )
    {
        for (int j = i+1 ; j< numsSize ; j++)
        {
            if (nums[i]+ nums [j]== target)
            {
                int answer[] = {i,j};
                return answer
            }

        }

    }
}


int main(void)
{
    int nums[4] = {2,7,11,15};
    int target = 9;
    int numSize = 4;
    int returnSize = 2;
    int* x = twoSum(nums, numsSize, target, returnSize);

    for (int i = 0; i < returnSize; i++)
    {
        printf("%i",x[i]);
    }
}
