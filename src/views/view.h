#pragma once

class View {
public:
	virtual ~View() = default;
	virtual void draw() = 0;
	virtual void clear() = 0;
};
