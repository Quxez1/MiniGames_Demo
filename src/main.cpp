// ########################################################
//                    Platform Globals
// ########################################################
static bool running = true;

// ########################################################
//                    Platform Functions
// ########################################################
bool platform_create_window(int width, int height, const char* title);
void platform_update_window();

// ########################################################
//                    Windows Platform
// ########################################################
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

// ########################################################
//                    Windows Globals
// ########################################################

static HWND Window;

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProcA(hwnd, uMsg, wParam, lParam);
    }
}

// ########################################################
//                Platform Implementations
// ########################################################
LRESULT CALLBACK Windows_window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    switch (msg)
    {
        case WM_CLOSE:
        {
            running = false;
            break;
        }

        default:
        {
            result = DefWindowProcA(hwnd, uMsg, wParam, lParam);
            break;
        }
    }

    return result;
}

bool platform_create_window(int width, int height, const char* title)
{
    HINSTANCE Instance = GetModuleHandleA(NULL);

    WNDCLASSA wc = {};
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hInstance = Instance;
    wc.hIcon = LoadIcon(Instance, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); //Default arrow cursor
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "CasinoWindowClass";
    wc.lpfnWndProc = Windows_window_callback;

    if(!RegisterClassA(&wc))
    {
        return false;
    }

    int dwStyle = WS_OVERLAPPEDWINDOW;

    Window = CreateWindowExA(0, "CasinoWindowClass",
        title,
        dwStyle, //Window style
        100, 100, //Position
        width, height, //Size
        NULL, NULL, Instance, NULL);
    if(!Window) {
        return false;
    }

    ShowWindow(Window, SW_SHOW);
    UpdateWindow(Window);
    return true;
}

void platform_update_window()
{
    MSG msg;

    while(PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
            running = false;
            break;
        }

        TranslateMessage(&msg);
        DispatchMessageA(&msg); //Send the message to the window procedure
    }
}

#endif

int main()
{
    platform_create_window(1200, 800, "Casino");

    while(running)
    {
        // Update
        platform_update_window();
    }

    return 0;
}