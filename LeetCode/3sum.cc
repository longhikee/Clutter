#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
*
Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:

The solution set must not contain duplicate triplets.

Example:

Given array nums = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
*/


vector<vector<int> > threeSum(vector<int>& nums) {
        size_t i = 0;
	size_t j = 0;
	size_t k = 0;
        size_t size = nums.size();
        int sum = 0;

        vector<vector<int>> answer;
        for (; i < size ; i++)
        {
	//as nums is sorted firstly, no need apply two loops
            for (j = size - 1; j > i; j--)
            {
                sum = -(nums[i] + nums[j]);
                for (k = i + 1; k < j; k++)
                {
                    if (nums[k] == sum)
                    {
                        cout << i << " " << k << " " << j << endl;
                        cout << "i k j value: " << nums[i] << " " << nums[k] << " " << nums[j] << endl;
                        answer.push_back({nums[i], nums[k], nums[j]});
                    }
		    while(nums[k] == nums[k+1] && k < j)
		      k++;
                }
		while((j-1 > i) && (nums[j] == nums[j-1]))
		  j--;
                
            }
            while(nums[i] == nums[i+1] && i < size)
	      i++;
        }
        return answer;
}

int main()
{
   vector<int> nums{-4,-1,-1,-1,-1,0,1,1,1,1,1,1,1,2,2,2,2};
//   vector<int> nums{0,0,0,0,0,0,0};

   cout << "[ ";
   for (auto e : nums)
      cout << e << " ";
   cout << "]" << endl;
   cout << endl << endl;
   sort(nums.begin(),nums.end());
   vector<vector<int> > answer = threeSum(nums);

   cout << endl << endl << endl;
   for (auto v : answer)
   {
       cout << "[ ";
       for (auto e : v)
       {
         cout << e << " ";

       }
       cout << "]";
       cout << endl;
   }

}
