class NPC
{
public:
	NPC();
	void walkTo(int x, int y);
	void setPosition(int x, int y);
	bool isWalking();
	bool isTalking();
	Pos position();
	void say(std::string text);
	void setIcon(const char *icon);
	const char* getIcon();
	void walk(int diff);
	const char *getSpeech();
	Rect getRect();
private:
	std::vector<Item> *inventory;
	Pos p;
	Pos walkP;
	int direction;
	bool walking;
	bool talking;
	const char *icon;
	const char *speechString;
	const char *room;
};