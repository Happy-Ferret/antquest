class HotSpot {
public:
	HotSpot(int x, int y, int x2, int y2, const char *name);
	bool intersects(int x, int y);
	const char * getName();
private:
	Rect rect;
	const char *spotName;
};