#ifndef UI_MANAGER_H_
#define UI_MANAGER_H_

#include <unordered_map>

#include "EventInterface.h"

class UiManager {
private:
	struct UiText {
		int x;
		int y;
		std::string message;
	};
public:
    UiManager();
    ~UiManager();
    void Render();
    void Init();
private:
    void RenderTest();
    void handleUiDisplayEvent(EventInterface* event);
private:
    const bool testFlag_;
    std::unordered_map<std::string, UiText> text_list_;
};

#endif  // UI_MANAGER_H_

