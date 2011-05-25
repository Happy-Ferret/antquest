class Room {
public:
	Room();
	int newRoom(const char *roomStr);
	const char* getBackground();
	const char* getFile();
	void setBackground(const char* bg);
	HotSpot* intersectsHotSpot(int x, int y);
	Object* intersectsObject(int x, int y);

	unsigned getNumberofObjects();
	Object *getObject(int index);
	void addHotSpot(HotSpot *hs);
	void addObject(Object *obj);
private:
	void TesT();
	char* backGround;
	std::vector<HotSpot*> hotSpots;
	std::vector<Object*> objects;
	std::vector<WalkArea> walkAreas;
	char* fileName;
};