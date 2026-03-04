import re

with open('src/main.cpp', 'r', encoding='utf-8') as f:
    content = f.read()

# Remove the int main() block.
main_block_match = re.search(r'int main\(int argc, char \*argv\[\]\) \{.*\}', content, flags=re.DOTALL)
if main_block_match:
    main_block = main_block_match.group(0)
    cpp_content = content[:main_block_match.start()]
else:
    cpp_content = content

# Keep includes, but we must also add #include "FinancialDashboard.h"
# and we can keep the local classes as they are.
# But we must convert the inline class FinancialDashboard to out-of-line definition for the constructor.
# Wait, class FinancialDashboard is defined as:
# class FinancialDashboard : public QMainWindow {
# public:
#     FinancialDashboard(QWidget* parent = nullptr) : QMainWindow(parent) {
# ...
#     }
# };

# We will modify it manually:
dashboard_class_pattern = re.compile(
    r'class FinancialDashboard : public QMainWindow \{\s*public:\s*FinancialDashboard\(QWidget\*\s*parent\s*=\s*nullptr\)\s*:\s*QMainWindow\(parent\)\s*\{',
    re.MULTILINE
)

match = dashboard_class_pattern.search(cpp_content)
if match:
    # Instead of 'class FinancialDashboard...{', it will just be the constructor implementation.
    before = cpp_content[:match.start()]
    after = cpp_content[match.end():]
    
    # We also need to remove the matching closing bracket '};' for the class
    # The class ends right before the end of cpp_content (before main)
    # So we'll just cut out the last '};'
    last_brace_idx = after.rfind('};')
    if last_brace_idx != -1:
        after = after[:last_brace_idx] + after[last_brace_idx+2:]
    
    new_cpp_content = '#include "FinancialDashboard.h"\n' + before + '\nFinancialDashboard::FinancialDashboard(QWidget* parent) : QMainWindow(parent) {\n' + after
else:
    new_cpp_content = cpp_content


with open('src/FinancialDashboard.cpp', 'w', encoding='utf-8') as f:
    f.write(new_cpp_content)

main_content = '''#include "FinancialDashboard.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // Global font
    QFont font("Segoe UI", 10);
    app.setFont(font);
    
    FinancialDashboard window;
    window.show();
    
    return app.exec();
}
'''
with open('src/main.cpp', 'w', encoding='utf-8') as f:
    f.write(main_content)

header_content = '''#pragma once
#include <QMainWindow>

class FinancialDashboard : public QMainWindow {
    Q_OBJECT
public:
    explicit FinancialDashboard(QWidget* parent = nullptr);
};
'''
with open('src/FinancialDashboard.h', 'w', encoding='utf-8') as f:
    f.write(header_content)

with open('CMakeLists.txt', 'r', encoding='utf-8') as f:
    cmake_content = f.read()

cmake_content = cmake_content.replace('src/main.cpp', 'src/main.cpp\n    src/FinancialDashboard.cpp')
with open('CMakeLists.txt', 'w', encoding='utf-8') as f:
    f.write(cmake_content)
