#pragma once

class ModelUpdatedReceiver {
public:
	virtual ~ModelUpdatedReceiver() = default;
	virtual void model_updated() = 0;
};
