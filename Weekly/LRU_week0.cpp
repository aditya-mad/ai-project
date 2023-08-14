#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int frames_count, pages_count, page_faults = 0;
	cin >> frames_count >> pages_count;

	vector<int> frames(frames_count), pages(pages_count);

	for (int i = 0; i < pages_count; i++)
		cin >> pages[i];

	for (auto current_page : pages)
	{
		vector<int>::iterator present = find(frames.begin(), frames.end(), current_page);

		if (present != frames.end())
		{
			frames.erase(present);
		}
		else
		{
			page_faults++;
			if (frames.size() == frames_count)
			{
				frames.erase(frames.begin());
			}
		}
		frames.push_back(current_page);
	}

	cout << "No of page faults - " << page_faults;

	return 0;
}
