class Animation
{
public:
	Animation();
	void addAnim(const char *name);
	void addFrame(int index, int x, int y, int w, int h, const char *name);
	SDL_Rect getFrame(int time);
	void setAnim(const char *name);
private:
	struct Anim {
		const char *animationName;
		SDL_Rect rects[MAX_FRAMES];
	};
	Anim anims[MAX_ANIMS];
	int currentFrame;
	int currentAnim;
	int nextFreeAnim;
};