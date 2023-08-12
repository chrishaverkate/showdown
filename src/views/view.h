#pragma once

class View {
public:
	virtual ~View() = default;
	virtual void draw() = 0;
	virtual void clear() = 0;

	virtual void activate() { _active = true; }
	virtual void deactivate() { _active = false; }

protected:
	bool _active = false;
};
