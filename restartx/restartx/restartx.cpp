#include <iostream>
#include <windows.h>

int main() {

        HANDLE hToken;
        TOKEN_PRIVILEGES tkp;

        // Get a token for this process.
        if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
            return(1);
        }

        // Get the LUID for the shutdown privilege.
        LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);

        tkp.PrivilegeCount = 1;  // one privilege to set
        tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        // Get the shutdown privilege for this process.
        AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

        // Shut down the system and force all applications to close.
        if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_POWEROFF | EWX_FORCE | EWX_FORCEIFHUNG, 0)) {
            return(1);
        }

        return(0);
    }


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
