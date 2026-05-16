# Kavaro Desktop Management System 🚀

Kavaro is a high-performance desktop application built with **C++** and the **Qt Framework**. It serves as a comprehensive management dashboard designed for financial tracking, order management, and specialized handling of STL (3D model) file uploads and processing.

---

## 🛠 Tech Stack

*   **Language:** Modern C++ (C++17/20)
*   **UI Framework:** Qt Widgets (for a native, hardware-accelerated experience).
*   **Build System:** CMake (Cross-platform compatibility).
*   **Styling:** Custom QSS (Qt Style Sheets) for a modern, dark-themed aesthetic (Deep Navy/Slate).
*   **Resources:** Qt Resource System (.qrc) for embedding assets directly into the binary.

---

## 📂 Detailed Project Structure & File Roles

### 🏛 Core Files
- **`src/main.cpp`**: The entry point. Initializes the `QApplication`, sets global fonts (Segoe UI), manages the `LoginWindow`, and handles the smooth transition to the `FinancialDashboard` upon successful authentication.
- **`CMakeLists.txt`**: Defines project dependencies, includes, and build instructions for compilers.
- **`qrc.qrc`**: Manages all embedded assets like icons, logos, and background images.

### 🏠 Main Screens (`src/Screens/`)
- **`Dashboard/FinancialDashboard.cpp`**: The master container window. It orchestrates the entire UI by bringing together the Sidebar, TopNavbar, and the content area using a `QStackedWidget` for seamless page switching.
- **`Auth/`**: Contains the logic for user login and registration, ensuring secure access to the dashboard.

### 📄 Dashboard Pages (`src/Screens/Dashboard/Pages/`)
Each page is a dedicated `QWidget` swapped in the main stack:
- **`OverviewPage.cpp`**: The landing page. Contains high-level analytics, financial charts (StatusBarChart), and a recent orders summary.
- **`AllOrdersPage.cpp`**: A comprehensive table view for managing transactions, including order status tracking and search functionality.
- **`STLUploadsPage.cpp`**: A specialized module for 3D model management.
    - Features a drag-and-drop style `STLUploadArea`.
    - Uses an `STLGrid` to display models as custom `STLCard` widgets.
    - Supports category filtering (e.g., Gaming, Anime) and file metadata display (Size, Triangle count).
- **`NotificationsPage.cpp`**: Manages system alerts and user updates.
- **`SettingsPage.cpp`**: Allows users to configure application preferences and profile details.

### 🧩 UI Components (`src/Screens/Dashboard/Components/`)
Reusable widgets that build the interface:
- **`Sidebar.cpp`**: A vertical navigation bar that controls the `QStackedWidget`. It supports expansion/collapse for space efficiency.
- **`TopNavbar.cpp`**: The header component featuring global search, notification triggers, user profile access, and the sidebar toggle button.
- **`STL_Uploads_page/`**: A sub-directory of components specifically for the STL page, including `STLHeader`, `STLGrid`, and `STLCard`.

---

## ⚙️ How It Works (The Engine)

### 1. Signal & Slot Mechanism
The app heavily relies on Qt's **Signal and Slot** architecture:
- Clicking a menu item in the `Sidebar` emits a signal that tells the `FinancialDashboard` to switch the active index of the `QStackedWidget`.
- Uploading a file in the `STLUploadArea` triggers a signal that dynamically appends a new `STLCard` to the grid.

### 2. Modular UI Design
Instead of one giant file, every UI element is its own class. This makes the code **maintainable** and **scalable**. For example, to change the look of an STL card, you only need to edit `STLCard.cpp` without touching the main page logic.

### 3. State-of-the-Art Styling
The application uses a "Glassmorphic" and "Flat-Modern" hybrid design. Backgrounds are deep slate (#0f172a), while interactive elements use gradients and subtle hover effects implemented via QSS.

---

## 🚀 Getting Started

### Prerequisites
- **Qt 6.x** (or 5.15+)
- **CMake 3.16+**
- A C++17 compatible compiler (MSVC, GCC, or Clang)

### Build Instructions
1.  **Clone the Repository**:
    ```bash
    git clone https://github.com/tahagaber/Kavaro_Desktop.git
    ```
2.  **Open in IDE**: Open `CMakeLists.txt` in **Qt Creator** or **VS Code**.
3.  **Configure & Build**: Run the CMake configure step and then build the project.
4.  **Run**: Execute the `Kavaro_decktop` binary.

---

## 📝 Roadmap
- [ ] Integration with a backend Database (SQL/PostgreSQL).
- [ ] Real-time 3D previewing of STL files using `QtDataVisualization` or `Qt3D`.
- [ ] Enhanced PDF export for financial reports.

---
*Created by Taha Gaber - Kavaro Project*
