#include "CMyString.h"

int main()
{
	CMyString example("text1\nSome strings\nstring1\nstring2\nstring3"
					  "\n\nnew string set\nstring4\nstring5\0text2\nnumbers\0text3", 95);
	
	std::cout << example << std::endl;

	int number = 1;
	size_t i = 0;
	while(example.GetLength() > 0)
	{
		if (example[i++] == '\0')
		{
			std::cout << number++ << ")" << std::endl;
			std::cout << example.GetStringData() << "\n-------" << std::endl;
			example = example.SubString(i, example.GetLength());
			i = 0;
		}
	}
}

