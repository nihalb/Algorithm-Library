#include<stdio.h>

struct Level
{
	Level();
	Level* Children[26];
	bool Terminate;
};

Level::Level()
{
	Terminate = false;
	for(int i=0; i<26; ++i) Children[i] = NULL;
}

class Trie
{
	public:
	Trie();
	void Insert(char str[]);
	bool IsMember(char str[]);
	private:
	Level* Epsilon;
};

Trie::Trie()
{
	Epsilon = new Level();
}

void Trie::Insert(char str[])
{
	Level* Temp = Epsilon;
	for(int index=0; str[index] != '\0'; ++index)
	{
		if(Temp->Children[str[index]-'A'] == NULL)
		{
			Temp->Children[str[index]-'A'] = new Level();
		}
		Temp = Temp->Children[str[index]-'A'];
	}
	Temp->Terminate = true;
}

bool Trie::IsMember(char str[])
{
	Level* Temp = Epsilon;
	for(int index=0; str[index] != '\0'; ++index)
	{
		Temp = Temp->Children[str[index]-'A'];
		if(Temp == NULL) return false;
	}
	return Temp->Terminate;
}

int main()
{
	Trie Dictionary;
	char str[] = "NIHAL";
	char stri[] = "HI";
	Dictionary.Insert(str);
	printf("%d\n",Dictionary.IsMember(str));
	printf("%d\n",Dictionary.IsMember(stri));
	return 0;
}
