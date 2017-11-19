#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int min(int a,int b)
{
    return (a<b?a:b);
}

int max(int a,int b)
{
    return (a>b?a:b);
}

void qsort_first(vector<int>& nums, int l , int r, long long& sum)
{
    if (r <= l)
    {
        return;
    }
    int tmp;
    int p = nums[l];
    int i = l + 1;
    for (int j=l+1;j<=r;j++)
    {
        if (nums[j] < p)
        {
            tmp = nums[i];
            nums[i] = nums[j];
            nums[j] = tmp;
            i++;
        }
    }
    tmp = nums[l];
    nums[l] = nums[i-1];
    nums[i-1] = tmp;
    qsort_first(nums,l,i-2, sum);
    qsort_first(nums,i,r,sum);
    sum += i-2 - l + 1 + r - i + 1;
}

void qsort_last(vector<int>& nums, int l , int r, long long& sum)
{
    if (r <= l)
    {
        return;
    }
    int tmp;
    tmp = nums[r];
    nums[r] = nums[l];
    nums[l] = tmp;
    int p = nums[l];
    int i = l + 1;
    for (int j=l+1;j<=r;j++)
    {
        if (nums[j] < p)
        {
            tmp = nums[i];
            nums[i] = nums[j];
            nums[j] = tmp;
            i++;
        }
    }
    tmp = nums[l];
    nums[l] = nums[i-1];
    nums[i-1] = tmp;
    qsort_last(nums,l,i-2, sum);
    qsort_last(nums,i,r,sum);
    sum += i-2 - l + 1 + r - i + 1;
}


void qsort_med(vector<int>& nums, int l , int r, long long& sum)
{
    if (r <= l)
    {
        return;
    }
    int tmp;
    int mid = l + ((r-l+1)/2 - (((r-l+1))%2==0?1:0));
    int mn = min(min(nums[l],nums[mid]),nums[r]); 
    int mx = max(max(nums[l],nums[mid]),nums[r]);
    int mid_index = l;
    if(nums[l] != mn && nums[l] != mx)
        mid_index = l;
    else if(nums[mid] != mn && nums[mid] != mx)
        mid_index = mid;
    else if(nums[r] != mn && nums[r] != mx)
        mid_index = r;

    tmp = nums[l];
    nums[l] = nums[mid_index];
    nums[mid_index] = tmp;
    int p = nums[l];
    int i = l + 1;
    for (int j=l+1;j<=r;j++)
    {
        if (nums[j] < p)
        {
            tmp = nums[i];
            nums[i] = nums[j];
            nums[j] = tmp;
            i++;
        }
    }
    tmp = nums[l];
    nums[l] = nums[i-1];
    nums[i-1] = tmp;
    qsort_med(nums,l,i-2, sum);
    qsort_med(nums,i,r,sum);
    sum += i-2 - l + 1 + r - i + 1;
}

void qsort(vector<int>& nums, int l , int r, long long& sum)
{
    if (r <= l)
    {
        return;
    }
    int r_ind = l + rand() % (r - l + 1);
    int tmp;
    tmp = nums[r_ind];
    nums[r_ind] = nums[l];
    nums[l] = tmp;
    int p = nums[l];
    int i = l + 1;
    for (int j=l+1;j<=r;j++)
    {
        if (nums[j] < p)
        {
            tmp = nums[i];
            nums[i] = nums[j];
            nums[j] = tmp;
            i++;
        }
    }
    tmp = nums[l];
    nums[l] = nums[i-1];
    nums[i-1] = tmp;
    qsort(nums,l,i-2, sum);
    qsort(nums,i,r,sum);
    sum += i-2 - l + 1 + r - i + 1;
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
    }
    f.close();
    vector<int> nums1(nums);
    vector<int> nums2(nums);
    vector<int> nums3(nums);
    long long sum = 0;
    qsort_first(nums,0,nums.size()-1,sum);
    cout<<sum<<"\n";
   
    sum = 0;
    qsort_last(nums1,0,nums.size()-1,sum);
    cout<<sum<<"\n";
    
    sum = 0;
    qsort_med(nums2,0,nums.size()-1,sum);
    cout<<sum<<"\n";

    sum = 0;
    qsort(nums3,0,nums.size()-1,sum);
    cout<<sum<<"\n";

    return 0;
}
