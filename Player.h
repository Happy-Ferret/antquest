class Player
{
public:
	Player();
	void pickUp(Item *i);
	void walkTo(int x, int y);
	void setPosition(int x, int y);
	bool isWalking();
	bool isTalking();
	Pos position();
	void say(std::string text);
	void setIcon(const char *icon);
	const char* getIcon();
	void walk(int diff);
	void setAnimation(Animation *an);
	SDL_Rect getCurrentFrame(int time);
	void updateAnim();
	Action getAction();
	void setAction(Action act);
	Animation *a;
	bool hasItem(const char *item);
	void drop(const char *itemname);
private:
	std::vector<Item*> inventory;
	Pos p;
	Pos walkP;
	int direction;
	bool walking;
	bool talking;
	char *icon;
	Action action;
};