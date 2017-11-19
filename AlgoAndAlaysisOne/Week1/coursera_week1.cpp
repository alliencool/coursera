#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

long long merge_and_count(vector<int>& nums)
{
    if (nums.size() <= 1)
        return 0;
    int div_size = nums.size()/2;
    vector<int> nums1, nums2;
    for (int i=0;i<nums.size();i++)
        if (i<div_size)
            nums1.push_back(nums[i]);
        else
            nums2.push_back(nums[i]);
    long long rev1 = merge_and_count(nums1);
    long long rev2 = merge_and_count(nums2);

    long long rev3 = 0;
    int i=0, j=0,k=0;
    while(i<nums1.size() && j < nums2.size())
    {
        if (nums1[i] <= nums2[j])
        {
            nums[k] = nums1[i];
            i++;
        }
        else
        {
            nums[k] = nums2[j];
            rev3 += nums1.size() - i;
            j++;
        }
        k++;
    }
    while(i < nums1.size())
        nums[k++] = nums1[i++];
    while(j < nums2.size())
        nums[k++] = nums2[j++];
    return rev1 + rev2 + rev3;
}

int main(int argc, char** argv)
{
    ifstream f;
    f.open(argv[1]);
    vector<int> nums;
    string s;
    while (getline(f,s))
    {
        nums.push_back(stoi(s));
        cout<<nums[nums.size()-1]<<"\n";
    }
    f.close();
    cout<<"Answer is "<<merge_and_count(nums)<<"\n";
    return 0;
}
