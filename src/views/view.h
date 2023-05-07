#pragma once

class View {
public:
	virtual ~View() = default;
	virtual void draw() = 0;
};
