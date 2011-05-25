class Item {
public:
	Item(const char *name, const char *iconPicture);
	const char *getName();
	const char *getIcon();
private:
	char *name;
	char *iconPicture;
};