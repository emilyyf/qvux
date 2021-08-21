#include <tty.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t row;
size_t column;
u8 color;
u16* buffer;

static inline u8 vga_entry_color(vga_color fg, vga_color bg) {
	return (bg << 4) | fg;
}

static inline u16 vga_entry(unsigned char uc, u8 color) {
	return ((u16) color << 8) | (u16) uc;
}

void tty_init(void) {
	row = 0;
	column = 0;
	color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
	buffer = (u16*) 0xB8000;
	for (size_t y = 0; y < VGA_WIDTH; ++y) {
		for (size_t x = 0; x < VGA_WIDTH; ++x) {
			buffer[y * VGA_WIDTH + x] = vga_entry(' ', color);
		}
	}
}

void tty_set_color(vga_color fg, vga_color bg) {
	color = vga_entry_color(fg, bg);
}

void tty_scroll(void) {
	u16* _buf = (u16*) 0xB8000;
	for (size_t y = 0; y < VGA_WIDTH; ++y) {
		for (size_t x = 0; x < VGA_WIDTH; ++x) {
			_buf[y * VGA_WIDTH + x] = _buf[(y + 1) * VGA_WIDTH + x];
		}
	}
}

void tty_new_line(void) {
	column = 0;
	++row;
	if (row == VGA_HEIGHT) {
		--row;
		tty_scroll();
	}
}

void tty_put_char(char c) {
	if (c == '\n')
		return tty_new_line();

	const size_t index = row * VGA_WIDTH + column;
	buffer[index] = vga_entry(c, color);

	if (++column == VGA_WIDTH) {
		tty_new_line();
	}
}

void tty_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; ++i)
		tty_put_char(data[i]);
}

void printf(const char* data) {
	tty_write(data, strlen(data));
}