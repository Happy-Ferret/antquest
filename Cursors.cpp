#include "AntQuest.h"

void Cursors::loadCursors() {
	char line[33];
	const char *cursorFiles[] = {
	"usecursor.xpm",
	"lookcursor.xpm",
	"walkcursor.xpm",
	"talkcursor.xpm",
	"usecursorover.xpm",
	"lookcursorover.xpm",
	"lookcursorover.xpm",
	"lookcursorover.xpm"
	};

	for (int i=0; i<8; i++) {
		std::ifstream f(cursorFiles[i]);
		int j=0;
		if (f.is_open())
		{
		    while (! f.eof()&&j<37 )
			{
				f.getline(line,33);
				for (int k=0; k<32; k++) {
					cursors[i][j][k]=line[k];
				}
				j++;
			}
			f.close();
		}
	}
}


// Taken from SDL documentation
SDL_Cursor *Cursors::init_system_cursor(char image[37][32])
{
  int i, row, col;
  Uint8 data[4*32];
  Uint8 mask[4*32];
  int hot_x, hot_y;

  i = -1;
  for ( row=0; row<32; ++row ) {
    for ( col=0; col<32; ++col ) {
      if ( col % 8 ) {
        data[i] <<= 1;
        mask[i] <<= 1;
      } else {
        ++i;
        data[i] = mask[i] = 0;
      }
      switch (image[row][col]) {
        case 'X':
          data[i] |= 0x01;
          mask[i] |= 0x01;
          break;
        case '.':
          mask[i] |= 0x01;
          break;
        case ' ':
          break;
      }
    }
  }
  sscanf(image[row], "%d,%d", &hot_x, &hot_y);
  return SDL_CreateCursor(data, mask, 32, 32, hot_x, hot_y);
}

Cursors::Cursors() {
	loadCursors();
}


SDL_Cursor *Cursors::getCursor(int index) {
	switch (index) {
		case 0: return init_system_cursor(cursors[0]);
			break;
		case 1: return init_system_cursor(cursors[1]);
			break;
		case 2: return init_system_cursor(cursors[2]);
			break;
		case 3: return init_system_cursor(cursors[3]);
			break;
		case 4: return init_system_cursor(cursors[4]);
			break;
		case 5: return init_system_cursor(cursors[5]);
			break;
		default: return init_system_cursor(cursors[0]);
			break;
	}
}