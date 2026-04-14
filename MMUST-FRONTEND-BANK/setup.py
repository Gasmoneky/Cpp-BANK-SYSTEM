import os
import platform
import subprocess
import sys
import shutil

def run_cmd(cmd):
    """Executes a command and handles errors."""
    try:
        print(f"Executing: {cmd}")
        subprocess.check_call(cmd, shell=True)
    except subprocess.CalledProcessError as e:
        print(f"Error executing command: {e}")

def create_structure():
    """Creates the mirrored include/src directory structure."""
    print("📂 Building folder structure...")
    folders = [
        "assets", "build", "third_party",
        "include/core", "include/ui", "include/service", "include/data",
        "src/core", "src/ui", "src/service", "src/data"
    ]
    for folder in folders:
        os.makedirs(folder, exist_ok=True)
    print("✓ Structure ready.")



def install_system_deps():
    """Installs compilers and graphics headers for Fedora, Ubuntu, and Arch."""
    os_name = platform.system()
    
    if os_name == "Linux":
        print("🐧 Linux detected. Identifying distribution...")
        
        # 1. Fedora (DNF)
        if shutil.which("dnf"):
            print("Detected Fedora/RHEL. Using dnf...")
            run_cmd("sudo dnf install -y @development-tools cmake glfw-devel openssl-devel sqlite-devel mesa-libGL-devel")
            
        # 2. Ubuntu/Debian (APT)
        elif shutil.which("apt-get"):
            print("Detected Ubuntu/Debian. Using apt...")
            run_cmd("sudo apt-get update")
            run_cmd("sudo apt-get install -y build-essential cmake libglfw3-dev libssl-dev libsqlite3-dev libgl1-mesa-dev")
            
        # 3. Arch Linux (PACMAN)
        elif shutil.which("pacman"):
            print("Detected Arch Linux. Using pacman...")
            # Arch usually includes headers in the main package
            run_cmd("sudo pacman -S --needed --noconfirm base-devel cmake glfw-wayland openssl sqlite mesa")
            
        else:
            print("❌ Error: Could not identify package manager (dnf, apt, or pacman).")
            print("Please install development tools, cmake, glfw, openssl, and sqlite manually.")

    elif os_name == "Windows":
        print("🪟 Windows detected. Ensure Visual Studio and CMake are installed.")
        # winget is a good fallback for modern Windows
        run_cmd("winget install kitware.cmake --silent")

def setup_libraries():
    """Clones and bootstraps vcpkg to manage our 'Bank-Grade' libraries."""
    if not os.path.exists("third_party/vcpkg"):
        print("📦 Cloning vcpkg...")
        os.chdir("third_party")
        run_cmd("git clone https://github.com/microsoft/vcpkg.git")
        os.chdir("vcpkg")
        
        # Bootstrap vcpkg
        if platform.system() == "Linux":
            run_cmd("./bootstrap-vcpkg.sh")
        else:
            run_cmd(".\\bootstrap-vcpkg.bat")
        
        # Install specific libraries
        print("📥 Installing ImGui, SQLCipher, JSON, and Httplib...")
        # [imgui[glfw-opengl3-binding]] gives us the specific code to draw the window
        libs = "imgui[glfw-opengl3-binding] sqlcipher nlohmann-json cpp-httplib"
        if platform.system() == "Linux":
            run_cmd(f"./vcpkg install {libs}")
        else:
            run_cmd(f".\\vcpkg install {libs}")
            
        os.chdir("../..")

if __name__ == "__main__":
    create_structure()
    install_system_deps()
    setup_libraries()
    print("\n✅ PROJECT INITIALIZED!")
    print("Your environment is configured for 'Bank-Grade' development on " + platform.system() + ".")
