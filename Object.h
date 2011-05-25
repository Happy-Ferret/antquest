class Object {
public:
	Object(int x, int y, int x2, int y2, const char *name, const char *icon);
	bool intersects(int x, int y);
	const char * getName();
	const char *getIcon();
	SDL_Rect getRect();
	SDL_Surface* getSurface();
private:
	Rect rect;
	const char *objectName;
	const char *objectIcon;
	SDL_Rect srect;
	SDL_Surface* surface;
};