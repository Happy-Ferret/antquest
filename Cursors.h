class Cursors {
public:
Cursors();
SDL_Cursor *getCursor(int index);
private:
	void loadCursors();
	SDL_Cursor *init_system_cursor(char image[37][32]);
	char cursors[8][37][32];
};