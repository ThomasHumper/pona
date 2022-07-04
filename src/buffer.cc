#include "buffer.hh"

Buffer::Buffer(const std::vector<std::string> &p_buffer):
	indentSize(4),

	rawBuffer(p_buffer),
	m_modified(false),

	m_furthestCursorX(0)
{}

char Buffer::At(const Vec2Dw &p_pos) const {
	return rawBuffer.at(p_pos.y).at(p_pos.x);
}

char &Buffer::At(const Vec2Dw &p_pos) {
	return rawBuffer.at(p_pos.y).at(p_pos.x);
}

std::size_t Buffer::Size() const {
	return rawBuffer.size();
}

const Vec2Dw &Buffer::GetCursor() const {
	return m_cursor;
}

void Buffer::SetCursor(const Vec2Dw &p_cursor) {
	m_cursor = p_cursor;
	UpdateCursor();

	m_furthestCursorX = m_cursor.x + CountLineTabs();
}

void Buffer::SetCursorX(std::size_t p_x) {
	m_cursor.x = p_x;
	UpdateCursorX();

	m_furthestCursorX = m_cursor.x + CountLineTabs();
}

void Buffer::SetCursorY(std::size_t p_y) {
	m_cursor.y = p_y;
	UpdateCursorY();
}

void Buffer::CursorRight() {
	if (m_cursor.x < CursorLine().length())
		++ m_cursor.x;
	else if (m_cursor.y < rawBuffer.size() - 1) {
		++ m_cursor.y;
		m_cursor.x = 0;
	}

	m_furthestCursorX = m_cursor.x + CountLineTabs();
}

void Buffer::CursorLeft() {
	if (m_cursor.x > 0)
		-- m_cursor.x;
	else if (m_cursor.y > 0) {
		-- m_cursor.y;
		m_cursor.x = CursorLine().length();
	}

	m_furthestCursorX = m_cursor.x + CountLineTabs();
}

void Buffer::CursorUp() {
	if (m_cursor.y > 0) {
		-- m_cursor.y;
		m_cursor.x = m_furthestCursorX;

		std::size_t posX = 0, i = 0;
		for (; i < CursorLine().length(); ++ i) {
			if (CursorLine().at(i) == '\t')
				posX += indentSize;
			else
				++ posX;

			if (posX > m_cursor.x)
				break;
		}

		m_cursor.x = i;
	} else {
		m_cursor.x = 0;
		m_furthestCursorX = m_cursor.x;
	}
}

void Buffer::CursorDown() {
	if (m_cursor.y < rawBuffer.size() - 1) {
		++ m_cursor.y;
		m_cursor.x = m_furthestCursorX;

		std::size_t posX = 0, i = 0;
		for (; i < CursorLine().length(); ++ i) {
			if (CursorLine().at(i) == '\t')
				posX += indentSize;
			else
				++ posX;

			if (posX > m_cursor.x)
				break;
		}

		m_cursor.x = i;
	} else {
		m_cursor.x = CursorLine().length();
		m_furthestCursorX = m_cursor.x + CountLineTabs();
	}
}

void Buffer::CursorWordRight() {
	while (Utils::IsWhitespace(CursorCh())) {
		CursorRight();

		if (m_cursor.x >= CursorLine().length())
			return;
	}

	do {
		if (m_cursor.x >= CursorLine().length()) {
			CursorRight();

			return;
		}

		CursorRight();
	} while (Utils::IsWordCh(CursorCh()));
}

void Buffer::CursorWordLeft() {
	CursorLeft();

	while (Utils::IsWhitespace(CursorCh())) {
		if (m_cursor.x == 0)
			return;

		CursorLeft();
	}

	CursorLeft();
	while (Utils::IsWordCh(CursorCh())) {
		if (m_cursor.x == 0)
			return;

		if (Utils::IsWordCh(CursorCh()))
			CursorLeft();
	}
	CursorRight();
}

void Buffer::CursorFullUp() {
	m_cursor.y = 0;
	m_cursor.x = 0;
}

void Buffer::CursorFullDown() {
	m_cursor.y = rawBuffer.size() - 1;
	m_cursor.x = CursorLine().length();
}


void Buffer::CursorInsert(char p_ch) {
	CursorLine().insert(m_cursor.x, std::string(1, p_ch));
	++ m_cursor.x;

	m_furthestCursorX = m_cursor.x + CountLineTabs();
	m_modified = true;
}

void Buffer::CursorDelete() {
	if (m_cursor.x > 0) {
		CursorLine().erase(m_cursor.x - 1, 1);
		-- m_cursor.x;
	} else if (m_cursor.y > 0) {
		std::string oldLine = CursorLine();

		rawBuffer.erase(rawBuffer.begin() + m_cursor.y);
		-- m_cursor.y;
		m_cursor.x = CursorLine().length();

		CursorLine() += oldLine;
	}

	m_furthestCursorX = m_cursor.x + CountLineTabs();
	m_modified = true;
}

void Buffer::CursorSplit() {
	std::string newLine = CursorLine().substr(m_cursor.x);
	if (newLine.length() > 0)
		CursorLine().erase(m_cursor.x);

	++ m_cursor.y;
	rawBuffer.insert(rawBuffer.begin() + m_cursor.y, newLine);
	m_cursor.x = 0;

	m_furthestCursorX = m_cursor.x + CountLineTabs();
	m_modified = true;
}

void Buffer::UpdateCursorX() {
	if (m_cursor.x > CursorLine().length())
		m_cursor.x = CursorLine().length();
}

void Buffer::UpdateCursorY() {
	if (m_cursor.y >= rawBuffer.size())
		m_cursor.y = rawBuffer.size() - 1;
}

void Buffer::UpdateCursor() {
	// Y has to be updated first, else CursorLine is gonna throw if it is not correct
	UpdateCursorY();
	UpdateCursorX();
}

const std::string &Buffer::CursorLine() const {
	return rawBuffer.at(m_cursor.y);
}

std::string &Buffer::CursorLine() {
	return rawBuffer.at(m_cursor.y);
}

char Buffer::CursorCh() const {
	// .at() throws, i do not want it to throw in this case
	return CursorLine()[m_cursor.x];
}

char &Buffer::CursorCh() {
	return CursorLine()[m_cursor.x];
}

bool Buffer::IsModified() const {
	return m_modified;
}

void Buffer::FlagUnmodified() {
	m_modified = false;
}

std::size_t Buffer::CountLineTabs() {
	return std::count(CursorLine().begin(), CursorLine().begin() +
	                  m_cursor.x, '\t') * (indentSize - 1);
}
