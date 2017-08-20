#ifndef UI_MANAGER_H_
#define UI_MANAGER_H_

class UiManager {
public:
    UiManager();
    ~UiManager();
    void Render();
    void Init();
private:
    void RenderTest();
private:
    const bool testFlag_;
};

#endif  // UI_MANAGER_H_

